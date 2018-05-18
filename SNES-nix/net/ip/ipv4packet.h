#ifndef __ipv4packet_h_2018_05_18_12_32
#define __ipv4packet_h_2018_05_18_12_32

#include <stdint.h>
#include <os/io/sysio.h>

typedef struct{
  uint8_t versionAndHeaderLength;
  uint8_t dscpAndEcn;
  uint16_t packetLength;
  uint16_t identification;
  uint16_t flagsAndFragmentOffset;
  uint8_t ttl;
  uint8_t protocol;
  uint16_t headerCsum;
  uint32_t sourceIpAddress;
  uint32_t destinationIpAddress;
  uint32_t options[];
} ipheader;

typedef union{
  char addrBytes[4];
  uint32_t addrVal;
}inet_addr;


#endif
