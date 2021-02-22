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
Lcd12864WriteCommand(0x30);//�������ã�һ���� 8 λ���ݣ�����ָ�
Lcd12864WriteCommand(0x0C);//������ʾ���α� off���α�λ�� off
Lcd12864WriteCommand(0x01);//�� DDRAM
Lcd12864WriteCommand(0x02);//DDRAM ��ַ��λ
Lcd12864WriteCommand(0x80);//�趨 DDRAM 7 λ��ַ 000��0000 ����ַ������ AC
//Lcd12864ClearScreen();
}

void PortInit(void)
{
 P0=P1=P2=P3=0xFF;
}

