#ifndef __KEY_H__
#define __KEY_H__

#include "stc89.h"
#include "delay.h"
#include "led_8.h"


sbit KEY0=P3^7;
sbit KEY1=P3^6;
sbit KEY2=P3^5;
sbit KEY3=P3^4;

extern void Key_Scan();
extern void Key_Init();


#endif
