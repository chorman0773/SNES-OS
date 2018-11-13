/*
 * GFX.h
 *
 *  Created on: Nov 13, 2018
 *      Author: chorm
 */

#ifndef SNES_OS_OS_GFX_H__2018_11_317_11_22_50
#define SNES_OS_OS_GFX_H__2018_11_317_11_22_50

#include <stdint.h>

#ifdef __cplusplus
extern"C"{
#endif
/**
 * Opaque Structure storing Graphics Environment Information
 */
typedef struct sGFXEnv* GFXEnv;

enum GFXEnvField{
	DECORATED,
	VISIBLE,
	XPOS,
	YPOS,
	LEN,
	HEIGHT,
	ICON,
	NAME
};

enum GFXErrorCode{
	E_OK = 0,
	E_INVALID = -1,
	E_RESOURCE_UNAVAILABLE = -2,
	E_WAIT  = 3,
	E_STOP = 4,
	E_NO_TARGET = 5,
	E_DISPOSED = 6,
	E_UNBOUNND = 7,
	E_TERM = 9,
	E_NO_PERMISSION = 1
};

enum GFXErrorCode newGFXEnv(GFXEnv __restrict__ parent,GFXEnv __restrict__*  out)__attribute__((nonnull(2)));

enum GFXErrorCode freeGFXENv(GFXEnv env)__attribute__((nonnull(1)));

enum GFXErrorCode getRoot(GFXEnv* rout)__attribute__((nonnull(1)));



bool isValid(GFXEnv env);

enum GFXErrorCode gfxEnvGet(GFXEnv target,enum GFXEnvField field,...)__attribute__((nonnull(1)));
enum GFXErrorCode gfxEnvSet(GFXEnv target,enum GFXEnvField field,...)__attribute__((nonnull(1)));


enum GFXErrorCode gfxDraw(GFXEnv target,uint16_t dlen,uint16_t dwidth,const uint16_t* ddata)__attribute__((nonnull(1,4)));


enum GFXErrorCode gfxCreate(GFXEnv target)__attribute__((nonnull(1)));
enum GFXErrorCode gfxDispose(GFXEnv target)__attribute__((nonnull(1)));

#ifdef __cplusplus
};
#endif

#endif /* SNES_OS_OS_GFX_H__2018_11_317_11_22_50 */
