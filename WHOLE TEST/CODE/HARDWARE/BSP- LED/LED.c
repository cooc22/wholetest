#include "led.h"


void LED_Init()
{
	delay_ms(100);
    LED=0xff;
    delay_ms(100);
	LED=0x00;
}


/***********************************

LED���ܺ���:1.ȫ��ȫ��2.˳����˳����3.������������4.һ��һ������(��ˮ��)5.����һ������(�����)

void  LED_All_ON();
void  LED_All_OFF();
void  LED_Left_One();
void  LED_Right_One();
void  LED_Left_Continue();
void  LED_Right_Continue();

***********************************/

void oneled(uchar i)
 {
	      uchar j;
	 for(j=0;j<i;j++)
	 {
          LED=0xfe;          //��һ������ 1111.1110
          delay_ms(100);
          LED=0xfd;          //�ڶ�������
          delay_ms(100);
          LED=0xfb;          //����������
          delay_ms(100);
          LED=0xf7;          //���ĸ�����
          delay_ms(100);
          LED=0xef;          //���������
          delay_ms(100);
          LED=0xdf;          //����������
          delay_ms(100);
          LED=0xbf;          //���߸�����
          delay_ms(100);
          LED=0x7f;          //�ڰ˸�����
          delay_ms(100);
          LED=0xff;
          LED=0xfe;          //��һ������
          delay_ms(100);
	 }
}
 

void back_oneled(uchar i)
  {
	       uchar j;
	 for(j=0;j<i;j++)
	 {
           LED=0x7f;          //�ڰ˸����� 0111.1111
           delay_ms(100);
           LED=0xbf;          //���߸�����
           delay_ms(100);
           LED=0xdf;          //����������
           delay_ms(100);
           LED=0xef;          //���������
           delay_ms(100);
           LED=0xf7;          //���ĸ�����
           delay_ms(100);
           LED=0xfb;          //����������
           delay_ms(100);
           LED=0xfd;         //�ڶ�������
           delay_ms(100);
           LED=0xfe;         //��һ������
           delay_ms(100);
     }
  }
  
  
  void stopled(void)
{
       LED=0xff;    //�ر�8��LED
	   delay_ms(100);
}



void runninghorse(void)
{ 
  uint i;
  uchar temp; 
  {
    temp=0x01;
    for(i=0;i<8;i++)  //8����ˮ���������
    {
    LED=~temp;		//0xfe
    delay_ms(100);   //������ʱ����
    temp<<=1;
    }
	if(LED == 0x00 )	
    { 
	LED = 0xfe; 
	  } // 0xfe = 1111 1110 
   }
 }


void back_runninghorse()
{
  uint i;
  uchar temp; 
   
   {
    temp=0x80;
    for(i=0;i<8;i++)  //8����ˮ�Ʒ����������
   {
    LED=~temp;		  //0x7f
    delay_ms(100);   //������ʱ����
    temp>>=1;
   }
  if(LED == 0x00 )	
  { 
  LED = 0x7f; 
  } // 0xfe = 1111 1110 
  }
}

void flowingwater(void)
{
	uint i;
    uchar temp; 

  
  {
  temp=0xfe;
   for(i=0;i<8;i++)  //8����ˮ������ȫ������
  {
   LED=temp;
   delay_ms(100);   //������ʱ����
   temp=(temp|0x01)<<1;
  }
  if(LED == 0x00 )	
  { 
  LED = 0xfe; 
  } // 0xfe = 1111 1110 
  }
}

void back_flowingwater(void)
{
  uint i;
  uchar temp; 
  
  {
   temp=0x7f;
   for(i=0;i<8;i++)  //8����ˮ�����η���ȫ������
   {
    LED=temp;
    delay_ms(100);   //������ʱ����
    temp=(temp|0x01)>>1;
   }
  }
  if(LED == 0x00 )	
  { 
  LED = 0x7f; 
  } // 0xfe = 1111 1110 
}



