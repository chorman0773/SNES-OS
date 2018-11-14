/*
 * device.h
 *
 *  Created on: Nov 13, 2018
 *      Author: chorm
 */

#ifndef SNES_OS_OS_DEV_DEVICE_H__2018_11_317_17_29_13
#define SNES_OS_OS_DEV_DEVICE_H__2018_11_317_17_29_13
#include <stddef.h>
#include <stdbool.h>
#include <os/types.h>
#include <os/fs/path.h>

typedef unsigned short devno_t;

typedef unsigned char devtype_t;

typedef struct{
	devtype_t type;
	int(*read)(void*,unsigned long,size_t);
	int(*write)(const void*,unsigned long,size_t);
}device;

devno_t registerDevice(device);
void mkNod(devno_t,path*);

fd_t devopen(devno_t,unsigned char);



#endif /* SNES_OS_OS_DEV_DEVICE_H__2018_11_317_17_29_13 */
