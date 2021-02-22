#include "smg.h"

uint t0;
uchar sec,min,hour;

void SMG_Init()
{
  uchar i;
  for(i=0;i<8;i++)
   {
    DUAN=LED7Code_CA[i];
    WEI=Wei_CA[i];
    delay_ms(50);
    DUAN=0xff;
    }
   
  for(i=0;i<8;i++)
   {
    DUAN=LED7Code_CC[i];
    WEI=Wei_CC[i];
    delay_ms(50);
    DUAN=0x00;
    }
}

/*
void smg_count()//時鐘的秒分時算術邏輯这里要计算基时间
{
    t0++;
    
    if(t0==200)
    {
     t0=0;
     sec++;
    }
    if(sec>=60)
    {
     sec=0;
     min++;
    }
    if(min>=60)
    {
     min=0;
     hour++;
    }
    if(hour>=24)
    {
     hour=0;
    }
}
*/