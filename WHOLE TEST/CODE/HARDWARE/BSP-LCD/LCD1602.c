#include "lcd1602.h"

void rd_bf()
{
  unsigned char sta;
    dataport=0xff;
    RS=0;
    RW=1;
    do{
      E=1;
      sta=dataport;
      E=0;
    }while(sta&0x80);
}

void Lcd1602WriteData(unsigned char dat)
{
 rd_bf();
 RS=1;
 RW=0;
 E=1;
 dataport=dat;
 E=0;
}

void Lcd1602WriteDictate(unsigned char dictate)
{
 rd_bf();
 RS=0;
 RW=0;
 E=1;
 dataport=dictate;
 E=0;
}

void Lcd1602Display(unsigned char address,unsigned char _data)
{
  Lcd1602WriteDictate(address);
  Lcd1602WriteData(_data);
}


void Lcd1602ClearScreen(void)
{
 Lcd1602WriteData(0x01);
 delay_us(50);
}


void Lcd1602_Init(void)
{
 Lcd1602ClearScreen();
 Lcd1602WriteDictate(0x38);//��ʾģʽ���ã� ���� 16x2 ��ʾ�� 5x7 ����8λ�ӿ�
 Lcd1602WriteDictate(0x01);//����ʾ
 Lcd1602WriteDictate(0x40); //��ʼ��ʾ��ַ
 Lcd1602ClearScreen();
}


