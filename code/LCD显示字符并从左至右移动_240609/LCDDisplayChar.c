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
	//while((readLCDState() & 0x80) != 0);  //���Һ����ʾ���Ƿ���æ��״̬ P0^7 = 1æ��P0^7 = 0����

	writeLCDCommand(0x38);  //������������Ϊ8λ����ʾ2�У�ÿ�е��ַ���СΪ5*7
	//writeLCDCommand(0x02);  //���ù�곷�ص���ʾ�����Ϸ�
	writeLCDCommand(0x06);  //д�������ݹ�����ƣ���ʾ�����ƶ�	
	writeLCDCommand(0x0E);  //��ʾ���ܴ򿪣��й�꣬��겻��˸
	//writeLCDCommand(0x14);  //�������һ����ACֵ��1
	writeLCDCommand(0x01);  //����
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


	