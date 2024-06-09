#include <reg51.h>

sbit LCD_WR = P2^5;
sbit LCD_RS = P2^6;
sbit LCD_EN = P2^7;

#define LCD_DB P0

void delay_N_40us(int delayTime);
void LCDInit();
char readLCDState();
void writeLCDCommand(unsigned char cmd);
char readLCDData();
void writeLCDData(unsigned char dat);
void LCDDisplayChar(unsigned char x, unsigned char y, unsigned char dat);

int main()
{
	LCDInit();
	//LCDDisplayChar(1, 1, 0x41);
	//writeLCDCommand(0x84);
	writeLCDData(0x41);
	while(1)
	{
		
	}
	return 0;
}

void LCDInit()
{
	//while((readLCDState() & 0x80) != 0);  //检查液晶显示屏是否处于忙的状态 P0^7 = 1忙，P0^7 = 0空闲

	writeLCDCommand(0x38);  //设置数据总线为8位，显示2行，每行的字符大小为5*7
	//writeLCDCommand(0x02);  //设置光标撤回到显示器左上方
	writeLCDCommand(0x06);  //写入新数据光标右移，显示屏不移动	
	writeLCDCommand(0x0E);  //显示功能打开，有光标，光标不闪烁
	//writeLCDCommand(0x14);  //光标右移一格，且AC值加1
	writeLCDCommand(0x01);  //清屏
	delay_N_40us(100);
}

char readLCDState()
{
	LCD_RS = 0;
	LCD_WR = 1;
	LCD_EN = 1;
	delay_N_40us(1);
	return LCD_DB;
}

void writeLCDCommand(unsigned char cmd)
{
	LCD_RS = 0;
	LCD_WR = 0;
	LCD_EN = 0;
	LCD_DB = cmd;
	delay_N_40us(1);
	LCD_EN = 1;
	delay_N_40us(1);
	LCD_EN = 0;
	delay_N_40us(1);
}

char readLCDData()
{
	LCD_RS = 1;
	LCD_WR = 1;
	LCD_EN = 1;
	delay_N_40us(1);
	return LCD_DB;
}

void writeLCDData(unsigned char dat)
{
	LCD_RS = 1;
	LCD_WR = 0;
	LCD_EN = 0;
	LCD_DB = dat;
	delay_N_40us(1);
	LCD_EN = 1;
	delay_N_40us(1);
	LCD_EN = 0;
	delay_N_40us(1);
}

void LCDDisplayChar(unsigned char x, unsigned char y, unsigned char dat)
{
	if(y == 1)
		writeLCDCommand(0x80 + (x-1));
	else
		writeLCDCommand(0xC0 + (x-1));
	
	writeLCDData(dat);
	
}

void delay_N_40us(int delayTime)
{
	int i = 0;
	int j = 0;
	for(i = 0;i < delayTime;i++)
		for(j = 0;j < 5;j++ );
}


	