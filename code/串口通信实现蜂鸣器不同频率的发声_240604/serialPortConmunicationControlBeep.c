#include <reg51.h>


int main()
{
	//设置串行口的工作方式以及使能接收功能   方式1
	SCON = 0x50;   //SM0 = 0 SM1 = 1 REN =1
	
	//设置波特率  9600
	PCON = 0x80;   //SMOD = 0
	TH1 = 0xFD;
	TL1 = 0xFD;
	
	//打开定时器T1，工作方式为方式2（8位自动重装）
	TR1 = 1;  //启动定时器
	
	
	
	while(1)
	{
		while(!RI);
		
		P1 = SBUF;
		
		RI = 0;  //关闭接收中断标志位
	
	}
	return 0;
}