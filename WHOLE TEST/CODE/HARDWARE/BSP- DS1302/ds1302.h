#ifndef _DS1302_H_
#define _DS1302_H_

unsigned char check_RTC(void);//���DS1302
void init_RTC(char *init_data);//��ʼ��DS1302
void read_date(char *s_cur_date);//��ȡ��ǰʱ�䲢����

#endif  /* _DS1302_H_ */
