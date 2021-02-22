#ifndef _LCD12864_
#define _LCD12864_

#include "stc89.h"
#include "intrins.h"
#include "delay.h"
#define _nop {}
#define High 1
#define Low    0

sbit RS=P3^2;
sbit RW=P3^3;
sbit EN=P3^4;
sbit CS1=P3^0;
sbit CS2=P3^1;
sbit RST=P3^5;

unsigned char code huan[]={
0x14,0x24,0x44,0x84,0x64,0x1C,0X20,0X18,0X0F,0XE8,0X08,0X08,0X28,0X18,0X08,0X00,
0X20,0X10,0X4C,0X43,0X43,0X2C,0X20,0X10,0X0C,0X03,0X06,0X18,0X30,0X60,0X20,0X00};//��

unsigned char code ying[]={
0x40,0x41,0xCE,0x04,0x00,0xFC,0x04,0x02,0x02,0xFC,0x04,0x04,0x04,0xFC,0x00,0x00,
0x40,0x20,0x1F,0x20,0x40,0x47,0x42,0x41,0x40,0x5F,0x40,0x42,0x44,0x43,0x40,0x00}; //ӭ

unsigned char code chai[]={
0x80,0x80,0xFC,0x80,0x7F,0x48,0x48,0x00,0x7F,0x90,0x88,0x84,0x82,0xE0,0x00,0x00,
0x44,0x44,0x24,0x24,0x14,0x0C,0x04,0xFF,0x04,0x0C,0x14,0x24,0x24,0x44,0x44,0x00}; //��

unsigned char code yu[]={
0x20,0x10,0x2C,0xE7,0x24,0x24,0x00,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0x00,0x00,
0x01,0x01,0x01,0x7F,0x21,0x11,0x40,0x41,0x41,0x41,0x7F,0x41,0x45,0x59,0x40,0x00}; //��

unsigned char code wen[]={
0x08,0x08,0x08,0x38,0xC8,0x08,0x09,0x0E,0x08,0x08,0xC8,0x38,0x08,0x08,0x08,0x00,
0x80,0x80,0x40,0x40,0x20,0x11,0x0A,0x04,0x0A,0x11,0x20,0x40,0x40,0x80,0x80,0x00}; //��

unsigned char code zi[]={
0x10,0x10,0xD0,0xFF,0x90,0x10,0x40,0x44,0x54,0x65,0xC6,0x64,0x54,0x44,0x40,0x00,
0x04,0x03,0x00,0xFF,0x00,0x03,0x00,0x04,0x04,0x04,0xFF,0x04,0x04,0x04,0x00,0x00}; //��

unsigned char code shan[]={
0x10,0x10,0xF0,0x1F,0x10,0xF0,0x80,0xFE,0x82,0xFE,0x80,0xFE,0x82,0xFE,0x80,0x00,
0x40,0x22,0x15,0x08,0x16,0xA1,0x60,0x1F,0x20,0xBF,0x40,0x3F,0x80,0xFF,0x00,0x00}; //�

unsigned char code hao[]={
0x00,0x82,0x82,0xBA,0xAA,0xAA,0xAA,0xAB,0xAA,0xAA,0xAA,0xBA,0x82,0x82,0x80,0x00,
0x02,0x01,0xA0,0xAA,0xAA,0x56,0x56,0xAA,0xF2,0x12,0x2A,0x22,0x40,0x42,0x01,0x00}; //��

extern void Lcd12864_Busy();
extern void Lcd12864WriteCommand(uchar command);
extern void Lcd12864WriteData(uchar ucdata);
extern void Lcd12864Display(unsigned char page,unsigned char col,unsigned char code *hzk);
extern void Lcd12864_ClearScreen(void);
extern void Lcd12864_Init(void);
extern void PortInit(void);

#endif
