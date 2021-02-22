#ifndef _DS1302_H_
#define _DS1302_H_

unsigned char check_RTC(void);//检测DS1302
void init_RTC(char *init_data);//初始化DS1302
void read_date(char *s_cur_date);//读取当前时间并解释

#endif  /* _DS1302_H_ */
