#ifndef _WDT_H_
#define _WDT_H_

void init_1820();
void write_1820(unsigned char x);
unsigned char read_1820();
unsigned char gettemp();//¶ÁÈ¡ÎÂ¶ÈÖµ
unsigned int get_temp(char num); 

#endif
