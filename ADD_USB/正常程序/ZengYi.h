/*============================================ ͷ�ļ�˵�� ============================================================
ͷ�ļ����ƣ�ZengYi.h
ͷ�ļ���;���������
================================================ END ===============================================================*/

#define		A0_H	  P3OUT |= BIT1
#define		A0_L	  P3OUT &=~ BIT1
#define		A1_H	  P3OUT |= BIT0
#define		A1_L	  P3OUT &=~ BIT0
#define		A2_H	  P4OUT |= BIT7
#define		A2_L	  P4OUT &=~ BIT7
#define		A3_H	  P5OUT |= BIT0
#define		A3_L	  P5OUT &=~ BIT0
#define		A4_H	  P1OUT |= BIT0
#define		A4_L	  P1OUT &=~ BIT0
#define		A5_H	  P1OUT |= BIT1
#define		A5_L	  P1OUT &=~ BIT1
//*********************************************   ��������   **********************************************
void BinaryConversion10_2(uchar data);
void GainControl(void);
void GainControlFirst(void);
void GAIN_AUTO(unsigned char zengyi);//ֻ���Զ�������������
void GAIN_AUTO_MAX( void );//���Զ�����ֵ��Ϊ�����
//*************************************************** END *************************************************

/*******************************************************************************
�������ƣ� void BinaryConversion10_2(uchar data)
�������ܣ� ʮ����ת���ɶ�����
����	�� ��Ĵ�˵
����ʱ�䣺 2010-2-19
�޸�ʱ�䣺 2010-04-28
˵��    �� ���� Binary_2 �д��ת����Ķ����ƣ��Ӹ�λ����λ��Binary_2[DIGIT-1]��
		   Binary_2[DIGIT-2]��......Binary_2[0] ��
*******************************************************************************/
#define BASE   2        //*Ҫת���ɼ�������/* 
#define DIGIT  4     //*ת��������λ��/* 
uchar Binary_2[DIGIT];
void BinaryConversion10_2(uchar data)
{
   uchar i=0;
   uchar mmm=0;
   //for( i=0;data!=0;i++ )//���������⣺��� data �ȸ�ֵ1����Binary_2[0]==1�������ţ��� data ��Ϊ0���ͻ�ʹȫ�ֱ��������е� Binary_2[0] û�����㡣
   for( i=0;i<4;i++ )
   {
      mmm=data%2;
      data/=BASE;
	  Binary_2[i]=mmm;
   }
}

/*******************************************************************************
�������ƣ� void GainControl(void)
�������ܣ� ��������ƽŽ��п��ƣ����߻�������
����	�� ��Ĵ�˵
ʱ��	�� 2010-4-26
˵��    �� 1�����ƽţ��Ӹߵ�������Ϊ:P1.0 P1.1 P1.2 P1.3
                                  A0   A1   A2   A3��
           2����Ϊ�����������
*******************************************************************************/
void GainControl(void)
{
   if( ZengYi_flag==1 )
   {
      //memset( Binary_2,0,4 );      
      
      if( ZengYi_disp<=3 )//�� 3 ������(���AD7711������)�����ã��ڶ���ȫΪ0
      {          
          BinaryConversion10_2( ZengYi_disp );
          switch( Binary_2[DIGIT-4] )
          {
          //case 0:	A4_L;	break;
	  //case 1:	A4_H;	break;
          case 0:	A5_L;	break;
	  case 1:	A5_H;	break;  
	  default:			break;			  
          }
          switch( Binary_2[DIGIT-3] )
          {          
          //case 0:	A5_L;	break;
	  //case 1:	A5_H;	break;
          case 0:	A4_L;	break;
	  case 1:	A4_H;	break;
	  default:			break;			  
          }
          A0_L; //  �ڶ������1������
          A1_L;
          A2_L;
          A3_L;
      }
      else
        if( ZengYi_disp<=6 )//���Ƶڶ������棬��һ��ȫΪ1
        {
          A4_H; //  ������ȫ��
          A5_H;
          A2_L; //  ��һ��ȫ��
          A3_L;
          BinaryConversion10_2( ZengYi_disp-4 +1 );//��Ҫ 0 0 ��
          switch( Binary_2[DIGIT-4] )
          {
          //case 0:	A0_L;	break;
	  //case 1:	A0_H;	break;
          case 0:	A1_L;	break;
	  case 1:	A1_H;	break;  
	  default:			break;			  
          }
          switch( Binary_2[DIGIT-3] )
          {          
          //case 0:	A1_L;	break;
	  //case 1:	A1_H;	break;
          case 0:	A0_L;	break;
	  case 1:	A0_H;	break;
	  default:			break;			  
          }
        }
        else//,ZengYi_disp>6
          if( ZengYi_disp<=9 )  //  ����7,8,9////��һ������
          {
            A0_H; //  ��3����ڶ���ȫ��
            A1_H;
            A4_H;
            A5_H;
            BinaryConversion10_2( ZengYi_disp-7 +1 );//��Ҫ 0 0 ��
            switch( Binary_2[DIGIT-4] )
            {
            case 0:	A2_L;	break;
	    case 1:	A2_H;	break;
	    default:			break;			  
            }
            switch( Binary_2[DIGIT-3] )
            {          
            case 0:	A3_L;	break;
	    case 1:	A3_H;	break;
	    default:			break;			  
            }
          }
          else  //  10 11 12
          {
            A0_H;
            A1_H;
            A3_H;
            A2_H;
            A4_H;
            A5_H;
          }          
   }
}

/*******************************************************************************
�������ƣ� void GainControlFirst(void)
�������ܣ� MCU�ϵ���ʼ����
����	�� ��Ĵ�˵
ʱ��	�� 2010-2-19
˵��    �� 1�����ƽţ��Ӹߵ�������Ϊ:P1.0 P1.1 P1.2 P1.3
           2�������ϵ�� ZengYi_disp==0 ������ֱ�ӽ��ĸ��ܽ����͡�
*******************************************************************************/
void GainControlFirst(void)
{   
   A0_L;
   A1_L;
   A2_L;
   A3_L;
   A4_L; //  ������ȫ��
   A5_L;
}

///////////////////////////////////////////////////////////////////////////////////

/*********************************************************************************************************
�������ƣ�void GAIN_AUTO(unsigned char zengyi)
�������ܣ��Զ������ж�����ֵ�����趨��
˵    ����      
��    �ߣ���Ĵ�˵
����ʱ�䣺2010-07-12
�޸�ʱ�䣺
*********************************************************************************************************/
void GAIN_AUTO(unsigned char zengyi)//ֻ���Զ�������������
{//ʹ���Ŷ��� ��
  //ZengYi_disp = ZengYi_MAX;/////ֱ�Ӵ����һ������
  ZengYi_disp = zengyi;
  ZengYi_flag = 1;
  GainControl();
  ZengYi_flag = 0;
}

/*********************************************************************************************************
�������ƣ�void GAIN_AUTO_MAX( void )
�������ܣ��Զ����淽ʽ�£�������ֵ��Ϊ���ֵ��
˵    �����ú��������¼��㱻���ã�1��key_use1(void)                                
                                  2��SaveControl(void)
          �Զ�����ʱ���������һ����������ֳ����������ƣ�ʹ�ù�����Ա�������ֽӴ�����׮��ʹ���źż���
          ��������һ����ļ��ʱ��ֻҪ���°�ѹ�������������ߡ��ɼ������Ϳ��Ա��������ڼ��һ���µġ��㡱��
��    �ߣ���Ĵ�˵
����ʱ�䣺2010-07-12
�޸�ʱ�䣺
*********************************************************************************************************/
void GAIN_AUTO_MAX( void )
{
  if( AutoZengYiRun.ZengYi_Ever_Used == 0 )
    GAIN_AUTO( ZengYi_MAX-1 );
}


