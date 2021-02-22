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
#include "ZhangType.h"          //变量类型
#include "fun.h"            //常用函数 
#define SETMODE    0x38          //16*2显示,5*7点阵,8位数据接口
#define DISOPEN   0x0C          //显示开,不显示光标,光标不闪烁
#define DISMODE   0x06          //读写字符后地址加1,屏显不移动
#define SETADDR    0x80          //设置数据地址指针初始值
#define CLEAR 0x01          //清屏,数据指针清零
#define RET       0x02          //回车,数据指针清零 
#define PORT  P2            //I/O口 
sbit RS = P1^0;
sbit RW = P1^1;
sbit E = P1^2; 
void Init1602(void);        //初始化1602
void Write1602_Com(uint8 com);  //写命令
void Write1602_Dat(uint8 dat);  //写数据
void CheckBusy(void);           //检查忙
void Write1602_One_Dat(uint8 X,uint8 Y,uint8 dat);          //写一个数据
void Write1602_Str(uint8 addr,uint8 length,uint8 *pbuf);    //写一个数据串 
#endif//

#include "1602.h" 
void Write1602_Com(uint8 com)
{
    E=0;
    RS=0;                    //命令
    Delay(50);               //延时
    RW=0;                    //写         
    Delay(50);
    PORT=com;                //端口赋值
    Delay(50);
    E=1;                     //高脉冲
    Delay(50);
    E=0;
}

void Write1602_Dat(uint8 dat)
{
    E=0;
    RS=1;                    //数据
    Delay(50);               //延时
    RW=0;                    //写
    Delay(50);
    PORT=dat;                //端口赋值
    Delay(50);
    E=1;                     //高脉冲
    Delay(50);
    E=0;
} 

void CheckBusy(void)
{
    uint8 temp;
    RS=0;                    //命令
    RW=1;                    //读
    E=0;
    while(1)
    {
       PORT=0xFF;           //端口为输入
       E=1;                 //高脉冲
       temp=PORT;
       E=0;
       if ((temp&0x80)==0)      //检查BF位是否为0
       break;
    }
} 

void Init1602(void)
{
    Write1602_Com(SETMODE);     //模式设置
    Delay(500);
    Write1602_Com(DISOPEN);     //显示设置
    Delay(500);
    Write1602_Com(DISMODE);     //显示模式
    Delay(500);
    Write1602_Com(CLEAR);       //清屏
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
*名称:主文件(_main.c)
*功能:测试
*日期:2014/09/09
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
    Init1602();              //初始化1602 //自定义CGRAM
    Write1602_Str(0x40,8,hot);                       //摄氏温标
    Write1602_Str(0x48,8,pi);                        //pai
    Write1602_Str(0x80,strlen(strMCU),strMCU);           //"I love MCU!"
    Write1602_Str(0x80+0x40,strlen(strTest),strTest);    //"LCD1602 Test!"
    for(i=0;i<50;i++)                             //延时一段时间
    Delay(10000);
    Write1602_Com(CLEAR);                            //指令执行时间较长
    Delay(500);                                      //多加一些延时
    for(i=0;i<16;i++)
    Write1602_Dat(0);
    Write1602_Com(0xc0);                          //设置DDRAM地址
    for(i=0;i<16;i++)
    Write1602_Dat(1);
    for(i=0;i<50;i++)                             //延时一段时间
    Delay(10000);
    Write1602_Com(CLEAR);                            //指令执行时间较长
    Delay(500);                                      //多加一些延时
    Write1602_Str(0x80+0x10,strlen(blog),blog);          //写在显示之外
    while(1)
    {
       Write1602_Com(0x18);                      //左
       for(i=0;i<20;i++)                         //延时
       Delay(10000);
    }

} 

