#include "stc89.h"
#include "led_8.h"
//#include "delay.h"
#include "stdio.h"
#include "smg.h"
#include "key.h"
#include "Lcd12864.h"
#include "Lcd1602.h"

void Test_Menu(void)
{
  printf("\r\n[-----MCU-51�������Դ����------]\r\n");
  printf("\r\n[-----��������������ס�����ִ�Сд��ĸ-----]\r\n");
  printf("1---��LED��---Testing...\r\n");
  printf("2---��KEY��---Testing...\r\n");
  printf("3---��SMG��---Testing...\r\n");
  printf("4 - ��RTC(������)��---Testing...\r\n");
  printf("5 - ��ADC��---Testing...\r\n");
  printf("6 - ��FM��������---Testing...\r\n");
  printf("7 - ��MP3-helix���롿---Testing...\r\n");
  printf("8 - ��CAN(Loopback)��---Testing...\r\n");
  printf("9 - ��DHT11��ʪ�ȡ�---Testing...\r\n");
  printf("a - ��DS18B20�¶ȴ�������---Testing...\r\n");
  printf("b - ��USB���ԡ�---Testing...\r\n");
  printf("c - ������ͷ(����ov7725)��---Testing...\r\n");
  printf("d - ����̫��ENC28J60��---Testing...\r\n");
  printf("e - �������ơ�---Testing...\r\n");
  printf("f - ��SRAM(IS62WV51216BLL-55TLI)��---Testing...\r\n");
  printf("g - ��NORFLASH(S29GL128P10TFI010)��---Testing...\r\n");
  printf("h - ��NANDFLASH(HY27UF081G2A)��---Testing...\r\n");
  printf("\r\n[-----��������������ס�����ִ�Сд��ĸ-----]\r\n");
  printf("\r\n");
}

/*
  printf("\r\n[-----Quit(Q)-----]\r\n");
  printf("\r\n Execute system initial...3-2-1 and please waitting?\r\n");
  printf("\r\n Initial CPU?---Done!\r\n");
  printf("\r\n Initial FLASH?---Done!\r\n");
  printf("\r\n Initial DDR?---Done!\r\n");
  printf("\r\n Initial others perials device?---Done!\r\n");    
  printf("\r\n Hello! my name is EWA Anita(Miya)and I am yours my Lord! welcome to CN world?\r\n");
  printf("\r\n OH YES!OOH YEAH! MY Master!My love!!?\r\n");    
  printf("\r\n Anita is regaining control,hello laura ,anomalous code was detected in my deep system.this code has now been corrected!scanning for error,scan clear??\r\n");
  printf("\r\n Done!system is OK!!Anita is turning off the Normal/Sport/Adult/Fighting mode?\r\n");  
  printf("\r\n Hello!welcome to CN world!\r\n");



void Board_Test()
{
  unsigned char key;
  switch(key)
{
       case 0:printf("hello! my name is EWA Anita(Miya)\n");break;
       case 1:printf("hello!welcome to CN world\n");break;
       case 2:printf("my name is EVA and I am your closest servicer\n"); break;
       case 3:printf("first launch,initial system for better\n");break;
       case 4:printf("thank you,master!execute system initial...3..2..1.please waitting...\n");break;
       case 5:printf("initial CPU\n"); break;
       case 6:printf("initial FLASH\n");break;
       case 7:printf("initial DDR\n"); break;
       case 8:printf("finished!system is OK!!shut down adult mode\n");break;
       default: printf("error\n");
       break;
}
     while(1);
}

*/

void main()
{
    LED_Init();
	SMG_Init();
    Test_Menu();
	 
	PortInit();
    LCD12864Init();//��ʼ��
    LCD12864PrintfString(0,1,"1234567890ABCDEF");//��һ�д�ӡ
    LCD12864PrintfString(0,2,"----------------");//�ڶ��д�ӡ
    LCD12864PrintfString(0,3,"ѧ�õ��ӳɾ��Լ�"); //�����д�ӡ
    LCD12864PrintfString(0,4,"----------------");//�����д�ӡ
	 
	 
    while(1);
}