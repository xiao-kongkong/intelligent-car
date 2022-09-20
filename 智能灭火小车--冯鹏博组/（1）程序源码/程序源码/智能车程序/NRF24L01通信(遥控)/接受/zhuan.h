 #ifndef   __zhuan_H__
#define   __zhuan_H__
#define uchar unsigned char
#define uint unsigned int

	 sbit  RX1 = P1^1;	 //Ç°³¬Éù²¨		S1
	 sbit  TX1 = P1^2;
	 sbit  RX2 = P2^1;	 //×ó³¬Éù²¨		S2
	 sbit  TX2 = P2^2;
	 sbit  RX3 = P2^6;	 //ÓÒ³¬Éù²¨		S3
	 sbit  TX3 = P2^7;

	 sbit  feng = P2^3;

	 sbit xun1 = P2^4;
	 sbit xun2 = P2^5;



extern	 unsigned int num1;
extern	 unsigned int  time;
extern	 unsigned int  timer;
extern	 unsigned char posit;
extern	 unsigned int S1,S2,S3; 
extern	unsigned char o;
extern unsigned char n1,n2;
void youzhuan();
void zuozhuan();
void houzhuan();
void zuo();
void you();
//void zhi();
//void xiaozuo(uchar x);
//void xiaoyou(uchar x);
void move ();
extern void pwm (uchar x, uchar y);
void qian();
void zuozuo();
void youyou();
void ting();
void xiaoqian();

#endif