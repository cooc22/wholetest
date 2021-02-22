#include "lcd12864.h"


void Lcd12864_Busy()
 {
  uchar busy;
  EN=Low;
  RS=Low;
  RW=High;
  while(1)
  {
    EN=High;
    _nop;
      _nop;
    busy=P0;
      _nop;
    EN=Low;
    if((busy&0x90)==0)
    break;
  };
 }

void Lcd12864WriteCommand(uchar command)
 {
  Lcd12864_Busy();
  RS=Low;
  _nop;
  RW=Low;
  _nop;
  EN=High;
  _nop;
  P0=command;
  _nop;
  EN=Low;  
  _nop;
 }
 

void Lcd12864WriteData(uchar ucdata)
  {
   Lcd12864_Busy();  
   RS=High;
   _nop;
   RW=Low;
   _nop;
   EN=High;
   _nop;
   P0=ucdata;
   _nop;
   EN=Low;
   _nop;
  }
  


void Lcd12864Display(unsigned char page,unsigned char col,unsigned char code *hzk)
{
 unsigned char j=0,i=0;
 for(j=0;j<2;j++)
  {
   Lcd12864WriteCommand(0xb8+page+j);
   Lcd12864WriteCommand(0x40+col);
   for(i=0;i<16;i++)
   Lcd12864WriteData(hzk[16*j+i]);
  }
}

void Lcd12864_ClearScreen(void)
{
 Lcd12864WriteCommand(0x01);
 delay_us(20);
}


void Lcd12864_Init(void)
{
Lcd12864WriteCommand(0x30);//功能设置，一次送 8 位数据，基本指令集
Lcd12864WriteCommand(0x0C);//整体显示，游标 off，游标位置 off
Lcd12864WriteCommand(0x01);//清 DDRAM
Lcd12864WriteCommand(0x02);//DDRAM 地址归位
Lcd12864WriteCommand(0x80);//设定 DDRAM 7 位地址 000，0000 到地址计数器 AC
//Lcd12864ClearScreen();
}

void PortInit(void)
{
 P0=P1=P2=P3=0xFF;
}

