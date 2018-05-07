#include <os/sysio.h>
#include <bios/BIOS-time.h>
#include <openssl/AES.h>
#include <openssl/SHA.h>
#include <string.h>
#include <stdlib.h>

struct urandomState{
	unsigned char key[32];
	unsigned char iv[16];
	unsigned char state[32];
};

struct urandomState state;

void reduce(unsigned char* in,unsigned char* out,unsigned int outLen){
	for(int i = 0; i<outLen;i++)
		out[i] = in[2*i]^in[2*i+1];
}

void updateUrandom(){
	AES_KEY key;
	unsigned char nstate[32];
	unsigned char vstate[64];
	AES_set_encrypt_key(state.key,256,&key);
	AES_cbc_encrypt(state.state,nstate,32,state.iv,&key);
	SHA512(nstate,32,vstate);
	SHA256(nstate,32,state.state);
	reduce(vstate,state.key,32);
}

void urandom(unsigned char* out,unsigned int outSize){
	int tSize = outSize;
	int blocks;
	unsigned char* buff;
	unsigned char* currBuff;
	while(tSize%32!=0)
		tSize*=2;
	blocks = tSize/32;
	buff = malloc(tSize);
	currBuff = buff;
	for(int i = 0;i<blocks;i++){
		SHA256(state.state,32,currBuff);
		updateUrandom();
		currBuff += 32;
	}
	while(tSize!=outSize){
		tSize/=2;
		reduce(buff,buff,tSize);
	}
	memcpy(buff,out,outSize);
	memset(buff,0,blocks*32);
}
void seedUrandom(){
	unsigned char cntrls[2][4];
	unsigned char time[12];
	unsigned char mouse[3];
	unsigned char noise[32];
	unsigned char tmp[64];
	int fd = open("/dev/controllers",READ);
	
	read(fd,0,cntrls,sizeof(cntrls));
	close(fd);
	fd = open("/dev/rtc",READ);
	read(fd,0,time,sizeof(time));
	close(fd);
	fd = open("/dev/mouse",READ);
	read(fd,0,mouse,sizeof(mouse));
	close(fd);
	fd = open("/dev/mmu/analog",READ);
	read(fd,0,noise,sizeof(noise));
	close(fd);
	
	SHA256(cntrls,sizeof(cntrls)+sizeof(time)+sizeof(mouse)+sizeof(noise),tmp);
	memcpy(tmp,state.state,32);
	SHA512(cntrls,sizeof(cntrls)+sizeof(time)+sizeof(mouse)+sizeof(noise),tmp);
	reduce(tmp,state.key,32);
	SHA256(cntrls,sizeof(cntrls)+sizeof(time)+sizeof(mouse)+sizeof(noise)+sizeof(tmp),tmp);
	reduce(tmp,state.iv,16);
	updateUrandom();
	urandom(tmp,64);
}

unsigned char lastPoolHash[32];

void random(unsigned char* out,int outsize){
	unsigned char lastHash[32];
	unsigned char cntrls[2][4];
	unsigned char time[12];
	unsigned char mouse[3];
	unsigned char noise[32];
	unsigned char tmp[64];
	
	int fd;
	int tSize = outSize;
	int blocks;
	unsigned char* buff;
	unsigned char* currBuff;
	memcpy(lastPoolHash,lastHash,32);
	while(tSize%32!=0)
		tSize*=2;
	blocks = tSize/32;
	buff = malloc(tSize);
	currBuff = buff;
	for(int i = 0;i<blocks;i++){
		fd = open("/dev/controllers",READ);
		read(fd,0,cntrls,sizeof(cntrls));
		close(fd);
		fd = open("/dev/rtc",READ);
		read(fd,0,time,sizeof(time));
		close(fd);
		fd = open("/dev/mouse",READ);
		read(fd,0,mouse,sizeof(mouse));
		close(fd);
		fd = open("/dev/mmu/analog",READ);
		read(fd,0,noise,sizeof(noise));
		close(fd);
		urandom(tmp,sizeof(tmp));
		SHA256(lastHash,sizeof(lastHash)+sizeof(cntrls)+sizeof(time)+sizeof(mouse)+sizeof(noise)+sizeof(tmp),currBuff);
		memcpy(currBuff,lastHash,32);
		currBuff += 32;
	}
	while(tSize!=outSize){
		tSize/=2;
		reduce(buff,buff,tSize);
	}
	memcpy(buff,out,outSize);
	memset(buff,0,blocks*32);
}
