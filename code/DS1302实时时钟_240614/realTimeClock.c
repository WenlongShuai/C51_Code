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

		rtc[0] = hexTransformDec(ds1302Read[0]);  //��
		rtc[1] = hexTransformDec(ds1302Read[1]); //����
		rtc[2] = hexTransformDec(ds1302Read[2]);  //Сʱ
		rtc[5] = hexTransformDec(ds1302Read[5]);   //����
		rtc[3] = hexTransformDec(ds1302Read[3]);   //��
		rtc[4] = hexTransformDec(ds1302Read[4]);  //�·�
		rtc[6] = hexTransformDec(ds1302Read[6]);  //��
		
		key = detectKey();  //���ж��Ƿ��м����£����û�������򲻹�
		if(key == 1)
		{
			adjustmentTime(key);
		}
		else
		{
			//���л�
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
* �� �� ��       : hexTransformDec
* ��������		 		 : ��ʮ������ת����ʮ����
* ��    ��       : hex:ʮ������
* ��    ��    	 : ��
*******************************************************************************/
uint hexTransformDec(uchar hex)
{
	uint dat = 0;
	dat = (hex/16)*10 + (hex&0x0f);
	return dat;
}