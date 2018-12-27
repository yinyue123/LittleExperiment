
#include <reg52.h>
#include <intrins.h>
sbit MOTOA = P1^0;
sbit MOTOB = P1^1;
sbit MOTOC = P1^2;
sbit MOTOD = P1^3;


void delay(int time)
{ 
  int i,j;
  
  for(j=0; j <= time; j++)
   for(i =0 ; i <= 120; i++);
}

void main()
{ 
	P1 = 0x00;
	while (1) 
	{	 	
			MOTOA = 1;
			MOTOB = 0;
			MOTOC = 1;
			MOTOD = 1;
			delay(2);

			MOTOA = 1;
			MOTOB = 1;
			MOTOC = 1;
			MOTOD = 0;
			delay(2);

			MOTOA = 0;
			MOTOB = 1;
			MOTOC = 1;
			MOTOD = 1;
			delay(2);

			MOTOA = 1;
			MOTOB = 1;
			MOTOC = 0;
			MOTOD = 1;
			delay(2);
	
	}
 
}


