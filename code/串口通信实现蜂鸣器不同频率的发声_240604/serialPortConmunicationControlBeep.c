#include <reg51.h>


int main()
{
	//���ô��пڵĹ�����ʽ�Լ�ʹ�ܽ��չ���   ��ʽ1
	SCON = 0x50;   //SM0 = 0 SM1 = 1 REN =1
	
	//���ò�����  9600
	PCON = 0x80;   //SMOD = 0
	TH1 = 0xFD;
	TL1 = 0xFD;
	
	//�򿪶�ʱ��T1��������ʽΪ��ʽ2��8λ�Զ���װ��
	TR1 = 1;  //������ʱ��
	
	
	
	while(1)
	{
		while(!RI);
		
		P1 = SBUF;
		
		RI = 0;  //�رս����жϱ�־λ
	
	}
	return 0;
}