#include "key.h"


void Key_Init()
{
 KEY0=KEY1=KEY2=KEY3=0;
 delay_ms(100);
 KEY0=KEY1=KEY2=KEY3=1;
}

void Key_Scan(void)
{
  if(!KEY0)
    {
	  delay_ms(10);
	  if(!KEY0)
	  {
	   	oneled();
		while(!KEY0);
	  }
	}

	 if(!KEY1)
    {
	  delay_ms(10);
	  if(!KEY1)
	  {
	   oneled();
		while(!KEY1);
	  }
	}

	 if(!KEY2)
    {
	  delay_ms(10);
	  if(!KEY2)
	  {
	   oneled();
		while(!KEY2);
	  }
	}

	 if(!KEY3)
    {
	  delay_ms(10);
	  if(!KEY3)
	  {
	   oneled();
		while(!KEY3);
	  }
	}
	
}

