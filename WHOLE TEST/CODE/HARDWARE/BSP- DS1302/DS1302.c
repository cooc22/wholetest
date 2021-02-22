/*
 功    能：实时时钟模块           时钟芯片型号：DS1302 
*/
#include"stc89.h"
#include"ds1302.h"
sbit     T_CLK      = P2^7;   /*实时时钟时钟线引脚 */
sbit     T_IO       = P1^4;   /*实时时钟数据线引脚 */
sbit     T_RST      = P1^5;   /*实时时钟复位线引脚 */
sbit  ACC0 ;
sbit  ACC7 ;
void   RTInputByte(uchar);       /* 输入 1Byte */
uchar  RTOutputByte(void);       /* 输出?1Byte */
void   W1302(uchar, uchar);
uchar  R1302(uchar);
void   Set1302(uchar *);         /* 设置时间 */
void   Bcd2asc(uchar,uchar *);
void   Get1302(uchar curtime[]); /* 读取1302当前时间 */
/******************************************************************** 
 函 数 名：RTInputByte()
 功    能：实时时钟写入一字节
 说    明：往DS1302写入1Byte数据 (内部函数)
 入口参数：d 写入的数据 
 返 回 值：无  
***********************************************************************/
void RTInputByte(uchar d) 
{ 
    uchar i;
    ACC = d;
    for(i=8; i>0; i--)
    {
        T_IO = ACC0;           /*相当于汇编中的 RRC */
        T_CLK = 1;
        T_CLK = 0;
        ACC = ACC >> 1; 
    } 
}
/******************************************************************** 
 函 数 名：RTOutputByte()
 功    能：实时时钟读取一字节
 说    明：从DS1302读取1Byte数据 (内部函数)
 入口参数：无  
 返 回 值：ACC
***********************************************************************/
uchar RTOutputByte(void) 
{ 
    uchar i;
    for(i=8; i>0; i--)
    {
        ACC = ACC >>1;         /*相当于汇编中的 RRC */
        ACC7 = T_IO;
        T_CLK = 1;
        T_CLK = 0;
    } 
    return(ACC); 
}
/******************************************************************** 
 函 数 名：W1302()
 功    能：往DS1302写入数据
 说    明：先写地址，后写命令/数据 (内部函数)
 调    用：RTInputByte() , RTOutputByte()
 入口参数：ucAddr: DS1302地址, ucData: 要写的数据
 返 回 值：无
***********************************************************************/
void W1302(uchar ucAddr, uchar ucDa)
{
    T_RST = 0;
    T_CLK = 0;
    T_RST = 1;
    RTInputByte(ucAddr);       /* 地址，命令 */
    RTInputByte(ucDa);       /* 写1Byte数据*/
    T_CLK = 1;
    T_RST = 0;
} 
/******************************************************************** 
 函 数 名：R1302()
 功    能：读取DS1302某地址的数据
 说    明：先写地址，后读命令/数据 (内部函数)
 调    用：RTInputByte() , RTOutputByte()
 入口参数：ucAddr: DS1302地址
 返 回 值：ucData :读取的数据
***********************************************************************/
uchar R1302(uchar ucAddr)
{
    uchar ucData;
    T_RST = 0;
    T_CLK = 0;
    T_RST = 1;
    RTInputByte(ucAddr);             /* 地址，命令 */
    ucData = RTOutputByte();         /* 读1Byte数据 */
    T_CLK = 1;
    T_RST = 0;
    return(ucData);
}
/******************************************************************** 
 函 数 名：BurstW1302T()
 功    能：往DS1302写入时钟数据(多字节方式)
 说    明：先写地址，后写命令/数据
 调    用：RTInputByte() 
 入口参数：pWClock: 时钟数据地址 格式为: 秒 分 时 日 月 星期 年 控制
                            8Byte (BCD码)1B 1B 1B 1B 1B  1B  1B 1B
 返 回 值：无
***********************************************************************/
void BurstW1302T(uchar *pWClock)
{
    uchar i;
    W1302(0x8e,0x00);         /* 控制命令,WP=0,写操作?*/
    T_RST = 0;
    T_CLK = 0;
    T_RST = 1;
    RTInputByte(0xbe);        /* 0xbe:时钟多字节写命令 */
    for (i = 8; i>0; i--)     /*8Byte = 7Byte 时钟数据 + 1Byte 控制*/
    {
        RTInputByte(*pWClock); /* 写1Byte数据*/
        pWClock++;
    }
    T_CLK = 1;
    T_RST = 0;
} 
/******************************************************************** 
 函 数 名：BurstR1302T()
 功    能：读取DS1302时钟数据
 说    明：先写地址/命令，后读数据(时钟多字节方式)
 调    用：RTInputByte() , RTOutputByte()
 入口参数：pRClock: 读取时钟数据地址 格式为: 秒 分 时 日 月 星期 年
                               7Byte (BCD码)1B 1B 1B 1B 1B  1B  1B
 返 回 值：无
***********************************************************************/
void BurstR1302T(uchar *pRClock)
{
    uchar i;
    T_RST = 0;
    T_CLK = 0;
    T_RST = 1;
    RTInputByte(0xbf);             /* 0xbf:时钟多字节读命令 */
    for (i=8; i>0; i--) 
    {
       *pRClock = RTOutputByte();   /* 读1Byte数据 */
       pRClock++;
    }
    T_CLK = 1;
    T_RST = 0;
}
/******************************************************************** 
 函 数 名：BurstW1302R()
 功    能：往DS1302寄存器数写入数据(多字节方式)
 说    明：先写地址，后写数据(寄存器多字节方式)
 调    用：RTInputByte()
 入口参数：pWReg: 寄存器数据地址
 返 回 值：无
***********************************************************************/
void BurstW1302R(uchar *pWReg)
{
    uchar i;
    W1302(0x8e,0x00);         /* 控制命令,WP=0,写操作*/
    T_RST = 0;
    T_CLK = 0;
    T_RST = 1;
    RTInputByte(0xfe);         /* 0xbe:时钟多字节写命令 */
    for (i=31; i>0; i--)       /* 31Byte 寄存器数据 */
    {
        RTInputByte(*pWReg);    /* 写1Byte数据*/
        pWReg++;
    }
    T_CLK = 1;
    T_RST = 0;
} 
/******************************************************************** 
 函 数 名：BurstR1302R()
 功    能：读取DS1302寄存器数据
 说    明：先写地址，后读命令/数据(寄存器多字节方式)
 调    用：RTInputByte() , RTOutputByte()
 入口参数：pRReg: 寄存器数据地址
 返 回 值：无
***********************************************************************/
void BurstR1302R(uchar *pRReg)
{
    uchar i;
    T_RST = 0;
    T_CLK = 0;
    T_RST = 1;
    RTInputByte(0xff);            /* 0xff:时钟多字节读命令 */
    for (i=31; i>0; i--)          /*31Byte 寄存器数据 */
    {
        *pRReg = RTOutputByte();  /* 读1Byte数据 */
        pRReg++;
    }
    T_CLK = 1;
    T_RST = 0;
}
/******************************************************************** 
 函 数 名：Set1302()
 功    能：设置初始时间
 说    明：先写地址，后读命令/数据(寄存器多字节方式)
 调    用：W1302()
 入口参数：pClock: 设置时钟数据地址 格式为: 秒 分 时 日 月 星期 年
                               7Byte (BCD码)1B 1B 1B 1B 1B  1B  1B
 返 回 值：无
***********************************************************************/
void Set1302(uchar *pClock) 
{
    uchar i;
    uchar ucAddr = 0x80; 
    W1302(0x8e,0x00);           /* 控制命令,WP=0,写操作?*/
    for(i =7; i>0; i--)
    { 
        W1302(ucAddr,*pClock);  /* 秒 分 时 日 月 星期 年 */ 
        pClock++;
        ucAddr +=2;
    }
    W1302(0x8e,0x80);           /* 控制命令,WP=1,写保护?*/
}
/******************************************************************** 
 函 数 名：Get1302()
 功    能：读取DS1302当前时间
 说    明：
 调    用：R1302() 
 入口参数：ucCurtime: 保存当前时间地址。当前时间格式为: 秒 分 时 日 月 星期 年 
                                        7Byte (BCD码)   1B 1B 1B 1B 1B  1B  1B
***********************************************************************/
void Get1302(uchar ucCurtime[]) 
{
    uchar i;
    uchar ucAddr = 0x81;
    for (i=0; i<7; i++)
    {
        ucCurtime[i] = R1302(ucAddr);/*格式为: 秒 分 时 日 月 星期 年 */
        ucAddr += 2;
    }
}