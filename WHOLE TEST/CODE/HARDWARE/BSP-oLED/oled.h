#ifndef _DS18B20_
#define _DS18B20_

void init_1820();
void write_1820(unsigned char x);
unsigned char read_1820();
unsigned char gettemp();//¶ÁÈ¡ÎÂ¶ÈÖµ
unsigned int get_temp(char num); 

#endif
