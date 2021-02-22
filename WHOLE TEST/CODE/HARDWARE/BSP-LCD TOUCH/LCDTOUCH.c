#ifndef __ZHANGTYPE_H__
#define __ZHANGTYPE_H__
#define uint8    unsigned char
#define uint16   unsigned short int
#define uint32   unsigned long int
#define int8     signed char
#define int16    signed short int
#define int32    signed long int
#define uint64   unsigned long long int
#define int64    signed long long int
#endif 

#ifndef __FUN_H__
#define __FUN_H__ 
#include "ZhangType.h"
#include"Delay.h"  
void Delay(uint16 time); 
#endif 

#include "fun.h" 
extern void Delay();

#ifndef __1602_H__
#define __1602_H__
#include "STC.h"
#include "ZhangType.h"          //��������
#include "fun.h"            //���ú��� 
#define SETMODE    0x38          //16*2��ʾ,5*7����,8λ���ݽӿ�
#define DISOPEN   0x0C          //��ʾ��,����ʾ���,��겻��˸
#define DISMODE   0x06          //��д�ַ����ַ��1,���Բ��ƶ�
#define SETADDR    0x80          //�������ݵ�ַָ���ʼֵ
#define CLEAR 0x01          //����,����ָ������
#define RET       0x02          //�س�,����ָ������ 
#define PORT  P2            //I/O�� 
sbit RS = P1^0;
sbit RW = P1^1;
sbit E = P1^2; 
void Init1602(void);        //��ʼ��1602
void Write1602_Com(uint8 com);  //д����
void Write1602_Dat(uint8 dat);  //д����
void CheckBusy(void);           //���æ
void Write1602_One_Dat(uint8 X,uint8 Y,uint8 dat);          //дһ������
void Write1602_Str(uint8 addr,uint8 length,uint8 *pbuf);    //дһ�����ݴ� 
#endif//

#include "1602.h" 
void Write1602_Com(uint8 com)
{
    E=0;
    RS=0;                    //����
    Delay(50);               //��ʱ
    RW=0;                    //д         
    Delay(50);
    PORT=com;                //�˿ڸ�ֵ
    Delay(50);
    E=1;                     //������
    Delay(50);
    E=0;
}

void Write1602_Dat(uint8 dat)
{
    E=0;
    RS=1;                    //����
    Delay(50);               //��ʱ
    RW=0;                    //д
    Delay(50);
    PORT=dat;                //�˿ڸ�ֵ
    Delay(50);
    E=1;                     //������
    Delay(50);
    E=0;
} 

void CheckBusy(void)
{
    uint8 temp;
    RS=0;                    //����
    RW=1;                    //��
    E=0;
    while(1)
    {
       PORT=0xFF;           //�˿�Ϊ����
       E=1;                 //������
       temp=PORT;
       E=0;
       if ((temp&0x80)==0)      //���BFλ�Ƿ�Ϊ0
       break;
    }
} 

void Init1602(void)
{
    Write1602_Com(SETMODE);     //ģʽ����
    Delay(500);
    Write1602_Com(DISOPEN);     //��ʾ����
    Delay(500);
    Write1602_Com(DISMODE);     //��ʾģʽ
    Delay(500);
    Write1602_Com(CLEAR);       //����
    Delay(500);
} 
 
void Write1602_One_Dat(uint8 x,uint8 y,uint8 dat)
{
    x&=0x0f;
    y&=0x01;
    if(y)
    x|=0x40;
    x|=0x80;
    Write1602_Com(x);
    Write1602_Dat(dat);
} 

void Write1602_Str(uint8 addr,uint8 length,uint8 *pbuf)
{
    uint8 i; 
    Write1602_Com(addr);
    for(i=0;i<8;i++)
    {
       Write1602_Dat(pbuf[i]);
    }
} 

/*******************************************************
*����:���ļ�(_main.c)
*����:����
*����:2014/09/09
*******************************************************/
#include "1602.h"
#include "fun.h" 
uint8 code hot[8]={0x10,0x06,0x09,0x08,0x08,0x09,0x06,0x00};
uint8 code pi[8]={0x00,0x1f,0x0a,0x0a,0x0a,0x13,0x00,0x00}; 
uint8 code strMCU[]="I love MCU!";
uint8 code strTest[]="LCD1602 Test!";
uint8 code blog[]="Welcome to my blog!"; 
uint8 i; 
void main()
{
    Init1602();              //��ʼ��1602 //�Զ���CGRAM
    Write1602_Str(0x40,8,hot);                       //�����±�
    Write1602_Str(0x48,8,pi);                        //pai
    Write1602_Str(0x80,strlen(strMCU),strMCU);           //"I love MCU!"
    Write1602_Str(0x80+0x40,strlen(strTest),strTest);    //"LCD1602 Test!"
    for(i=0;i<50;i++)                             //��ʱһ��ʱ��
    Delay(10000);
    Write1602_Com(CLEAR);                            //ָ��ִ��ʱ��ϳ�
    Delay(500);                                      //���һЩ��ʱ
    for(i=0;i<16;i++)
    Write1602_Dat(0);
    Write1602_Com(0xc0);                          //����DDRAM��ַ
    for(i=0;i<16;i++)
    Write1602_Dat(1);
    for(i=0;i<50;i++)                             //��ʱһ��ʱ��
    Delay(10000);
    Write1602_Com(CLEAR);                            //ָ��ִ��ʱ��ϳ�
    Delay(500);                                      //���һЩ��ʱ
    Write1602_Str(0x80+0x10,strlen(blog),blog);          //д����ʾ֮��
    while(1)
    {
       Write1602_Com(0x18);                      //��
       for(i=0;i<20;i++)                         //��ʱ
       Delay(10000);
    }

} 

