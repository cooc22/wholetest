#include "led.h"


void LED_Init()
{
	delay_ms(100);
    LED=0xff;
    delay_ms(100);
	LED=0x00;
}


/***********************************

LED功能函數:1.全亮全灭2.顺序亮顺序灭3.倒序亮倒序灭4.一个一个亮灭(流水灯)5.单独一个亮灭(跑马灯)

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
          LED=0xfe;          //第一个灯亮 1111.1110
          delay_ms(100);
          LED=0xfd;          //第二个灯亮
          delay_ms(100);
          LED=0xfb;          //第三个灯亮
          delay_ms(100);
          LED=0xf7;          //第四个灯亮
          delay_ms(100);
          LED=0xef;          //第五个灯亮
          delay_ms(100);
          LED=0xdf;          //第六个灯亮
          delay_ms(100);
          LED=0xbf;          //第七个灯亮
          delay_ms(100);
          LED=0x7f;          //第八个灯亮
          delay_ms(100);
          LED=0xff;
          LED=0xfe;          //第一个灯亮
          delay_ms(100);
	 }
}
 

void back_oneled(uchar i)
  {
	       uchar j;
	 for(j=0;j<i;j++)
	 {
           LED=0x7f;          //第八个灯亮 0111.1111
           delay_ms(100);
           LED=0xbf;          //第七个灯亮
           delay_ms(100);
           LED=0xdf;          //第六个灯亮
           delay_ms(100);
           LED=0xef;          //第五个灯亮
           delay_ms(100);
           LED=0xf7;          //第四个灯亮
           delay_ms(100);
           LED=0xfb;          //第三个灯亮
           delay_ms(100);
           LED=0xfd;         //第二个灯亮
           delay_ms(100);
           LED=0xfe;         //第一个灯亮
           delay_ms(100);
     }
  }
  
  
  void stopled(void)
{
       LED=0xff;    //关闭8个LED
	   delay_ms(100);
}



void runninghorse(void)
{ 
  uint i;
  uchar temp; 
  {
    temp=0x01;
    for(i=0;i<8;i++)  //8个流水灯逐个闪动
    {
    LED=~temp;		//0xfe
    delay_ms(100);   //调用延时函数
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
    for(i=0;i<8;i++)  //8个流水灯反向逐个闪动
   {
    LED=~temp;		  //0x7f
    delay_ms(100);   //调用延时函数
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
   for(i=0;i<8;i++)  //8个流水灯依次全部点亮
  {
   LED=temp;
   delay_ms(100);   //调用延时函数
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
   for(i=0;i<8;i++)  //8个流水灯依次反向全部点亮
   {
    LED=temp;
    delay_ms(100);   //调用延时函数
    temp=(temp|0x01)>>1;
   }
  }
  if(LED == 0x00 )	
  { 
  LED = 0x7f; 
  } // 0xfe = 1111 1110 
}



