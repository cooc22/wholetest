/*程序采用了状态机的思路，分为检测引导码，32位数据接收，连发码处理 三个状态。
还对用户码进行了校验，限定处理唯一用户码的遥控器的数据。对于反码也加入了验证。
 
检测程序如下：（程序使用11.0592Mhz晶振  不能使用12Mhz）*/
#include<reg52.h>  
#define uchar unsigned char
#define uint unsigned int
sbit beep=P1^7;
bit startflag;  //定义一个扫描开始标志位
bit irreceok;//红外接收OK标志位
bit irprosok;//红外接收处理OK标志位
uchar irdata[33];//定义一个存放编码的数组。引导码1位，客户码8位，客户反码8位，数据码8位，数据反码8位 ，共33位
uchar bitnum;//接收到的第几位数据的标志位
uchar irtime;//定义红外扫描时间
uchar ircode[4];//为四个码值定义一个数组存放，把四位码分开
uchar disp[8];//四组数据，每组拆成高四位和低四位，共八个元素
/**************1602部分******************/
sbit lcden=P1^2;
sbit lcdrs=P1^0;
sbit lcdrw=P1^1;
/*char code Tab[]={'0','1','2','3','4','5','6','7','8',
'9','A','B','C','D','E','F'};*/
char code Tab[]="0123456789abcdef";
void delay(uint z) //延时子程序
{
  uint x,y;
  for(x=z;x>0;x--)
  for(y=220;y>0;y--);
}

void write_com(uchar com)//定义一个带参数的写命令子程序
{
 lcdrs=0; //1602的rs为0时，接收命令，为1时接收数据
 P0=com;//把void write_com(uchar com)中的COM中的数据给P0口
 delay(2);
 lcden=1;
 delay(2);
 lcden=0;
 delay(2);
}

void init_1602()//定义一个初始化子程序
{
 lcden=0;
 lcdrw=0;
 write_com(0x38);//调用 write_com子程序并把0x38赋给P0口，显示模式打开
 write_com(0x0f);//调用 write_com子程序并把“开显示，显示光标，光标闪烁”指令码赋给P0口
 write_com(0x06);//调用 write_com子程序并把“地址指针加1，整屏不移动”指令码赋给P0口
 //write_com(0x80+0x10);//数据指针初始化，让指针指向可显示的最右端
 write_com(0x80);//数据指针初始化，让指针指向最左端，显示从第一行开始
 write_com(0x01);//调用 write_com子程序并把"清零指"令码赋给P0口
 }
 
void write_dat(uchar dat)//定义一个带参数的写数据子程序
{
 lcdrs=1; //1602的rs为0时，接收命令，为1时接收数据
 P0=dat;//把void write_shu(uchar shu)中的COM中的数据给P0口
 delay(2);
 lcden=1;
 delay(2);
 lcden=0;
 delay(2);
}
 
void delayms(uint t)
{
 uint i,j;
 for(i=t;i>0;i--)
 for(j=110;j>0;j--); 
}
void timer0init()//定时器O初始化
{
 TMOD=0x02;//定时器设成方式2，因为方式2可以自动重装初值
 TH0=0x00;//高位设为O
 TL0=0x00;//低位设为O
 ET0=1; //中断打开
 EA=1;//总中断打开
 TR0=1;//定时器打开
}

void int0init()//外部中断O初始化,按P3。2
{
 IT0=1;//设为下降沿触发方式。IT0=0为低电平触发。因为红外输入高时，接收为低，要从低开始计时
 EX0=1;//外部中断打开
 EA=1;//总中断打开
}

void irpros()//红外提取处理程序
{
  uchar i,k,j,irvalue;
  k=1;//第一k=0是引导码，不须要。所以从K=1开始提取编码，把K=0的引导码去掉
  for(j=0;j<4;j++)//共有四个码，所以循环四次
   {
     for(i=0;i<8;i++)//每个码八位，循环八次
    {
     irvalue=irvalue>>1;//irvalue低位在前，高位在后，所以右移，判断8次，右移7次
   if(irdata[k]>6)//如果两个中断的时间为1.125MS，说明传的是0，1.125/0.255=4.4个irtime,
   //如果两个中断的时间为1.125MS，说明传的是1，2.25/0.255=8.8个irtime,
   //我取中断值6；如果irdata大于6，说明是1，小于6说明是0；
    {
     irvalue=irvalue|0x80;
    }
    k++;//每提一次，K自增一次，一共要33次
  }
  ircode[j]=irvalue;
   }
  irprosok=1;
  beep=0;
  delay(3);
  beep=1;
}
void irwork()
{
 disp[0]=ircode[0]/16;//取高四位
 disp[1]=ircode[0]%16;//取低四位
 disp[2]=ircode[1]/16;//取高四位
 disp[3]=ircode[1]%16;//取低四位
 disp[4]=ircode[2]/16;//取高四位
 disp[5]=ircode[2]%16;//取低四位
 disp[6]=ircode[3]/16;//取高四位
 disp[7]=ircode[3]%16;//取低四位
}
void display()
{
 write_com(0x80);
 write_dat(Tab[disp[0]]);
 write_dat(Tab[disp[1]]);
 write_dat(Tab[disp[2]]);
 write_dat(Tab[disp[3]]);
 write_dat(Tab[disp[4]]);
 write_dat(Tab[disp[5]]);
 write_dat(Tab[disp[6]]);
 write_dat(Tab[disp[7]]);
}
void main()
{
 init_1602();
 timer0init();
 int0init();
   while(1)
     {
  if(irreceok)//判断接收是否OK
     {
   irpros();//接收OK就要处理.把数据从irdata中提出来
         irreceok=0;//要把irreceok清0，为下一次接收做准备
  }
  if(irprosok)
     {
   irwork();//如果处理OK，把数据分离，可以去显示
   irprosok=0;//要把irprosok清0，为下一次处理做准备
  }
    display();//显示函数还没写，有待完善
   
  }
 
}

void timer0() interrupt 1//定时器0中断函数
{
irtime++;/*irtime为字符型，最大为255，输入开始时读一次irtime
然后清0，结束再读一次，irtime乘以255就是一次扫描定时的时间*/
}
void int0() interrupt 0//外部中断0函数，这是关键
{
 if(startflag)//如果startflag=1就开始接数据
  {
     if(irtime>30) //接收引导码,引导码有9MS，9/0.256=33.15，在这就取32即可
                //说明这时检测到了引导码
  {
    bitnum=0;//收到引导码后，bitnum清O准备装数据
  }
  irdata[bitnum]=irtime;//第1个bitnum=0的数据被装入数组。
  irtime=0;//清0就不会对下次有影响
     bitnum++; //不停地给数组加入新数据
  
   if(bitnum==33)//如果bitmun=33，说明一帧数据传完
    {
     bitnum=0;//bitnum清0为接收下一帧做准备
     irreceok=1;//主函数只要判断irreceok是否为1做出后面的决定
    }
      
  }
else //
    {
  startflag=1;
  irtime=0;
 }
}

/*
	#include <reg52.h> 
	#include "lcd1602.h" 
003	#define uchar unsigned  char     // 宏定义uchar 为无符号字符 
004	#define uint  unsigned  int   
005	      
006	#define IR_UserCode 0xFF00          //红外遥控器 用户码  
007	uchar IR_Code[32] = {0}; 
008	uchar IR_User[16] = {0};  //用户码 
009	uchar IR_Data[8]  = {0};  //数据码 
010	uchar IR_CData[8] = {0};  //数据反码 
011	uchar key= '0',value = 0; //key LCD显示值; value  接收头接收到值（16进制） 
012	typedef enum
013	{ 
014	    State_0 = 0x00, 
015	    State_1 = 0x01, 
016	    State_2 = 0x02 
017	      
018	}ScanState_Typedef;  
019	ScanState_Typedef ScanState; 
020	void  IR_Check(void); 
021	void  IR_CodeHandle(void); 
022	void  IR_Decode(void); 
023	void  delay(uint n); 
024	void main() 
025	{                
026	    LCD_Init(); 
027	    LCD_WriteString("The Key Is:",1); 
028	      
029	    while(1){ 
030	        IR_Check(); 
031	    }  
032	} 
033	void  IR_Check(void) 
034	{ 
035	    uchar i=0,n=0; 
036	    switch(ScanState) 
037	    { 
038	        case State_0 :              //检测引导码 
039	        {    
040	            while(IR_DQ == 1); 
041	                  
042	            delay(500);       
043	            if( IR_DQ == 0 ) 
044	            { 
045	                while(IR_DQ == 0);   
046	                  
047	                delay(300); 
048	  
049	                if(IR_DQ == 1) 
050	                { 
051	                    ScanState = State_1;         
052	                    while( IR_DQ == 1 ); 
053	                }else{ 
054	                    ScanState = State_2;        //为连发码 
055	                          
056	                } 
057	            }else{ 
058	                    ScanState = State_0; 
059	            } 
060	  
061	            break; 
062	                                              
063	        } 
064	              
065	        case State_1:                      // 32位数据接收 
066	        { 
067	  
068	            while(i < 32){ 
069	                while(IR_DQ == 0); 
070	                delay(60);                  //延时0.48ms 
071	                      
072	                if(IR_DQ == 1) 
073	                IR_Code[i] = 0; 
074	  
075	                delay(28);                  //延时0.22ms,总延时0.70ms 
076	  
077	                if(IR_DQ == 1) 
078	                {    
079	                    IR_Code[i] = 1; 
080	                    while(IR_DQ == 1); 
081	                }else{ 
082	                    IR_Code[i] = 0; 
083	                } 
084	                i++; 
085	            } 
086	            IR_CodeHandle(); 
087	            ScanState = State_0;                     
088	            break; 
089	        } 
090	        case State_2:                       //连发码处理 
091	        { 
092	            while( IR_DQ == 0 ); 
093	            ScanState = State_0;     
094	                      
095	            break; 
096	        }    
097	    } 
098	} 
099	void IR_CodeHandle(void) 
100	{ 
101	    uchar n=0,check=0; 
102	    uint  user = 0; 
103	    for(n=0;n<8;n++) 
104	    { 
105	        IR_User[n] = IR_Code[n];      //低位用户码 
106	        IR_User[8+n] = IR_Code[8+n];  //高位用户码 
107	        IR_Data[n] = IR_Code[16+n]; 
108	        IR_CData[n] = IR_Code[24+n]; 
109	        if(IR_Data[n] + IR_CData[n] == 0x01){ check++;}    //反码检测,正数的原码和补码 各位相加后为 0x01 
110	    } 
111	    for(n=0;n<16;n++)                       //处理用户码 
112	    { 
113	        if(n==0) 
114	        { 
115	            user = IR_User[0]; 
116	        }else{ 
117	            user += IR_User[n] * (2 << (n-1)); 
118	        } 
119	    } 
120	    if((user == IR_UserCode) && (check == 8))      //用户码校验 反码校验 
121	    { 
122	        for(n=0;n<8;n++)                //处理数据码,二进制转换为16进制 
123	        { 
124	            if(n==0) 
125	            { 
126	                value = IR_Data[0]; 
127	            }else{ 
128	                value += IR_Data[n] * (2 << (n-1)); 
129	            } 
130	        } 
131	        IR_Decode(); 
132	        LCD_WriteByte(0xC7,0);         //更新接收值 
133	        LCD_WriteByte(key,1); 
134	    } 
135	      
136	} 
137	void  IR_Decode(void) 
138	{ 
139	    //P3 = value; 
140	    switch(value) 
141	    { 
142	        case 0x0D : key = '0';break; 
143	        case 0x0C : key = '1';break; 
144	        case 0x18 : key = '2';break; 
145	        case 0x5E : key = '3';break; 
146	        case 0x08 : key = '4';break; 
147	        case 0x1C : key = '5';break; 
148	        case 0x5A : key = '6';break; 
149	        case 0x42 : key = '7';break; 
150	        case 0x52 : key = '8';break; 
151	        case 0x4A : key = '9';break; 
152	        default : key= '?';  
153	    } 
154	} 
155	void delay(uint n) 
156	{ 
157	    while(--n);             // 8us一次 
158	}
*/