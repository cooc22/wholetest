 
 /*************************�˲���Ϊ18B20����������*************************************/

#include <reg52.H>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit D18B20=P3^7; // 18b20�����Ŷ���

sbit rs=P2^6;    //	 1602���Ŷ��� 
sbit rw=P2^5;
sbit e=P2^7;
#define  NOP()   _nop_()   /* �����ָ�� */
#define  _Nop()  _nop_()   /*�����ָ��*/

void TempDelay (uchar us);	//18b20�ĺ�������
void Init18b20 (void);
void WriteByte (uchar wr);  //���ֽ�д��
void read_bytes (uchar j);
uchar CRC (uchar j);
void GemTemp (void);
void TemperatuerResult(void);

void delay(uchar a);			//1602�ֺ�������
void lcd_mang();
void write_lcd1602(uchar cmd,uchar i);
void ini_lcd1602();


bit  flag;
uint Temperature;	//������Ŷ����¶Ⱥ��ֵ
uchar temp_buff[9]; //�洢��ȡ���ֽڣ�read scratchpadΪ9�ֽڣ�read rom IDΪ8�ֽ�
uchar *p,TIM;

/************************************************************
*Function:��ʱ����
*parameter:
*Return:
*Modify:
*************************************************************/
void TempDelay (uchar us)
{
	while(us--);
}

/************************************************************
*Function:18B20��ʼ��
*parameter:
*Return:
*Modify:
*************************************************************/
void Init18b20 (void)
{
	D18B20=1;
	_nop_();
	D18B20=0;
	TempDelay(80);   //delay 530 uS//80
	_nop_();
	D18B20=1;
	TempDelay(14);   //delay 100 uS//14
	_nop_();
	_nop_();
	_nop_();
	
	if(D18B20==0)
		flag = 1;   //detect 1820 success!
	else
		flag = 0;    //detect 1820 fail!
	TempDelay(20);       //20
	_nop_();
	_nop_();
	D18B20 = 1;
}

/************************************************************
*Function:��18B20д��һ���ֽ�
*parameter:
*Return:
*Modify:
*************************************************************/
void WriteByte (uchar wr)  //���ֽ�д��
{
	unsigned char idata i;
	for (i=0;i<8;i++)
	{
		D18B20 = 0;
		_nop_();
		D18B20=wr&0x01;
		TempDelay(3);   //delay 45 uS //5
		_nop_();
		_nop_();
		D18B20=1;
		wr >>= 1;
	}
}

/************************************************************
*Function:��18B20��һ���ֽ�
*parameter:
*Return:
*Modify:
*************************************************************/
unsigned char ReadByte (void)     //��ȡ���ֽ�
{
	unsigned char idata i,u=0;
	for(i=0;i<8;i++)
	{
		D18B20 = 0;
		u >>= 1;
		D18B20 = 1;
		if(D18B20==1)
		u |= 0x80;
		TempDelay (2);
		_nop_();
	}
	return(u);
}

/************************************************************
*Function:��18B20
*parameter:
*Return:
*Modify:
*************************************************************/
void read_bytes (uchar j)
{
	 unsigned char idata i;
	 for(i=0;i<j;i++)
	 {
		  *p = ReadByte();
		  p++;
	 }
}

/************************************************************
*Function:��ȡ�¶�
*parameter:
*Return:
*Modify:
*************************************************************/
void GemTemp (void)
{        
	    Temperature = temp_buff[1]*0x100 + temp_buff[0];
//	    Temperature *= 0.625;
		Temperature /= 16;
		TempDelay(1);
}

/************************************************************
*Function:18B20IDȫ����
*parameter:
*Return:
*Modify:
*************************************************************/
void TemperatuerResult(void)
{
	Init18b20 ();
	WriteByte(0xcc);   //skip rom
	WriteByte(0x44);   //Temperature convert

	Init18b20 ();
	WriteByte(0xcc);   //skip rom
	WriteByte(0xbe);   //read Temperature
	p = temp_buff;
	read_bytes (9);
	GemTemp();
}


void GetTemp()
{       
     if(TIM==100) //ÿ�� 1000ms ��ȡ�¶�
	{  TIM=0;
	   TemperatuerResult();
	}
}

/*************************************
 [ t1 (10ms)�ж�] �ж�
*************************************/
void T1zd(void) interrupt 3 
{
   TH1 = 0xD8;    //10
   TL1 = 0xF0;
   TIM++;

}
/************************************************************
 


   ������1602��ʾģ��




*************************************************************/
void delay(uchar a)
{
     uchar i;
     while(a--)
	   {
	      for(i=0;i<250;i++)
		    {
			   _nop_();
               _nop_();
			   _nop_();
               _nop_();  
			}
	   }   
}

 //��æ
 void lcd_mang()
{
   rs=0;
   rw=1;
   e=1;
   _nop_();
	_nop_();
	_nop_();
	_nop_();
   while(P0&0x80);
     e=0;
}

 //1602��д
void write_lcd1602(uchar cmd,uchar i)
{
    lcd_mang();
	rs=i;
	rw=0;
	e=0;
	_nop_();
	_nop_();	
	e=1; 
	_nop_();
	_nop_();
	P0=cmd; 
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	e=0;	
}

//1602�ĳ�ʼ��
void ini_lcd1602()
{
  write_lcd1602(0x38,0);
  delay(1);  
  write_lcd1602(0x0c,0);
  delay(1); 
  write_lcd1602(0x06,0);
  delay(1);
  write_lcd1602(0x01,0);
  delay(1);  
}
