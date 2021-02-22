#include "stc89.h"
#include "intrins.h"
#include "adc.h"
#include "key.h"

#define MaxAdcBufSize 9
#define AdcBufStep 3

static volatile unsigned int ADCBuffer[MaxAdcBufSize];

/********************************************************
ADC初始化
********************************************************/
void InitADC(void)
{ 
	ADMUX |= (1<<REFS1)|(1<<REFS0);
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	//ADC使能;ADC开始转换;连续转换;中断使能;128分频
}

/********************************************************
读取ADC
********************************************************/
unsigned int ReadADC(void)
{ 
	return ADCBuffer[0];
}

/********************************************************
ADC转换完成中断
********************************************************/
SIGNAL(SIG_ADC)
{ 
	unsigned char i;
	unsigned int tmp,sum = 0;
	tmp = ADC;
	
	for(i=1;i<MaxAdcBufSize - 1;i++)
	{
		ADCBuffer[i] = ADCBuffer[i+1];
		sum += ADCBuffer[i];
	}
	ADCBuffer[MaxAdcBufSize - 1] = tmp;
	sum += ADCBuffer[MaxAdcBufSize - 1];
	ADCBuffer[0] = (sum >> AdcBufStep);
}
