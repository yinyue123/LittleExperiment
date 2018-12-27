#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
//========================== 定义单片机端口 ========================== 

sbit d1=P3^6; // 定义PWM

sbit d21=P2^1; // 按键1
sbit d22=P2^2; // 按键2
sbit d23=P2^3; // 按键3
sbit LE1=P2^7;
sbit A= P2^4;
sbit BB=P2^5;
sbit C= P2^6;
sbit OE = P3^0;
sbit EOC = P3^1;
sbit ST = P3^2;
sbit CLK = P3^3;
uint code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//=========================== 定义全局变量==========================
unsigned int t,tt,ttt,ca,order1,i,count;
//============================================================
unsigned int timer_init(float t)///fanshi 1 jingzhen 11.0592mhz
{ 
	unsigned int count,chuzhi;
	count=t*11.0592/12*1000;
	chuzhi=65536-count;
	return (chuzhi);	
}

//========================== 延时子程序 ============================


void delay_50us(uint t)
{	
	uchar j;	
	for(;t>0;t--)		
		for(j=19;j>0;j--);		
}


void init() {	
	P0=0xff; 
	P2=0xff;
}

void display(uchar a,uchar b,uchar c,uchar d) 
{
	LE1=1; //选通hc573	
	//分别依次选通数码管的位选端 
	A=0; BB=0; C=0;
	P0=table[a]; delay_50us(20); A=1; BB=0; C=0;
	P0=table[b]; delay_50us(20); A=0; BB=1; C=0;
	P0=table[c]; delay_50us(20); A=1; BB=1; C=0;
	P0=table[d]; delay_50us(20); 
	P0=0x00; 
	LE1=0; 
}
void fenzhi(uint n) {	
	uint t;
	uchar t1,t2,t3,t4;
	t=500+2000/255.0*n; 
	if(ttt!=t)
	{
		ca=t;
		ttt=t;
	}
	if(d21==0)	
	{ 
		delay_50us(1000); 
		if(d21==0&&ca<2500) 
			ca+=100; 
		while(!d21);
	} 
	if(d22==0)	
	{ 
		delay_50us(1000); 
		if(d22==0&&ca>500)
			ca-=100; 
		while(!d22); 
	} 
	if(d23==0)
	{ 
		delay_50us(1000);
		if(d23==0)
			ca=1500;
		
		while(!d23); 
	} 
	t1=ca/1000;
	t2=ca/100%10;
	t3=ca%100/10;
	t4=ca%10;
	display(t1,t2,t3,t4);
}

void main() 
{
	P1=00;
	TMOD = 0x12; 
	TH0 = 0x14; 
	TL0 = 0x14; 
	TH1=0xff;
	TL1=0xfe;
	t=tt=0xfe33; 
	order1=1; 
	TR0 = 1; 
	TR1=1;
	
	IE = 0x8a; 
	P3 = 0x3f; 
	init(); 
	while(1)
	{
		tt=timer_init(ca/1000.0);
		ST = 0; 
		ST = 1; 
		ST = 0;
		while(EOC == 0); 
		OE = 1;
		
		fenzhi(P1);
	} 
}

void Timer0_INT() interrupt 1 
{
	
	CLK = !CLK; 
}

void timer1(void) interrupt 3 
{
	switch( order1) 
	{ 
	case 1:
		if(t<65536)
			d1=1;
		
		TH1=t>>8; 
		TL1=t&0x00ff; 
		break;
		
	case 2:
		d1=0;
		
		TH1=(65536-t+0xb800)>>8;
		
		TL1=(65536-t+0xb800)&0x00ff; 
		order1=0; 
		t=tt;
		break; 
	default :
		
		order1=0;
	} order1++;
}
