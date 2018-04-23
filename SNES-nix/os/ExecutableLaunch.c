#include "ExecutableLaunch.h"
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <BIOS.h>

const char* const cmainSyms[] = {"main"};

const char* const cppmainSyms[] = {"main","main@**CI","main@**^CI","main@**^CI"};

const char* const cppstartupSym = "startup";

int symHash(const char* name,int len){
	int hash = 0;
	const int prime =  31;
	for(int i = 0;i<strlen(name);i++){
		hash *= prime;
		hash += name[i];
	}
	return hash%len;	
}

binary_descriptor readHeader(FILE* f){
	binary_descriptor desc;
	fseek(f,0,SEEK_SET);
	fread(&desc,sizeof(binary_descriptor),1,f);
	return desc;
}

bool validateElf(FILE* f){
	binary_descriptor desc = readHeader(f);
	if(desc.magic!=ELF_MAGIC)
		return false;
	return true;
}

bool validateLib(FILE* f){
	binary_descriptor desc = readHeader(f);
	if(desc.magic!=LIB_MAGIC)
		return false;
	return true;
}

symbol* openSymbols(FILE* f){
	binary_descriptor header = readHeader(f);
	fseek(f,sizeof(binary_descriptor),SEEK_SET);
	symbo* ret = (symbol*) calloc(header.symtblSize,sizeof(symbol));
	fread(ret,header.symtblSize,sizeof(symbol),f);
	return ret;
}

bool areNamesEqual(const char* a,const char* b){
	if(strlen(a)!=strlen(b))
		return false;
	else if(memcmp(a,b,strlen(a))!=0)
		return false;
	return true;
}

void* link(FILE* f,const char* name){
	binary_descriptor header = readHeader(f);
	symbol* symbols = openSymbols(f);
	int addr = symHash(name,header.symtblSize);
	symbol sym = symbols[addr];
	if(!areNamesEqual(name,sym.name))
		return NULL;
	else if(sym.type==DUMMY)
		return NULL;
	return sym.addr;
}
typedef int (*main_t)(const char**,int);
typedef void (*startup_t)(void);
void startup(FILE* f,const char** argv,int argc){
	binary_descriptor header = readHeader(f);
	void* prg = (void*)0x000100;
	void* cdata = (void*)0x000110+header.execSize;
	void* data = (void*) cdata+0x10+header.cdataSize;
	void* stack = 0x700000;
	void* heap = 0x740000;
	main_t main;
	startup_t startup;
	symbol* symbols;
	if(!validateElf(f)){
		fprintf(stderr,"Could not start file. Not a valid elf file");
		abort();
	}
	setpermissions(prg,header.execSize,PROC_Read|PROC_Write);
	setpermissions(cdata,header.cdataSize,PROC_Read|PROC_Write);
	setpermissions(data,header.dataSize,PROC_Read|PROC_Write);
	
	fread(cdata,header.cdataSize,1,f);
	setpermissions(cdata,header.cdataSize,PROC_Read);
	fread(data,header.dataSize,1,f);
	fread(prg,header.execSize,1,f);
	setpermission(prg,header.execSize,PROC_Read|PROC_Exec);
	if(header.type==cpp){
		startup = (startup_t)link(f,cppstartupSym);
		if(startup!=NULL)
			startup();
		for(int i = 0;i<sizeof(cppmainSyms)/sizeof(const char* const);i++){
			main = (main_t)link(f,cppmainSyms[i]);
			if(main!=NULL)
				break;
		}
	}else
		for(int i = 0;i<sizeof(cmainSyms)/sizeof(const char* const);i++){
			main = (main_t)link(f,cmainSyms[i]);
			if(main!=NULL)
				break;
		}
	
	if(main==NULL){
		fprintf(stderr,"Could not start file, no entry point found");
		abort();
	}
	setProtectionLevel(3);
	exit(main(argv,argc));
}


