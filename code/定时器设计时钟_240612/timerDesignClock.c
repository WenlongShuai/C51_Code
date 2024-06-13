#include <reg51.h>
#include <stdio.h>

#include "LCD1602.h"

sbit KEY1 = P3^1;
sbit KEY2 = P3^0;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

uint timer0Count = 0;
int hour = 23;
int minute = 59;
int second = 0;
uint month = 1;
uint day = 30;
char i = 0;

char *weekList[] = {"Mon.", "Tues.", "Wed.", "Thur.", "Fri.", "Sta.", "Sun."};

char date[6] = {0};
char week[6] = {0};
char time[9] = {0};

uchar detectKey();
void detectTime();
void addSubTime(uchar operate);

void timer0Init();

int main()
{
	uchar key = 0;
	uchar count = 0;

	P3 = 0xff;
	timer0Init();
	
	lcd1602Init();
	lcdDisplatString(1,1,"Da:");
	lcdDisplatString(9,1,"We:");
	lcdDisplatString(1,2,"time:");

	while(1)
	{
		key = detectKey();
		if(key != 0)
		{
			while(key != 4)
			{		
				switch(key)
				{
					case 1:  //切换光标
						count++;
						if(count == 1)
						{
							lcd1602WriteCommand(0x14);  //设定显示屏或光标移动方向指令
							lcd1602WriteCommand(0x84);
						}
						else if(count == 2)
						{
							lcd1602WriteCommand(0x14);  //设定显示屏或光标移动方向指令
							lcd1602WriteCommand(0x87);
						}
						else if(count == 3)
						{
							lcd1602WriteCommand(0x14);  //设定显示屏或光标移动方向指令
							lcd1602WriteCommand(0x8F);
						}
						else if(count == 4)
						{
							lcd1602WriteCommand(0x14);  //设定显示屏或光标移动方向指令
							lcd1602WriteCommand(0xC6);
						}
						else if(count == 5)
						{
							lcd1602WriteCommand(0x14);  //设定显示屏或光标移动方向指令
							lcd1602WriteCommand(0xC9);
						}
						else if(count == 6)
						{
							lcd1602WriteCommand(0x14);  //设定显示屏或光标移动方向指令
							lcd1602WriteCommand(0xCC);					
							count = 0;
						}
						break;
					case 2:  //加1
						addSubTime('+');
						break;
					case 3:  //减一
						addSubTime('-');
						break;
				}
				key = detectKey();
			}
			count = 0;
		}
		
		sprintf(date,"%.2d:%.2d",month,day);
		lcdDisplatString(4,1,date);
		
		sprintf(week,"%s",weekList[i]);
		lcdDisplatString(12,1,week);
		
		sprintf(time,"%.2d:%.2d:%.2d",hour,minute,second);
		lcdDisplatString(6,2,time);
	}
	return 0;
}

void timer0Init()
{
	//打开总中断
	EA = 1;
	
	//打开定时器0的中断允许控制位
	ET0 = 1;
	
	//设置定时器0的工作方式
	TMOD = 0x01;
	
	//启动定时器0
	TCON = 0x10;
	
	//设置定时器初值
	TH0 = (65536 - 50000) / 256;  //50ms
	TL0 = (65536 - 50000) % 256;

}

void timer0() interrupt 1
{
	TH0 = (65536 - 50000) / 256;  //50ms
	TL0 = (65536 - 50000) % 256;
	timer0Count++;
	
	if(timer0Count == 20)  //1s
	{
		timer0Count = 0;
		second++;
		if(second == 60)
		{
			detectTime();
		}
	}
}

void detectTime()
{
	if(second == 60)
	{
		second = 0;
		minute++;
		if(minute == 60)
		{
			minute = 0;
			hour++;
			if(hour == 24)
			{
				hour = 0;
				day++;
				i++;
				if(i == 7)
				{
					i = 0;
				}
				if(day > 28)
				{
					if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)  //大月
					{
						if(day == 32)
						{
							if(month == 12)
							{	
								month = 1;
							}
							else
							{
								month++;
							}
							day = 0;
						}
					}
					else if(month == 4 || month == 6 || month == 9 || month == 11)
					{
						if(day == 31)
						{
							day = 0;
							month++;
						}
					}
					else
					{
						if(day == 30)
						{
							day = 0;
							month++;
						}
					}
				}
			}
		}
	}
}

uchar detectKey()
{
	uchar flag = 0;
	if(!KEY1)
	{
		delayMs(5);
		while(KEY1);
		flag = 1;
		delayMs(5);
		while(!KEY1);
	}
	else if(!KEY2)
	{
		delayMs(5);
		while(KEY2);
		flag = 2;
		delayMs(5);
		while(!KEY2);
	}
	else if(!KEY3)
	{
		delayMs(5);
		while(KEY3);
		flag = 3;
		delayMs(5);
		while(!KEY3);
	}
	else if(!KEY4)
	{
		delayMs(5);
		while(KEY4);
		flag = 4;
		delayMs(5);
		while(!KEY4);
	}
	
	return flag;
}


void addSubTime(uchar operate)
{
	uchar ac = 0;
	ac = lcd1602ReadState();
	P2 = ac;
	if(ac == 0x04)  //month
	{
//		if(operate == '+')
//		{
//			month++;
//			if(month == 13)
//			{
//				month = 1;
//			}
//		}
//		else
//		{
//			month--;
//			if(month == 0)
//			{
//				month = 12;
//			}
//		}
		month++;
		sprintf(date,"%.2d",month);
		lcdDisplatString(4,1,date);
		
	}
	else if(ac == 0x07)  //day
	{
//		if(operate == '+')
//		{
//			day++;
//			if(day > 28)
//			{
//				if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)  //大月
//				{
//					if(day == 32)
//					{
//						day = 0;
//					}
//				}
//				else if(month == 4 || month == 6 || month == 9 || month == 11)
//				{
//					if(day == 31)
//					{
//						day = 0;
//					}
//				}
//				else
//				{
//					if(day == 30)
//					{
//						day = 0;
//					}
//				}
//			}
//		}	
//		else
//		{
//			day--;
//			if(day == 0)
//			{
//				if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)  //大月
//				{
//					day = 31;
//				}
//				else if(month == 4 || month == 6 || month == 9 || month == 11)
//				{
//					day = 30;
//				}
//				else
//				{
//					day = 29;
//				}
//			}
//		}
		day++;
		sprintf(date,"%.2d",day);
		lcdDisplatString(7,1,date);
	}
	else if(ac == 0x0f)  //week
	{
//		if(operate == '+')
//		{
//			i++;
//			if(i == 7)
//			{
//				i = 1;
//			}
//		}
//		else
//		{
//			i--;
//			if(i == -1)
//			{
//				i = 6;
//			}
//		}
		i++;
		sprintf(week,"%s",weekList[i]);
		lcdDisplatString(12,1,week);
	}
	else if(ac == 0x46)  //hour
	{
//		if(operate == '+')
//		{
//			hour++;
//			if(hour == 24)
//			{
//				hour = 0;
//			}
//		}
//		else
//		{
//			hour--;
//			if(hour == -1)
//			{
//				hour = 23;
//			}
//		}
		hour++;
		sprintf(time,"%.2d",hour);
		lcdDisplatString(6,2,time);
	}
	else if(ac == 0x49)  //minute
	{
//		if(operate == '+')
//		{
//			minute++;
//			if(minute == 60)
//			{
//				minute = 0;
//			}
//		}
//		else
//		{
//			minute--;
//			if(minute == -1)
//			{
//				minute = 59;
//			}
//		}
		minute++;
		sprintf(time,"%.2d",minute);
		lcdDisplatString(9,2,time);
	}
	else if(ac == 0x4c) //second
	{
//		if(operate == '+')
//		{
//			second++;
//			if(second == 60)
//			{
//				second = 0;
//			}
//		}
//		else
//		{
//			second--;
//			if(second == -1)
//			{
//				second = 59;
//			}
//		}
		second++;
		sprintf(time,"%.2d",second);
		lcdDisplatString(12,2,time);
	}
	//lcd1602WriteCommand(ac | 0x80);
	//lcd1602WriteCommand(0x14);
}


