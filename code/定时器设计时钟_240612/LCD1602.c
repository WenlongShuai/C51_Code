#include <LCD1602.h>

static void delayUs(uint us);

void lcd1602Init()
{
	lcd1602WriteCommand(0x38);
	lcd1602WriteCommand(0x0E);
	lcd1602WriteCommand(0x06);
	lcd1602WriteCommand(0x01);
	delayMs(100);  //等待LCD初始化完成
}


//读状态 输入：RS=L，RW=H，E=H 输出：DB0～DB7=状态字 
uchar lcd1602ReadState()
{
	uchar lcdState = 0;
	
	lcd1602_RS = 0;
	lcd1602_WR = 1;
	lcd1602_EN = 1;
	lcdState = P0;
	delayUs(2);
	return lcdState;
}

//写指令 输入：RS=L，RW=L，E=下降沿脉冲，DB0～DB7=指令码 输出：无 
void lcd1602WriteCommand(uchar cmd)
{
	lcd1602_RS = 0;
	lcd1602_WR = 0;
	lcd1602_EN = 1;
	delayUs(2);
	P0 = cmd;
	lcd1602_EN = 0;
	delayUs(2);
}

//写数据 输入：RS=H，RW=L，E=下降沿脉冲，DB0～DB7=数据  输出：无
void lcd1602WriteData(uchar dat)
{
	lcd1602_RS = 1;
	lcd1602_WR = 0;
	lcd1602_EN = 1;
	delayUs(2);
	P0 = dat;
	lcd1602_EN = 0;
	delayUs(2);
}

//读数据 输入：RS=H，RW=H，E=H  输出：DB0～DB7=数据 
uchar lcd1602ReadData()
{
	uchar lcdReadData = 0;
	lcd1602_RS = 1;
	lcd1602_WR = 1;
	lcd1602_EN = 1;
	lcdReadData = P0;
	delayUs(2);
	return lcdReadData;
}

void lcdDisplayChar(unsigned char x, unsigned char y, unsigned char dat)
{
	if(y == 1)
		lcd1602WriteCommand(0x80 + (x-1));
	else
		lcd1602WriteCommand(0xC0 + (x-1));
	
	lcd1602WriteData(dat);
}


void lcdDisplatString(unsigned char x, unsigned char y, char *str)
{
	unsigned char address = 0;
	if(y == 1)
		address = 0x80 + (x-1);
	else
		address = 0xC0 + (x-1);
	
	while(*str != '\0')
	{
		lcd1602WriteCommand(address);
		lcd1602WriteData(*str);
		str++;
		address++;
		if(((address & 0x7F) > 0x0F) && (((address & 0x7F) < 0x27)))
		{
			address = 0xC0;
		}
		else if(((address & 0x7F) > 0x4F) && ((address & 0x7F) < 0x67))
		{
			address = 0x80;
		}
	}
}

void lcd1602Clear()
{
	lcd1602WriteCommand(0x01);
}

void delayMs(unsigned int ms)
{
	int i = 0;
	int j = 0;
	for(i = 0;i < ms;i++)
	{
		for(j = 0;j < 130;j++);
	}
}

//us=1,  3us
static void delayUs(uint us)
{
	while(us--);
}
