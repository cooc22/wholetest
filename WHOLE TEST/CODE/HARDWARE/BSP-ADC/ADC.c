#include "stc89.h"
#include "intrins.h"
#include "adc.h"
#include "key.h"

#define MaxAdcBufSize 9
#define AdcBufStep 3

static volatile unsigned int ADCBuffer[MaxAdcBufSize];

/********************************************************
ADC��ʼ��
********************************************************/
void InitADC(void)
{ 
	ADMUX |= (1<<REFS1)|(1<<REFS0);
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	//ADCʹ��;ADC��ʼת��;����ת��;�ж�ʹ��;128��Ƶ
}

/********************************************************
��ȡADC
********************************************************/
unsigned int ReadADC(void)
{ 
	return ADCBuffer[0];
}

/********************************************************
ADCת������ж�
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
