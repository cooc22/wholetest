#define byte unsigned char 

data int result; 
sbit cs_ad= 0xa4; 
sbit dout= 0xa3; 
sbit clk= 0xa2; 

void delay(void) //延时子程序 
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
cs_ad=1; //禁止I/O CLOCK 
cs_ad=0; //开启控制电路，使能DATA OUT和I/O CLOCK 
result=0; //清转换变量 
for(i=0;i<10;i++) //采集10次 ，即10bit 
{ 
clk=0; 
result*=2; 
if(dout) result++; 
clk=1; 
} 
delay(); 
cs_ad=1; //DATA OUT 返回到高阻状态而终止序列 
result=result; //转换后的数值存放在变量result1中 
goto number1; //重新去采集 
}