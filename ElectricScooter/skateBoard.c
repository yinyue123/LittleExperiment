#include<reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
//========================== ���嵥Ƭ���˿� ========================== 
//sbit d1=P2^0; // ����PWM

sbit F_DOUT=P3^1;//ѹ��1
sbit F_SCK=P3^2;//ѹ��1

sbit B_DOUT=P3^3;//ѹ��2
sbit B_SCK=P3^4;//ѹ��2

sbit d1=P3^6; // ����PWM

sbit d21=P2^0; // ����1
sbit d22=P2^1; // ����2
sbit d23=P2^2; // ����3
sbit A= P2^4;
sbit BB= P2^5;
sbit C= P2^6;
sbit LE1=P2^7;


uint code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//=========================== ����ȫ�ֱ���==========================
unsigned long FBuffer = 0,BBuffer = 0, change = 0;
unsigned int t,tt,ttt,ca,order1,i,count,Fwight=0,Bwight=0,ii =0;
//============================================================

//****************************************************
//��ʱ����
//****************************************************
void Delay__hx711_us(void)
{
    _nop_();
    _nop_();
}

//****************************************************
//MS��ʱ����(12M�����²���)
//****************************************************
void Delay_ms(unsigned int n)
{
    unsigned int  i,j;
    for(i=0;i<n;i++)
        for(j=0;j<123;j++);
} 

//****************************************************
//��ȡHX711
//****************************************************
unsigned long F_Read(void)    //����128
{
    unsigned long count;
    unsigned char i;
      F_DOUT=1;
    Delay__hx711_us();
      F_SCK=0;
      count=0;
      while(F_DOUT);
      for(i=0;i<24;i++)
    {
          F_SCK=1;
          count=count<<1;
        F_SCK=0;
          if(F_DOUT)
            count++;
    }
     F_SCK=1;
    Delay__hx711_us();
    F_SCK=0;  
    return(count);
} 
/*{
	uint j;
	unsigned long ;
}*/
void FGetWeight()
{
    FBuffer = F_Read();
    FBuffer = FBuffer/100;

    Fwight = FBuffer;
    Fwight = Fwight;//��ȡʵ���AD������ֵ��
    
    Fwight = (unsigned int)((float)Fwight/2.15+0.05);    
	//����ʵ���ʵ������,��Ϊ��ͬ�Ĵ������������߲�һ������ˣ�ÿһ����������Ҫ���������2.15���������
    //�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��//������Գ���������ƫСʱ����С����ֵ��
    //������Գ���������ƫСʱ����С����ֵ��//����ֵһ����2.15��������֮�䡣�򴫸�����ͬ������
    //+0.05��Ϊ����������ٷ�λ        
    Fwight = Fwight/2;
}
/*
unsigned long B_Read(void)    //����128
{
    unsigned long count;
    unsigned char i;
      B_DOUT=1;
    Delay__hx711_us();
      B_SCK=0;
      count=0;
      while(B_DOUT);
    for(i=0;i<24;i++)
    {
          B_SCK=1;
          count=count<<1;
        B_SCK=0;
          if(B_DOUT)
            count++;
    }
     B_SCK=1;
    Delay__hx711_us();
    B_SCK=0;  
    return(count);
} 

void BGetWeight()
{
    BBuffer = B_Read();
    BBuffer = BBuffer/100;

    Bwight = BBuffer;
    Bwight = Bwight;                //��ȡʵ���AD������ֵ��
    
    Bwight = (unsigned int)((float)Bwight/2.09+0.05);     
    Bwight = Bwight/2;    
    

}
*/
void Different()
{
	if(++ii>=10)
	{
		FGetWeight();
//		BGetWeight();
		change = (Fwight-Bwight)/(Fwight+Bwight) * 1.0;
		change = 1 * 1.0;
		if(change > 0)
		{
			if(ca <1700) //MAX 2000
			{
				ca = ca + change;
			}
		}
		else
		{
			if(ca > 1000)
			{
				ca = ca + change;
			}
		}
		ii=0;
	}
}
////////////////////////////////////////////////////////////
unsigned int timer_init(float t)///fanshi 1 jingzhen 11.0592mhz
{ 
	unsigned int count,chuzhi;
	count=t*11.0592/12*1000;
	chuzhi=65536-count;
	return (chuzhi);	
}

//========================== ��ʱ�ӳ��� ============================

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
	uchar e,f,g,h;
	LE1=1; //ѡͨhc573	
	//�ֱ�����ѡͨ����ܵ�λѡ�� 
	A=0; BB=0; C=0;
	P0=table[a]; delay_50us(20); A=1; BB=0; C=0;
	P0=table[b]; delay_50us(20); A=0; BB=1; C=0;
	P0=table[c]; delay_50us(20); A=1; BB=1; C=0;
	P0=table[d]; delay_50us(20);
	

	e=Fwight/1000;
	f=Fwight/100%10;
	g=Fwight%100/10;
	h=Fwight%10;
	A=0; BB=0; C=1;
	P0=table[e]; delay_50us(20); A=1; BB=0; C=1;
	P0=table[f]; delay_50us(20); A=0; BB=1; C=1;
	P0=table[g]; delay_50us(20); A=1; BB=1; C=1;
	P0=table[h]; delay_50us(20); 
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
		if(d21==0&&ca<2000) 
			ca+=100; 
		while(!d21);
	} 
	if(d22==0)	
	{ 
		delay_50us(1000); 
		if(d22==0&&ca>1000)
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
	TMOD = 0x12; //��Ƭ��������Ĵ��� ,���������Ƽ���/�ж�����
	TH0 = 0x14; //��ʱ��
	TL0 = 0x14; //������
	TH1=0xff;
	TL1=0xfe;
	t=tt=0xfe33; 
	order1=1; 
	TR0 = 1; //��������λ
	TR1=1;
	
	IE = 0x8a; //�жϼĴ���
	P3 = 0x3f; 
	init(); 

	Delay_ms(1000);         //��ʱ1s,�ȴ��������ȶ�

	while(1)
	{
		tt=timer_init(ca/1000.0);
		Different();		
		fenzhi(P1);
	} 
}

void Timer0_INT() interrupt 1 
{
	
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
		break; 
	default :
		
		order1=0;
	} order1++;
}