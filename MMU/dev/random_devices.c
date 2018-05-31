#include <devices.h>

#include <openssl/AES.h>
#include <openssl/SHA.h>
#include <string.h>
#include <stdlib.h>

#define random devices[18]
#define urandom devices[19];

extern device devices[];

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
	unsigned char cntrls[8];
	unsigned char time[12];
	unsigned char mouse[4];
	unsigned char noise[32];
	unsigned char tmp[64];
	devices[0].read(0,cntrls,sizeof(cntrls));
  devices[1].read(0,time,sizeof(time));
  devices[2].read(0,mouse,sizeof(mouse));
  devices[255].read(0,noise,sizeof(noise));
	
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
	unsigned char mouse[4];
	unsigned char noise[32];
	unsigned char tmp[64];
	
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
		devices[0].read(0,cntrls,sizeof(cntrls));
    devices[1].read(0,time,sizeof(time));
    devices[2].read(0,mouse,sizeof(mouse));
    devices[255].read(0,noise,sizeof(noise));
		urandom(tmp,sizeof(tmp));
		SHA256(lastHash,sizeof(lastHash)+sizeof(cntrls)+sizeof(time)+sizeof(mouse)+sizeof(noise)+sizeof(tmp),currBuff);
		memcpy(currBuff,lastHash,32);
		currBuff += 32;
	}
	SHA256(buff,tSize,lastPoolHash);
	while(tSize!=outSize){
		tSize/=2;
		reduce(buff,buff,tSize);
	}
	memcpy(buff,out,outSize);
	memset(buff,0,blocks*32);
	free(buff);
}

int readUrandom(unsigned long long l,unsigned char* out,unsigned int outSize){
  urandom(out,outSize);
  return outSize;
}
int readRandom(unsigned long long l,unsigned char* out,unsigned int outSize){
  random(out,outSize);
  return outSize;
}

int writeUrandom(unsigned long long l,unsigned const char* in,unsigned int inSize){
  return -1;
}
int writeRandom(unsigned long long l,unsigned const char* in,unsigned int inSize){
  return -1;
}




