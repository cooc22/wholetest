#define byte unsigned char 

data int result; 
sbit cs_ad= 0xa4; 
sbit dout= 0xa3; 
sbit clk= 0xa2; 

void delay(void) //��ʱ�ӳ��� 
{ 
data byte i,j; 
for(i=0;i<255;i++) 
{ 
for(j=0;j<255;j++) ; 
} 
} 
main() 
{ 
data byte i; 
number1: 
cs_ad=1; //��ֹI/O CLOCK 
cs_ad=0; //�������Ƶ�·��ʹ��DATA OUT��I/O CLOCK 
result=0; //��ת������ 
for(i=0;i<10;i++) //�ɼ�10�� ����10bit 
{ 
clk=0; 
result*=2; 
if(dout) result++; 
clk=1; 
} 
delay(); 
cs_ad=1; //DATA OUT ���ص�����״̬����ֹ���� 
result=result; //ת�������ֵ����ڱ���result1�� 
goto number1; //����ȥ�ɼ� 
}