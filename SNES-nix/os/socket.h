#ifndef __socket_h_2018_06_06_12_56
#define __socket_h_2018_06_06_12_56
#include <os/types.h>
#ifdef __cplusplus
extern "C"{
#endif

#define AF_INET 1
#define AF_UNIX 2
#define AF_BTH 3
#define AF_UNSPECIFIED 0

#define SOCK_DGRAM 1
#define SOCK_RAW 2
#define SOCK_STREAM 3
#define SOCK_SEQPACKET 4
#define SOCK_RDM 5
#define SOCK_UNSPECIFIED 0

#define IPPROTO_ICMP 1
#define IPPROTO_IGMP 2
#define IPPROTO_TCP 3
#define IPPROTO_UDP 4
#define IPPROTO_RM 5
#define BTHPROTO_RFCOMM 6
#define PROTO_UNSPECIFIED 0

typedef struct sockaddr{
  unsigned short sa_family;
  char sa_data[14];
}SOCKADDR;
typedef struct in_addr{
  union{
    unsigned char S_un_b[4];
    unsigned short S_un_w[2];
    unsigned int S_un;
  };
}INADDR;
typedef struct sockaddr_in{
  unsigned short sin_family;
  unsigned short sin_port;
  union in_addr sin_addr;
  char zero[8];
}SOCKADDR_IN;

fd_t socket(int,int,int);

int accept(fd_t,INADDR*,int*);
int bind(fd_t,const struct sockaddr*,int);
int connect(fd_t,const struct sockaddr*,int);
int listen(fd_t,int);

unsigned int inetaddr(const char*);

#ifdef __cplusplus
};
#endif
#endif
