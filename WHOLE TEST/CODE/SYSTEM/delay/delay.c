#include "delay.h"
							    
							   
void delay_ms(uchar nms)
{
   uchar i,j;
    for(i=nms;i>0;i--)
    for(j=110;j>0;j--);
       ;
}

void delay_us(uint nus)
{
   uint i,j;
   for(i=nus;i>0;i--)
   for(j=255;j>0;j--);
}





































