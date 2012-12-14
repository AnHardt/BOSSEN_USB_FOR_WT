/*============================================ ͷ�ļ�˵�� ============================================================
ͷ�ļ����ƣ�init.h
ͷ�ļ���;�����ֹ���ģ���Լ���Ƭ���ĳ�ʼ��
================================================ END ===============================================================*/

//////////////////////////////////// �������� /////////////////////////////////////
void InitSys(void);
void TimeA_Init(void);
void TimeB_Init(void);
void  AVRcontrol(unsigned char fffre);
void SetTimeB0(unsigned char fre);
void port_init(void);
void init_devices(void);
void adc12_init(void);

////////////////////////////////////// END ////////////////////////////////////////

/*********************************************************************************
�������ƣ�void InitSys(void)																	
�������ܣ�ϵͳ��ʼ��
˵����
*********************************************************************************/
void InitSys(void)
{
 	//volatile uint i=0;	
	uchar i=0;
    WDTCTL = WDTPW + WDTHOLD;  	 			//ֹͣ���Ź�
	
	BCSCTL1&=~XT2OFF; 						//ʹXT2��Ч,XT2�ϵ�ʱĬ��Ϊ�رյ�.
    do
    {
      IFG1 &= ~OFIFG;   					 //������ʧЧ��־             
      for (i = 0xFF; i > 0; i--);  			 //��ʱ,���ȶ�.
    }
	while ((IFG1 & OFIFG)!=0);     			 //������ʧЧ��־��Ч
	//BCSCTL2 =SELM_2+SELS;//BCSCTL2 += SELM1;  //MCLK��ʱ��ԴΪTX2CLK����Ƶ����Ϊ1
	                   //BCSCTL2 += SELS;  //SMCLK��ʱ��ԴΪTX2CLK����Ƶ����Ϊ1                     
	
					   			 //SVSCTL=0X60+PORON;//SVS
	BCSCTL2 = 0x00;
	BCSCTL2 |= SELM1;//MCLK ʱ��ΪXT2
	BCSCTL2 |= SELS;//SMCLKʱ��ΪXT2
    
}

/*********************************************************************************
�������ƣ�void port_init(void)																	
�������ܣ��ܽų�ʼ��
˵����
*********************************************************************************/
void port_init(void)
{/*
  P1DIR |=BIT4+BIT5+BIT6+BIT7;  //�������ܽ�ʹ����� ����ָʾ��
  P1DIR &= 0xf0;
  P2DIR &=~BIT2;
  P2DIR &=~BIT3;//������Ӧ�ӿڣ�����Ϊ����
  P2DIR |= BIT0+BIT4+BIT1;
  P4DIR |= BIT2;
  P5DIR |=BIT1+BIT3+BIT4;
  P3DIR |=BIT1+BIT2+BIT3+BIT4;
  P3DIR &=~BIT5;
  P3SEL |= 0x30; 
  P1DIR |=BIT0 ;//SVS   
  */
  P1DIR    |=   BIT5 + BIT6;  //Ƶ��ѡ������Ƶ�ʷ����
  //P1SEL |= BIT5+BIT6;
  //P3DIR |=	BIT1+BIT2+BIT3;   		   //ds1302
  P3DIR |=	BIT0 + BIT1; // ����
  P2DIR |=      BIT7; // ����
  P1DIR |=	BIT0+BIT1+BIT2+BIT3+BIT4;  //���棬LED1 
  P4DIR |=	BIT3+BIT4+BIT5;			   //Һ����   
  //P1DIR	&=	~BIT7;   			//��У����������Ϊ���룬�͵�ƽ��Ч  
  P5DIR    |=   BIT5 + BIT6 ;  //  ���� AVR ��Ƭ��
  
  P3DIR |=	BIT6 + BIT7 + BIT4; //ad7711  
  P3DIR	&=	~BIT5;  //ad7711  
  P4DIR |=	BIT0 + BIT1; //ad7711  
  
  P4DIR |=	BIT7;//---����������
  P5DIR |=	BIT0;//����������---����������
  //P6DIR |=	BIT0+BIT1;//����
  
  P6DIR |=	BIT7;//Ƿѹ������
  P6DIR |=	BIT6;//����������
  
  P5DIR |=	BIT1 + BIT2 + BIT3 + BIT4;//memory
  P3DIR |=      BIT2 + BIT3;
  
  CH376_PORT_INIT();
}

/*********************************************************************************
�������ƣ�void init_devices(void)																	
�������ܣ���Ƭ���ڲ�����ģ���ʼ��
˵����
*********************************************************************************/
void init_devices(void)
{
 //stop errant interrupts until set up
 //DINT(); //disable all interrupts
  _DINT();
 ME1=0X00; //disable sfr peripherals
 ME2=0X00;  
 IE1=0x00; //disable sfr interrupts
 IE2=0x00; 
 //initialise other peripherals
 port_init();  
 Ht1621_Init();
 TimeA_Init(); 
 TimeB_Init();
 adc12_init(); 
 ad7711Init(0); 
 /////////////////////////
 /*
 MMC_Init();
 MMC_get_volume_info();
 FAT32_Init(&Init_Arg);
 */
 MemoryInit();
 ////////////////////////////
 //EINT(); //re-enable interrupts
 _EINT();
}

/*********************************************************************************
�������ƣ�void TimeA_Init(void)																	
�������ܣ���ʱ��A��ʼ��
˵����
*********************************************************************************/
void TimeA_Init(void)
{
  
  //CCR0 = 50000;
  //CCR0 = 12500; // (1/800)���ж�һ��
  CCR0 = 10000;
  
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode
 
  
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  
}

/**************************************************************************************
��������: TimeB_Init()
��������: ��ʱ�� B ��ʼ��
ʱ    �䣺2010-02-27
˵    ��: 1��ʱ��ѡ�� ACLK��
          2�������ж�ʱ�䣬��Ҫ����400Hz��Ƶ��---40.96
          3����С�ж�ʱ�䣺30.5 uS
          4��Ƶ�ʣ�Hz��     TBCCR0
              120           136.53
              15            1092.27
              5             3276.8
**************************************************************************************/
void TimeB_Init(void)
{
  TBCTL = TBSSEL_2 + TBCLR + MC0;//ACLK==32768
  //TBCTL |= MC0;
  TBCCTL0 = CCIE;                       // CCR0 interrupt enabled
  
  //TBCCR0=10;
  //TBCCR0=yui;
}

/************************************************************************************
�������ƣ�void SetTimeB0(unsigned char fre)
�������ܣ�����ѡ���Ƶ�������ö�ʱʱ��----��ʱ��B0
����ʱ�䣺2010-04-28
˵    ����1��ti��Ҫ��ʱ��ʱ�䣬��ʱ��Դ��Ƶ���й�
          2��fre��ѡ���Ƶ��; 0-5hz,1-15hz,2-120hz,3-400hz
          3��ԭ�ȵ� 4 ��Ƶ�ʶ�Ҫ�ֱ���� 2 ��
************************************************************************************/
#define frequency_5     41690      //  ע��"/2"����Ϊԭ����Ҫ���� 5 ���ȵ�Ƶ�ʣ�������Ҫ������� 10 ���ȡ�
#define frequency_15    13823
#define frequency_120   1730
#define frequency_400   519
void SetTimeB0(unsigned char fre)
{    
    if( fre==0 )
      TBCCR0=frequency_5;				//��ʱʱ��
    if( fre==1 )
      TBCCR0=frequency_15;				//��ʱʱ��
    if( fre==2 )
      TBCCR0=frequency_120;				//��ʱʱ��
    if( fre==3 )
      TBCCR0=frequency_400;				//��ʱʱ��
    ///////////////////////////////
    AVRcontrol( fre );
}

void  AVRcontrol( unsigned char fffre )
{
    if( fffre == 0 )
    {
      AVR_1_L;
      AVR_2_L;
    }
    if( fffre == 1 )
    {
      AVR_1_L;
      AVR_2_H;
    }
    if( fffre == 2 )
    {
      AVR_1_H;
      AVR_2_L;
    }
    if( fffre == 3 )
    {
      AVR_1_H;
      AVR_2_H;
    }
}

/**************************************************************************************
��������: adc12_init()
��������: AD��ʼ��
ʱ    �䣺2010-02-27
˵    ��: 1��ʹ��Ƭ�ڲο���ѹ 1.5V����������Ӳ��ԭ��1.5V�Ĳο���ѹû�е���===�Ѿ�����ͨ����
          2��ʹ��AD�ж�����ɣ�
**************************************************************************************/
void adc12_init(void)
{
  
  //P6SEL =0xff;//   
  //P6SEL =0x18;//00011000
  P6SEL =0x1B;//00011011
  ADC12CTL0 = ADC12ON+MSC+SHT0_15+REFON;// Turn on ADC12, set sampling time,Ƭ�ڲο���ѹ
  
  //ADC12CTL1 = SHP+CONSEQ_3;             // Use sampling timer, repeated sequence
  //ADC12CTL1 = ADC12SSEL_2 ;             //  ACLK  
  //ADC12CTL1 =  ADC12DIV_5 ;             //  ʵ��֤����ADC12CTL1 �Ĵ�������һ�ν�����ֵ����ֵ��
  ADC12CTL1 = SHP + CONSEQ_3 + ADC12SSEL_2 + ADC12DIV_5;//  SHP--�����ź�(SAMPCON)ѡ�����λ
                                        //  CONSEQ_3--*����ͨ�����ת��
                                        //  ADC12SSEL_2--ʱ��ѡ��MCLK
                                        //  ADC12DIV_5-- 6��Ƶ
  
  ADC12MCTL0 = INCH_3;                  // ref+=AVcc, channel = A3 ��ص�ѹ�ɼ�
  ADC12MCTL1 = INCH_4 ;              // ref+=AVcc, channel = A4, end seq. �ɼ���������
  ADC12MCTL2 = INCH_0;
  ADC12MCTL3 = INCH_1 + EOS ;         
  ADC12IE = 0x02;                       // Enable ADC12IFG.1
  ADC12CTL0 |= ENC;                     // Enable conversions
  ADC12CTL0 |= ADC12SC;                 // Start conversion
}

