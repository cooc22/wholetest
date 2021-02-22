#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "stc89.h"
#include "delay.h"
#define HIGH 1
#define LOW  0

uchar table[]={"welcome to my world\n"};
uchar table1[]={"xinjing isn't good\n"};
sfr dataport = 0xA0;
sbit RS = P3^2;
sbit RW = P3^3;
sbit E  = P3^4;

extern void rd_bf();
extern void Lcd1602WriteData(uchar dat);
extern void Lcd1602WriteDictate(uchar dictate);
extern void Lcd1602Display(uchar address,uchar _data);
extern void Lcd1602ClearScreen(void);
extern void Lcd1602_Init(void);

#endif	

