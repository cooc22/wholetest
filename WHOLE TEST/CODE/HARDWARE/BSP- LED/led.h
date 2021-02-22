#ifndef __LED_H__
#define __LED_H__


#include "delay.h"
#include "stc89.h"   //stc51系列单片机定义文件
#define LED P1  //不能在头文件里面定义变量!我们不在头文件中定义变量。如果一个变量需要被多个C文件使用，就采用在C文件中定义的方式，并在这个C文件的对应头文件中加extern声明。
  
extern void LED_Init();
extern void oneled();
extern void back_oneled();
extern void stopled();
extern void runninghorse();
extern void back_runninghorse();
extern void flowingwater();
extern void back_flowingwater();



#endif