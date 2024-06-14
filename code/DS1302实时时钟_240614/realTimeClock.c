#include <reg51.h>
#include <stdio.h>

#include "DS1302.h"
#include "LCD1602.h"

uint hexTransformDec(uchar hex);

char code *weekList[] = {"Mon. ", "Tues.", "Wed. ", "Thur.", "Fri. ", "Sta. ", "Sun. "}; 

int main()
{
	uchar dat = 0;
	char time[10] = {0};
	char week[7 ] = {0};
	char date[12] = {0};
	
	DS1302Init();
	lcd1602Init();
	
	while(1)
	{
		readTime();
	
		//序列化
		sprintf(time, "%.2d:%.2d:%.2d", hexTransformDec(ds1302Read[2]), hexTransformDec(ds1302Read[1]),hexTransformDec(ds1302Read[0]));
		sprintf(week, "%s", weekList[hexTransformDec(ds1302Read[5])-1]);
		sprintf(date, "20%.2d-%.2d-%.2d", hexTransformDec(ds1302Read[6]), hexTransformDec(ds1302Read[4]),hexTransformDec(ds1302Read[3]));
		
		lcdDisplatString(1, 1, date);
		lcdDisplatString(12, 1, week);
		lcdDisplatString(1, 2, time);
	}
	return 0;
}

/*******************************************************************************
* 函 数 名       : hexTransformDec
* 函数功能		 		 : 将十六进制转换成十进制
* 输    入       : hex:十六进制
* 输    出    	 : 无
*******************************************************************************/
uint hexTransformDec(uchar hex)
{
	uint dat = 0;
	dat = (hex/16)*10 + (hex&0x0f);
	return dat;
}