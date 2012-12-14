/*============================================ ͷ�ļ�˵�� ============================================================
ͷ�ļ����ƣ�AD7711_ZY1.h
ͷ�ļ���;��24λADоƬ��������
ʱ      �䣺2010-02-25
��      �ã���оƬʹ���ⲿ����10M
================================================ END ===============================================================*/


/********************************************************************************

                            	�������͵Ķ���

********************************************************************************/
#define  	BYTE	unsigned char	
#define 	WORD	unsigned int
#define  	SBYTE	signed char
#define 	SWORD	signed int


#define         DRDY       BIT5
#define         DATA       BIT1
/*RFS�Ŀ���*/
#define		SET_RFS_1		(P3OUT |= BIT7)
#define		CLR_RFS_1		P3OUT &=~ BIT7

/*TFS�Ŀ���*/
#define		SET_TFS_1		P3OUT |= BIT6
#define		CLR_TFS_1		P3OUT &=~ BIT6

/*DRDY��״̬*/  //��ȡ�ܽ�״̬
//#define		STATUS_DRDY_1		(P3IN&0X20) //��ȡP35
#define		STATUS_DRDY_1		(P3IN & DRDY) //��ȡP35

/*SCLK�Ŀ���*/
#define		SET_SCLK		P4OUT |= BIT0
#define		CLR_SCLK		P4OUT &=~ BIT0

/*SDATA�Ŀ���*/
#define		SET_SDATA		P4OUT |= BIT1	
#define		CLR_SDATA		P4OUT &=~ BIT1
/*SDATA��״̬*/
//#define		STATUS_SDATA	(P4IN&0X02)
#define		STATUS_SDATA	(P4IN & DATA)
/*SDATA��������Ŀ���*/
/*SDATA_MASTER:ATmega32L������������ݣ�Ϊ��������	*/
/*SDATA_SLAVE :ATmega32L���룬�������ݣ�Ϊ��������	*/
#define		SDATA_MASTER	        P4DIR |=BIT1
#define		SDATA_SLAVE		P4DIR&=~BIT1

/*A0�Ŀ���*/
/*A0=0,������ƼĴ���*/
/*A0=1,�������ݼĴ���*/
#define		ACCESS_CTL_REG		P3OUT |= BIT4
#define		ACCESS_DATA_REG		P3OUT &=~ BIT4	
                                    
/*AD7710�Ŀ��ƼĴ���*/
//#define		CTRL_REG_LOW		0x86		
//#define		CTRL_REG_MID		0x81
#define		CTRL_REG_LOW		0x0D	//  FS7-FS0: 00001101	
#define		CTRL_REG_MID		0x93	//	WL R0 B0 B/U FS11 FS10 FS9 FS8: 10000011
										//	WL = 1; ������ݳ���24λ
										//	R0 = 0; ��
										//	B0 = 0;	�۶ϵ�����
										//	B/U= 0;	˫������ CH ���ʹ��
#define		CTRL_REG_HIG		0x20	//	MD2 MD1 MD0 G2 G1 G0 CH PD: 00100000
										//	MD2 MD1 MD0=001,������У׼ģʽ
										//	G2 G1 G0=000,����--1
										//	CH = 0; AIN1ͨ����Ĭ��
										//	PD = 0;	��׼����״̬
//#define		CTRL_REG_HIG		0x22	//	AIN2ͨ��
//#define		CTRL_REG_HIG		0x30	//	ͨ��1������8��



//*********************************************   ��������   **********************************************
void GetRealAD(void);
void send24Bit(BYTE *Comm,BYTE chs);//��AD7711ָ����ͨ������24bit���ݣ�chs��ѡ��ͨ������0��1��2,3
void readCommReg(BYTE *CommReg,BYTE chs);//��AD7711���ƼĴ���������*CommReg� chs��ѡ��ͨ������0��1��2��3
BYTE ad7711Init(BYTE chs);//��AD7711��ʼ���� chs��ѡ��ͨ������0,1,2,3
signed long Read24DataFromAd7710(void);
//*************************************************** END *************************************************

/**********************************************************************
��������:void send24Bit(BYTE *Comm,BYTE chs)
��������:��AD7711ָ����ͨ������24bit���ݣ�chs��ѡ��ͨ������0��1��2,3
ʱ    �䣺2010-02-25
��    �ã��ⲿ����10M
**********************************************************************/
void send24Bit(BYTE *Comm,BYTE chs)
{
	BYTE i,temp,j;	
        ACCESS_DATA_REG;//A0=0;	//���ƼĴ���
        CLR_TFS_1;//_TFS = 0;//д����ģʽ 
	for(i=0;i<3;i++)
	{		
                temp=*(Comm+i);
		for(j=0;j<8;j++)
		{
                        SET_SCLK;
			if(temp&0x80)
			{
				SET_SDATA;
			}
			else
			{
				CLR_SDATA;
			}
			
			asm("nop");//DelayMS(1);//asm("nop");
			CLR_SCLK;
			temp<<=1;
		}
	}	
	ACCESS_CTL_REG;
        SET_TFS_1;
}

/**********************************************************************
functionName:void readCommReg(BYTE *CommReg,BYTE chs)
description:��AD7711���ƼĴ���������*CommReg� chs��ѡ��ͨ������0��1��2��3
����ʱ�䣺70.53us  7.3728MHZ����
**********************************************************************/
void readCommReg(BYTE *CommReg,BYTE chs)
{
	BYTE i,j,temp=0;	
	SDATA_SLAVE;		
        ACCESS_DATA_REG;//A0=0; ////���ƼĴ���
        CLR_RFS_1;//_RFS = 0;//������ģʽ 	
        asm("nop");
	for(i=0;i<3;i++)
	{
		temp=0;			
		asm("nop");//DelayMS(20);//asm("nop");
		for(j=0;j<8;j++)
		{
			SET_SCLK;                        
			temp<<=1;			
			if(STATUS_SDATA)///////////////////////////////////////////////////
			temp|=0x01;				
			asm("nop");//DelayMS(1);//asm("nop");	
			CLR_SCLK;
		}
		*(CommReg+i)=temp;
	}
	SET_RFS_1;	
        ACCESS_CTL_REG;
	SDATA_MASTER;
}

/**********************************************************************
functionName:BYTE ad7711Init(BYTE chs)
description:��AD7711��ʼ���� chs��ѡ��ͨ������0,1,2,3
�����ʼ���ɹ�����0xff,ʧ�ܷ���0x00;
**********************************************************************/
uchar ad7711init;////////////////////////////////////////////////////////////
BYTE ad7711CtrlReg[3],temp1[3];
BYTE ad7711Init(BYTE chs)
{
	BYTE i,j,result;
RE:
	ad7711CtrlReg[0]=CTRL_REG_HIG;
	ad7711CtrlReg[1]=CTRL_REG_MID;
	ad7711CtrlReg[2]=CTRL_REG_LOW;
	send24Bit(ad7711CtrlReg,chs);
	//usDelay(32);
	asm("nop");//DelayMS(1);
	readCommReg(temp1,chs);
	i=0x00;
	while(i<20)//�ظ�����ʼ���Ƿ�ɹ�
	{
		result=0xFF;
                ad7711init = result;//////////////////////////
		for(j=0;j<3;j++)
		{
			if(temp1[j]!=ad7711CtrlReg[j])
			{
				result=0x00;
                                ad7711init = result;////////////////////////
			}
		}
		if(result)
		{
			return(result);
		}
		i++;
		send24Bit(ad7711CtrlReg,chs);
		//usDelay(32);
		asm("nop");//DelayMS(1);
		readCommReg(temp1,chs);
	}
        ad7711init = result;        
        
        if( result==0x00 )  goto RE;//�ظ����20�γ�ʼ��ʧ�ܺ󣬼������ؼ�顣������
        
	return(result);
}



/*******************************************************************************
�������ƣ�Read24DataFromAd7710(void)
�������ܣ���24λ����
˵    ����
ʱ    �䣺2010-02-25
*******************************************************************************/
unsigned long ReadData=0;
signed long Read24DataFromAd7710(void)
{
  uchar i=0;  
  ReadData=0;
  SDATA_SLAVE;   
  while(STATUS_DRDY_1)//
  {
      ;
  }  
  ACCESS_CTL_REG	;//A0=1;	//���ݡ�У׼�Ĵ���
  CLR_RFS_1;//_RFS = 0; //������ģʽ
  for(i=0;i<24;i++)
  {
	  SET_SCLK;//SCLK=1;
	  ReadData=ReadData<<1;
          if(STATUS_SDATA)
	  {
	      ReadData+=1;
          }
	  CLR_SCLK;//SCLK=0;
  }
  ACCESS_CTL_REG	;//A0 = 1; 
  SET_RFS_1;//_RFS = 1;
  //ReadData = ReadData>>ZengYi_disp; //�������� 
  return ReadData;
}

/*******************************************************************************
�������ƣ�
�������ܣ���ǰ������������ʹ�õ���ADֵ��Ϊԭֵ
˵    ����
ʱ    �䣺2010-02-25
*******************************************************************************/
void GetRealAD(void)
{
  
}
