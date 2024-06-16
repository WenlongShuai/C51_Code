#include <reg51.h>
#include <stdio.h>

#include "DS1302.h"
#include "LCD1602.h"
#include "keyScanAdjustmentTime.h"

uint hexTransformDec(uchar hex);

//uchar time[10] = {0};
//uchar week[7] = {0};
uchar date[12] = {0};

char code *weekList[] = {"Mon. ", "Tues.", "Wed. ", "Thur.", "Fri. ", "Sta. ", "Sun. "}; 

int main()
{
	uchar dat = 0;
	uchar key = 0;
	
	DS1302Init();
	lcd1602Init();
	
	while(1)
	{
		readTime();

		rtc[0] = hexTransformDec(ds1302Read[0]);  //秒
		rtc[1] = hexTransformDec(ds1302Read[1]); //分钟
		rtc[2] = hexTransformDec(ds1302Read[2]);  //小时
		rtc[5] = hexTransformDec(ds1302Read[5]);   //星期
		rtc[3] = hexTransformDec(ds1302Read[3]);   //天
		rtc[4] = hexTransformDec(ds1302Read[4]);  //月份
		rtc[6] = hexTransformDec(ds1302Read[6]);  //年
		
		key = detectKey();  //先判断是否有键按下，如果没键按下则不管
		if(key == 1)
		{
			adjustmentTime(key);
		}
		else
		{
			//序列化
			sprintf(date, "20%.2d-%.2d-%.2d", hexTransformDec(ds1302Read[6]), hexTransformDec(ds1302Read[4]),hexTransformDec(ds1302Read[3]));
			lcdDisplatString(1, 1, date);
			sprintf(date, "%s", weekList[hexTransformDec(ds1302Read[5])-1]);
			lcdDisplatString(12, 1, date);
			sprintf(date, "%.2d:%.2d:%.2d", hexTransformDec(ds1302Read[2]), hexTransformDec(ds1302Read[1]),hexTransformDec(ds1302Read[0]));
			lcdDisplatString(1, 2, date);
			
		}

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