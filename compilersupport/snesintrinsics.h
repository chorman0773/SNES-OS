/*
 * snesintrinsics.h
 *
 *  Created on: Nov 13, 2018
 *      Author: chorm
 */

#ifndef COMPILERSUPPORT_SNESINTRINSICS_H__2018_11_317_12_23_42
#define COMPILERSUPPORT_SNESINTRINSICS_H__2018_11_317_12_23_42

#define __intrinsic __attribute__((intrinsic,always_inline,naked)) __inline__

__intrinsic void __builtin_sep(unsigned char flg){
	__asm__("sep ?":flg);
}

__intrinsic void __builtin_rep(unsigned char flg){
	__asm__("rep ?":flg);
}

#endif /* COMPILERSUPPORT_SNESINTRINSICS_H__2018_11_317_12_23_42 */
