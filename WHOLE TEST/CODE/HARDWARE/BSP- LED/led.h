#ifndef __LED_H__
#define __LED_H__


#include "delay.h"
#include "stc89.h"   //stc51ϵ�е�Ƭ�������ļ�
#define LED P1  //������ͷ�ļ����涨�����!���ǲ���ͷ�ļ��ж�����������һ��������Ҫ�����C�ļ�ʹ�ã��Ͳ�����C�ļ��ж���ķ�ʽ���������C�ļ��Ķ�Ӧͷ�ļ��м�extern������
  
extern void LED_Init();
extern void oneled();
extern void back_oneled();
extern void stopled();
extern void runninghorse();
extern void back_runninghorse();
extern void flowingwater();
extern void back_flowingwater();



#endif