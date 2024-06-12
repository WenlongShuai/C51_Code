#include <reg51.h>
#include <stdio.h>

#include <LCD1602.h>

uint timer0Count = 0;
uint hour = 23;
uint minute = 59;
uint second = 0;
uint month = 1;
uint day = 30;
char *w = NULL;

char *weekList[] = {"Mon.", "Tues.", "Wed.", "Thur.", "Fri.", "Sta.", "Sun."};

char date[6] = {0};
char week[6] = {0};
char time[9] = {0};

void timer0Init();

int main()
{
	uchar i = 0;
	timer0Init();
	
	lcd1602Init();
	lcdDisplatString(1,1,"Da:");
	lcdDisplatString(9,1,"We:");
	lcdDisplatString(1,2,"time:");

	while(1)
	{
		if(timer0Count == 20)  //1s
		{
			timer0Count = 0;
			second++;
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

		sprintf(date,"%.2d.%.2d\0",month,day);
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
}
