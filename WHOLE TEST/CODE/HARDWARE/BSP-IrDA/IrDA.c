/*���������״̬����˼·����Ϊ��������룬32λ���ݽ��գ������봦�� ����״̬��
�����û��������У�飬�޶�����Ψһ�û����ң���������ݡ����ڷ���Ҳ��������֤��
 
���������£�������ʹ��11.0592Mhz����  ����ʹ��12Mhz��*/
#include<reg52.h>  
#define uchar unsigned char
#define uint unsigned int
sbit beep=P1^7;
bit startflag;  //����һ��ɨ�迪ʼ��־λ
bit irreceok;//�������OK��־λ
bit irprosok;//������մ���OK��־λ
uchar irdata[33];//����һ����ű�������顣������1λ���ͻ���8λ���ͻ�����8λ��������8λ�����ݷ���8λ ����33λ
uchar bitnum;//���յ��ĵڼ�λ���ݵı�־λ
uchar irtime;//�������ɨ��ʱ��
uchar ircode[4];//Ϊ�ĸ���ֵ����һ�������ţ�����λ��ֿ�
uchar disp[8];//�������ݣ�ÿ���ɸ���λ�͵���λ�����˸�Ԫ��
/**************1602����******************/
sbit lcden=P1^2;
sbit lcdrs=P1^0;
sbit lcdrw=P1^1;
/*char code Tab[]={'0','1','2','3','4','5','6','7','8',
'9','A','B','C','D','E','F'};*/
char code Tab[]="0123456789abcdef";
void delay(uint z) //��ʱ�ӳ���
{
  uint x,y;
  for(x=z;x>0;x--)
  for(y=220;y>0;y--);
}

void write_com(uchar com)//����һ����������д�����ӳ���
{
 lcdrs=0; //1602��rsΪ0ʱ���������Ϊ1ʱ��������
 P0=com;//��void write_com(uchar com)�е�COM�е����ݸ�P0��
 delay(2);
 lcden=1;
 delay(2);
 lcden=0;
 delay(2);
}

void init_1602()//����һ����ʼ���ӳ���
{
 lcden=0;
 lcdrw=0;
 write_com(0x38);//���� write_com�ӳ��򲢰�0x38����P0�ڣ���ʾģʽ��
 write_com(0x0f);//���� write_com�ӳ��򲢰ѡ�����ʾ����ʾ��꣬�����˸��ָ���븳��P0��
 write_com(0x06);//���� write_com�ӳ��򲢰ѡ���ַָ���1���������ƶ���ָ���븳��P0��
 //write_com(0x80+0x10);//����ָ���ʼ������ָ��ָ�����ʾ�����Ҷ�
 write_com(0x80);//����ָ���ʼ������ָ��ָ������ˣ���ʾ�ӵ�һ�п�ʼ
 write_com(0x01);//���� write_com�ӳ��򲢰�"����ָ"���븳��P0��
 }
 
void write_dat(uchar dat)//����һ����������д�����ӳ���
{
 lcdrs=1; //1602��rsΪ0ʱ���������Ϊ1ʱ��������
 P0=dat;//��void write_shu(uchar shu)�е�COM�е����ݸ�P0��
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
void timer0init()//��ʱ��O��ʼ��
{
 TMOD=0x02;//��ʱ����ɷ�ʽ2����Ϊ��ʽ2�����Զ���װ��ֵ
 TH0=0x00;//��λ��ΪO
 TL0=0x00;//��λ��ΪO
 ET0=1; //�жϴ�
 EA=1;//���жϴ�
 TR0=1;//��ʱ����
}

void int0init()//�ⲿ�ж�O��ʼ��,��P3��2
{
 IT0=1;//��Ϊ�½��ش�����ʽ��IT0=0Ϊ�͵�ƽ��������Ϊ���������ʱ������Ϊ�ͣ�Ҫ�ӵͿ�ʼ��ʱ
 EX0=1;//�ⲿ�жϴ�
 EA=1;//���жϴ�
}

void irpros()//������ȡ�������
{
  uchar i,k,j,irvalue;
  k=1;//��һk=0�������룬����Ҫ�����Դ�K=1��ʼ��ȡ���룬��K=0��������ȥ��
  for(j=0;j<4;j++)//�����ĸ��룬����ѭ���Ĵ�
   {
     for(i=0;i<8;i++)//ÿ�����λ��ѭ���˴�
    {
     irvalue=irvalue>>1;//irvalue��λ��ǰ����λ�ں��������ƣ��ж�8�Σ�����7��
   if(irdata[k]>6)//��������жϵ�ʱ��Ϊ1.125MS��˵��������0��1.125/0.255=4.4��irtime,
   //��������жϵ�ʱ��Ϊ1.125MS��˵��������1��2.25/0.255=8.8��irtime,
   //��ȡ�ж�ֵ6�����irdata����6��˵����1��С��6˵����0��
    {
     irvalue=irvalue|0x80;
    }
    k++;//ÿ��һ�Σ�K����һ�Σ�һ��Ҫ33��
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
 disp[0]=ircode[0]/16;//ȡ����λ
 disp[1]=ircode[0]%16;//ȡ����λ
 disp[2]=ircode[1]/16;//ȡ����λ
 disp[3]=ircode[1]%16;//ȡ����λ
 disp[4]=ircode[2]/16;//ȡ����λ
 disp[5]=ircode[2]%16;//ȡ����λ
 disp[6]=ircode[3]/16;//ȡ����λ
 disp[7]=ircode[3]%16;//ȡ����λ
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
  if(irreceok)//�жϽ����Ƿ�OK
     {
   irpros();//����OK��Ҫ����.�����ݴ�irdata�������
         irreceok=0;//Ҫ��irreceok��0��Ϊ��һ�ν�����׼��
  }
  if(irprosok)
     {
   irwork();//�������OK�������ݷ��룬����ȥ��ʾ
   irprosok=0;//Ҫ��irprosok��0��Ϊ��һ�δ�����׼��
  }
    display();//��ʾ������ûд���д�����
   
  }
 
}

void timer0() interrupt 1//��ʱ��0�жϺ���
{
irtime++;/*irtimeΪ�ַ��ͣ����Ϊ255�����뿪ʼʱ��һ��irtime
Ȼ����0�������ٶ�һ�Σ�irtime����255����һ��ɨ�趨ʱ��ʱ��*/
}
void int0() interrupt 0//�ⲿ�ж�0���������ǹؼ�
{
 if(startflag)//���startflag=1�Ϳ�ʼ������
  {
     if(irtime>30) //����������,��������9MS��9/0.256=33.15�������ȡ32����
                //˵����ʱ��⵽��������
  {
    bitnum=0;//�յ��������bitnum��O׼��װ����
  }
  irdata[bitnum]=irtime;//��1��bitnum=0�����ݱ�װ�����顣
  irtime=0;//��0�Ͳ�����´���Ӱ��
     bitnum++; //��ͣ�ظ��������������
  
   if(bitnum==33)//���bitmun=33��˵��һ֡���ݴ���
    {
     bitnum=0;//bitnum��0Ϊ������һ֡��׼��
     irreceok=1;//������ֻҪ�ж�irreceok�Ƿ�Ϊ1��������ľ���
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
003	#define uchar unsigned  char     // �궨��uchar Ϊ�޷����ַ� 
004	#define uint  unsigned  int   
005	      
006	#define IR_UserCode 0xFF00          //����ң���� �û���  
007	uchar IR_Code[32] = {0}; 
008	uchar IR_User[16] = {0};  //�û��� 
009	uchar IR_Data[8]  = {0};  //������ 
010	uchar IR_CData[8] = {0};  //���ݷ��� 
011	uchar key= '0',value = 0; //key LCD��ʾֵ; value  ����ͷ���յ�ֵ��16���ƣ� 
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
038	        case State_0 :              //��������� 
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
054	                    ScanState = State_2;        //Ϊ������ 
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
065	        case State_1:                      // 32λ���ݽ��� 
066	        { 
067	  
068	            while(i < 32){ 
069	                while(IR_DQ == 0); 
070	                delay(60);                  //��ʱ0.48ms 
071	                      
072	                if(IR_DQ == 1) 
073	                IR_Code[i] = 0; 
074	  
075	                delay(28);                  //��ʱ0.22ms,����ʱ0.70ms 
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
090	        case State_2:                       //�����봦�� 
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
105	        IR_User[n] = IR_Code[n];      //��λ�û��� 
106	        IR_User[8+n] = IR_Code[8+n];  //��λ�û��� 
107	        IR_Data[n] = IR_Code[16+n]; 
108	        IR_CData[n] = IR_Code[24+n]; 
109	        if(IR_Data[n] + IR_CData[n] == 0x01){ check++;}    //������,������ԭ��Ͳ��� ��λ��Ӻ�Ϊ 0x01 
110	    } 
111	    for(n=0;n<16;n++)                       //�����û��� 
112	    { 
113	        if(n==0) 
114	        { 
115	            user = IR_User[0]; 
116	        }else{ 
117	            user += IR_User[n] * (2 << (n-1)); 
118	        } 
119	    } 
120	    if((user == IR_UserCode) && (check == 8))      //�û���У�� ����У�� 
121	    { 
122	        for(n=0;n<8;n++)                //����������,������ת��Ϊ16���� 
123	        { 
124	            if(n==0) 
125	            { 
126	                value = IR_Data[0]; 
127	            }else{ 
128	                value += IR_Data[n] * (2 << (n-1)); 
129	            } 
130	        } 
131	        IR_Decode(); 
132	        LCD_WriteByte(0xC7,0);         //���½���ֵ 
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
157	    while(--n);             // 8usһ�� 
158	}
*/