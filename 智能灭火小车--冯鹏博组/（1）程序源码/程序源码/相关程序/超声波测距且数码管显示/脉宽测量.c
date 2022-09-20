/***********************************************************************************************************/
//hc-sr04 ���������ģ�� DEMO ����
//����11��0592
//����	  QQ�� 517535000
//taobao���̣�http://shop58246706.taobao.com
//���ߣ�ģ��TRIG�� P0.2  ECH0 ��P0.1
//����ܣ����������P1�����ݿ�,P2.5 P2.4 P2.3��ѡͨ�����
/***********************************************************************************************************/	    
		     #include <AT89x51.H>		//���������ļ�
			 #include <intrins.h>
			 #define  RX  P1_1
			 #define  TX  P1_2
			 unsigned int  time=0;
			 unsigned int  timer=0;
			 unsigned char posit=0;
			 sbit du = P2^6;
			 sbit we = P2^7;
			 unsigned long S=0;
			 bit      flag =0;							 //
			 unsigned char const discode[] ={ 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40,0x7c,0x39,0x5e,0x79,0x71/*-*/};   //��ѡ
			 unsigned char const positon[3]={ 0xf7,0xef,0xdf};		   //λѡ
			 unsigned char disbuff[4]	   ={ 0,0,0,0,};
/********************************************************/
    void Display(void)				 //ɨ�������
	{
	 if(posit==0)
	 { du = 1;
	 P0=(discode[disbuff[posit]])&0x7f;
	 du = 0;  }
	 else
	 {
	 du = 1;
	 P0=discode[disbuff[posit]];
	 du = 0;}

	  we = 1;
	  P0=positon[posit];
	  we = 0;

	  if(++posit>=3)
	  posit=0;
	}
/********************************************************/
    void Conut(void)
	{
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	
	 S=(time*1.7)/100;     //�������CM
	 if((S>=700)||flag==1) //����������Χ��ʾ��-��
	 {	 
	  flag=0;
	  disbuff[0]=10;	   //��-��
	  disbuff[1]=10;	   //��-��
	  disbuff[2]=10;	   //��-��
	 }
	 else
	 {
	  disbuff[0]=S%1000/100;
	  disbuff[1]=S%1000%100/10;
	  disbuff[2]=S%1000%10 %10;
	 }
	}
/********************************************************/
     void zd0() interrupt 1 		 //T0�ж��������������,������෶Χ
  {
    flag=1;							 //�ж������־
  }
/********************************************************/
   void  zd3()  interrupt 3 		 //T1�ж�����ɨ������ܺͼ�800MS����ģ��
  {
	 TH1=0xf8;
	 TL1=0x30;
	 Display();
	 timer++;
	 if(timer>=80)
	 {
	  timer=0;
	  TX=1;			                //800MS  ����һ��ģ��
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  TX=0;
	 } 
  }
/*********************************************************/

	void  main(  void  )

  {  
    TMOD=0x11;		   //��T0 T1Ϊ��ʽ1��GATE=1��  mode1 16λ�ڲ���ʱ��
	TH0=0;
	TL0=0;          
	TH1=0xf8;		   //2MS��ʱ
	TL1=0x30;
	ET0=1;             //����T0�ж�
	ET1=1;			   //����T1�ж�
	TR1=1;			   //������ʱ��
	EA=1;			   //�������ж�

	while(1)
	{
	 while(!RX);		//��RXΪ��ʱ�ȴ�
	 TR0=1;			    //��������
	 while(RX);			//��RXΪ1�������ȴ�
	 TR0=0;				//�رռ���
     Conut();			//����
	}

  }
                