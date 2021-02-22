#ifndef _SMG_H_
#define _SMG_H_

#include "stc89.h" 
#include "delay.h"
#include <intrins.h>
#define  NOP() _nop_()  /* 定义空指令 */
#define DUAN P1
#define WEI P0


uchar code LED7Code_CC[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //CC共陰極不帶小數點0-F
//uchar code LED7Code[16]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0xf7,0xfc,0xb9,0xde,0xf9,0xf1}; //CC共陰極帶小數點0-F
uchar Wei_CC[8]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};  //CC共陰極相對於位端位公共端，位的控制端

uchar code LED7Code_CA[16]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x4e,0x83,0xc6,0xa1,0x86,0x8e};  //CA共陽極不帶小數點0-F
//uchar code LED7Code[16]= {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,0x08,0x03,0x46,0x21,0x06,0x0e}; //CA共陽極帶小數點0-F
uchar Wei_CA[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};  //CA共陽極相對於位端位公共端來講的，位的控制端


extern void SMG_Init();

#endif
