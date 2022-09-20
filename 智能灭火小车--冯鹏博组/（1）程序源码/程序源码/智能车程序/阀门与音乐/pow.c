#include<stc12c5a.h>
#define uint unsigned int
#define uchar unsigned char

sbit ms = P1^0;
sbit mr = P1^1;
sbit mn = P1^2;

void delayms (uint i)
{	uint j,k;
	for (j = 0; j<i; j++)
		for (k = 0; k<120;k++);
}

void pow()
{
	ms=1;
	mr=0;
	mn=1;
delayms(1);	
}

void pows()
{
	ms=0;
	mr=0;
	mn=0;
	delayms(1);	
}