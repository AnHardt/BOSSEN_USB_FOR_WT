/*============================================ ͷ�ļ�˵�� ============================================================
ͷ�ļ����ƣ�Setting.h
ͷ�ļ���;���������õ���ع���
================================================ END ===============================================================*/

//*********************************************   ��������   **********************************************



void AB_shanshuo_repair(void);//Ϊ��ֹͬʱ����������˸λ
void MN_shanshuo_repair(void);//Ϊ��ֹͬʱ����������˸λ
void Position_shanshuo_repair(void);//Ϊ��ֹͬʱ����������˸λ

void AB_Setting(void);
void MN_Setting(void);
//void FeatureSelection_Port(void);
void FeatureSelection_Port_First(void);
void FrequencyPointSelection_Port(void);
void FeatureSelection(void);
void FrequencyPointSelection(void);
void TimeWindow(void);


void Position(void);
void PositionControl(void);
//*************************************************** END *************************************************

/*******************************************************************************
�������ƣ� 
�������ܣ� ���� ���� ���󣬵�һ��
ʱ��	�� 2010-2-19
˵��    �� ����1/2AB��Ĭ��ֵ0006.000 m  
*******************************************************************************/

void AB_Setting(void)
{
   uchar j=4;
   uint	 a;
   uchar *p;
   if( Setting_up==2 )
   {
      Setting_up=0;
	  AB_shanshuo --;
	  if( AB_shanshuo<=0 )
	     AB_shanshuo=4;
   }   
   if( Setting_down==2 )
   {
      Setting_down=0;
	  AB_shanshuo ++;
	  if( AB_shanshuo>4 )
	     AB_shanshuo=1;
   }//////////////////////////////////////////////////////��˸λѡ��
   
   if( Setting_up==1 )
   {
      Setting_up=0;
	  j=j-AB_shanshuo;
	  //AB_data+=pow(10,j);//10��n����	
	  p= Decomposition( AB_data );
	  if( *(p+j)!=9 )
	     AB_data+=pow10(j) ;
	  else
	     AB_data = AB_data- 9*pow10(j);
   }
   if( Setting_down==1 )
   {
      Setting_down=0;
	  j=j-AB_shanshuo;
	  p= Decomposition( AB_data );
	  if( *(p+j)!=0 )
	     AB_data-=pow10(j) ;
	  else
	     AB_data = AB_data+ 9*pow10(j);
   }///////////////////////////////////////�޸���˸���ֵĴ�С
   
   
   if( second%2==0 )
   {
      Ht1621WrOneData( 0,8 );//������˾�ı�ʶ  
   	  Ht1621WrOneData( 9,8+4 ); //������˾�ı�ʶ  //����1/2AB
   	  Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  	
   	  Ht1621WrOneData( 13,8 );	//��λ��m
   	  Ht1621WrOneData( disp_data_addr[0][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ 0 ][1] );//
   	  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ AB_data/1000 ][0] );
   	  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ AB_data/1000 ][1] );//
   	  a=AB_data%1000;//�õ���λ��
   	  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ a/100 ][0] );
   	  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ a/100 ][1] );//
   	  a=a%100; //�õ���λ��  
   	  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ a/10 ][0] );
   	  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ a/10 ][1] );///////Ĭ��ֵ0006.000m
   	  Ht1621WrOneData( 12,1 );	//С����
   	  a=a%10;//�õ���λ��
   	  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ a ][0] );
   	  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ a ][1] );// 
   	  Ht1621WrOneData( disp_data_addr[5][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[5][1],disp_data[ 0 ][1] );//
   	  Ht1621WrOneData( disp_data_addr[6][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[6][1],disp_data[ 0 ][1] );//   	  
   }
   else
   {
      Ht1621WrOneData( disp_data_addr[ AB_shanshuo ][0],0 );
      Ht1621WrOneData( disp_data_addr[ AB_shanshuo ][1],0 );//�Ӽ�λ��˸
      AB_shanshuo_repair( );
   }
}

/*******************************************************************************
�������ƣ� void MN_Setting(void)
�������ܣ� ���� ���� ���󣬵�2��
ʱ��	�� 2010-2-19
˵��    �� ����1/2MN��Ĭ��ֵ0003.000 m
*******************************************************************************/
void MN_Setting(void)
{
   uchar j=4;
   uint	 a;
   uchar *p;
   if( Setting_up==2 )
   {
      Setting_up=0;
	  AB_shanshuo --;
	  if( AB_shanshuo<=0 )
	     AB_shanshuo=4;
   }   
   if( Setting_down==2 )
   {
      Setting_down=0;
	  AB_shanshuo ++;
	  if( AB_shanshuo>4 )
	     AB_shanshuo=1;
   }//////////////////////////////////////////////////////��˸λѡ��
   
   if( Setting_up==1 )
   {
      Setting_up=0;
	  j=j-AB_shanshuo;
	  //AB_data+=pow(10,j);//10��n����	
	  p= Decomposition( MN_data );
	  if( *(p+j)!=9 )
	     MN_data+=pow10(j) ;
	  else
	     MN_data = MN_data- 9*pow10(j);
   }
   if( Setting_down==1 )
   {
      Setting_down=0;
	  j=j-AB_shanshuo;
	  p= Decomposition( MN_data );
	  if( *(p+j)!=0 )
	     MN_data-=pow10(j) ;
	  else
	     MN_data = MN_data+ 9*pow10(j);
   }///////////////////////////////////////�޸���˸���ֵĴ�С
   
   if( second%2==0 )
   {
      Ht1621WrOneData( 0,8 );//������˾�ı�ʶ  
      Ht1621WrOneData( 9,8+2 ); //������˾�ı�ʶ  //����1/2MN
      Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  	
      Ht1621WrOneData( 13,8 );	//��λ��m
      Ht1621WrOneData( disp_data_addr[0][0],disp_data[ 0 ][0] );
      Ht1621WrOneData( disp_data_addr[0][1],disp_data[ 0 ][1] );//
   	  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ MN_data/1000 ][0] );
   	  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ MN_data/1000 ][1] );//
   	  a=MN_data%1000;//�õ���λ��
   	  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ a/100 ][0] );
   	  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ a/100 ][1] );//
   	  a=a%100; //�õ���λ��  
   	  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ a/10 ][0] );
   	  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ a/10 ][1] );///////Ĭ��ֵ0006.000m
   	  Ht1621WrOneData( 12,1 );	//С����
   	  a=a%10;//�õ���λ��
      Ht1621WrOneData( disp_data_addr[4][0],disp_data[ a ][0] );
      Ht1621WrOneData( disp_data_addr[4][1],disp_data[ a ][1] );// 
      Ht1621WrOneData( disp_data_addr[5][0],disp_data[ 0 ][0] );
      Ht1621WrOneData( disp_data_addr[5][1],disp_data[ 0 ][1] );//
      Ht1621WrOneData( disp_data_addr[6][0],disp_data[ 0 ][0] );
      Ht1621WrOneData( disp_data_addr[6][1],disp_data[ 0 ][1] );//   	  
   }
   else
   {
      Ht1621WrOneData( disp_data_addr[ AB_shanshuo ][0],0 );
      Ht1621WrOneData( disp_data_addr[ AB_shanshuo ][1],0 );//�Ӽ�λ��˸ 
      
      MN_shanshuo_repair();
   }
   
}

/*******************************************************************************
�������ƣ� void FeatureSelection(void)
�������ܣ� ���� ���� ���󣬵�3��
ʱ��	�� 2010-2-19
˵��    �� ����"����ѡ��"��Ĭ��ֵ0000.000
*******************************************************************************/
void FeatureSelection(void)
{
   Ht1621WrOneData( 0,8 );//������˾�ı�ʶ  
   Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ  
   Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  	
   
   if( Setting_up==1 )
   {
      Setting_up=0;
	  FeatureSelection_data ++;
	  if( FeatureSelection_data>3 )
	     FeatureSelection_data=0;
      CheckFeatureSelection( );//�Ե������Position_data��7�����г�ʼ��
   }
   if( Setting_down==1 )
   {
      Setting_down=0;
	  if( FeatureSelection_data!=0 )
	     FeatureSelection_data --;
	  else
	     FeatureSelection_data=3;//0 1 2 3
      CheckFeatureSelection( );//�Ե������Position_data��7�����г�ʼ��
   }///////////////////////////////////////�޸���˸���ֵĴ�С
   //FeatureSelection_Port();//
   
   ////display
   if( second%2==0 )
   {      
   	  Ht1621WrOneData( disp_data_addr[0][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ 0 ][1] );//
   	  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ 0 ][0]+8 );//����������ѡ��
   	  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ 0 ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ 0 ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ FeatureSelection_data ][0] );
   	  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ FeatureSelection_data ][1] );///////Ĭ��ֵ0006.000m
   	  //Ht1621WrOneData( disp_data_addr[3][0],disp_data[ 9 ][0] );
   	  //Ht1621WrOneData( disp_data_addr[3][1],disp_data[ 9 ][1] );///////Ĭ��ֵ0006.000m
   	  
	  Ht1621WrOneData( 12,1 );	//С����
   	  
   	  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ 0 ][1] );// 
   	  Ht1621WrOneData( disp_data_addr[5][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[5][1],disp_data[ 0 ][1] );//
   	  Ht1621WrOneData( disp_data_addr[6][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[6][1],disp_data[ 0 ][1] );//   	  
   }
   else
   {
      Ht1621WrOneData( disp_data_addr[ 3 ][0],0 );
   	  Ht1621WrOneData( disp_data_addr[ 3 ][1],0 );//�Ӽ�λ��˸   
   }
}

/**************************************************************************************
�������ƣ�void FeatureSelection_Port(void)
�������ܣ�4�����Ƶ�ʵĿ��ƽ�
ʱ    �䣺2010-06-24
˵    ����1��
          2��
���Ƶڶ�·��ͨоƬ�Ĺܽţ�
��Ƭ����14��P1.2���ź�15��P1.3���š�
�������£�������ѹ��"����ѡ��"ѡ0����0��0
          ������ѹ��"����ѡ��"ѡ1����0��1
          ������ѹ��"����ѡ��"ѡ2����1��0
          ������ѹ��"����ѡ��"ѡ3����1��1

**************************************************************************************/
void FeatureSelection_Port(void)
{  
   //BinaryConversion10_2( FeatureSelection_data );////  
   BinaryConversion10_2( FrequencyPointSelection_data );//
   if( Binary_2[1]==1 )  FeatureSelection1_H;
   else  FeatureSelection1_L;
   if( Binary_2[0]==1 )  FeatureSelection0_H;
   else  FeatureSelection0_L;  
}

//���Ƶڶ�·��ͨоƬ�Ĺܽţ�
void GradeTwo_DaiTong(void)
{
  BinaryConversion10_2( FrequencyPointSelection_data );//
   if( Binary_2[1]==1 )  FeatureSelection1_H;
   else  FeatureSelection1_L;
   if( Binary_2[0]==1 )  FeatureSelection0_H;
   else  FeatureSelection0_L; 
}

void FeatureSelection_Port_First(void)///��ʼ��ȫ��
{
  FeatureSelection1_L;FeatureSelection0_L; 
}

/*******************************************************************************
�������ƣ� void FrequencyPointSelection(void)
�������ܣ� ���� ���� ���󣬵�4��---Ƶ��ѡ��
ʱ��	�� 2010-2-19
˵��    �� ����"Ƶ��ѡ��"��Ĭ��ֵ0000.000
*******************************************************************************/
void FrequencyPointSelection(void)
{
   Ht1621WrOneData( 0,8 );//������˾�ı�ʶ  
   Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ  
   Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  	
   
   if( Setting_up==1 )
   {
      Setting_up=0;
	  FrequencyPointSelection_data ++;
	  if( FrequencyPointSelection_data>3 )
	     FrequencyPointSelection_data=0;
   }
   if( Setting_down==1 )
   {
      Setting_down=0;
	  if( FrequencyPointSelection_data!=0 )
	     FrequencyPointSelection_data --;
	  else
	     FrequencyPointSelection_data=3;
   }///////////////////////////////////////�޸���˸���ֵĴ�С
   
   FrequencyPointSelection_Port();
   GradeTwo_DaiTong( );
   
   ///display
   if( second%2==0 )
   {      
   	  Ht1621WrOneData( disp_data_addr[0][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ 0 ][1] );//
   	  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ 0 ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ 0 ][0] +8 ); //������Ƶ��ѡ��
   	  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ 0 ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ FrequencyPointSelection_data ][0] );
   	  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ FrequencyPointSelection_data ][1] );///////Ĭ��ֵ0006.000m
   	  //Ht1621WrOneData( disp_data_addr[3][0],disp_data[ 9 ][0] );
   	  //Ht1621WrOneData( disp_data_addr[3][1],disp_data[ 9 ][1] );///////Ĭ��ֵ0006.000m
   	  
	  Ht1621WrOneData( 12,1 );	//С����
   	  
   	  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ 0 ][1] );// 
   	  Ht1621WrOneData( disp_data_addr[5][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[5][1],disp_data[ 0 ][1] );//
   	  Ht1621WrOneData( disp_data_addr[6][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[6][1],disp_data[ 0 ][1] );//   	  
   }
   else
   {
      Ht1621WrOneData( disp_data_addr[ 3 ][0],0 );
   	  Ht1621WrOneData( disp_data_addr[ 3 ][1],0 );//�Ӽ�λ��˸   
   }
}
void FrequencyPointSelection_Port(void)
{
   BinaryConversion10_2( FrequencyPointSelection_data );
   
   if( Binary_2[1]==1 )  FrequencyPointSelection1_H;
   else  FrequencyPointSelection1_L;
   if( Binary_2[0]==1 )  FrequencyPointSelection0_H;
   else  FrequencyPointSelection0_L;
}

/*******************************************************************************
�������ƣ� void TimeWindow(void)
�������ܣ� ���� ���� ���󣬵�5��---ʱ������
ʱ��	�� 2010-2-19
˵��    �� 1������"ʱ������"��Ĭ��ֵ0000.000 S
		   2��ʱ������������ֻ�����ֵĵ�4λ����ѭ������ѡ��ֵΪ0��1��2��3��
		   3��0Ϊ��ѹ"������"��P1.5��P1.6��Ƶ10S���Զ�ֹͣ��1Ϊ20S,2Ϊ30S��3Ϊ40S.

*******************************************************************************/
void TimeWindow(void)
{
   Ht1621WrOneData( 0,8 );//������˾�ı�ʶ  
   Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ  
   Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  
   
   Ht1621WrOneData( 10,1 );	//  ����"ʱ������"
   Ht1621WrOneData( 13,2 );	//  ��λ��S
   
   if( Setting_up==1 )
   {
      Setting_up=0;
	  TimeWindow_data ++;
	  if( TimeWindow_data>3 )
	     TimeWindow_data=0;
   }
   if( Setting_down==1 )
   {
      Setting_down=0;
	  if( TimeWindow_data!=0 )
	     TimeWindow_data --;
	  else
	     TimeWindow_data=3;
   }///////////////////////////////////////�޸���˸���ֵĴ�С
   
   ///display
   if( second%2==0 )
   {      
   	  Ht1621WrOneData( disp_data_addr[0][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ 0 ][1] );//
   	  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ 0 ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ 0 ][0]  ); 
   	  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ 0 ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ TimeWindow_data ][0] );
   	  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ TimeWindow_data ][1] );///////Ĭ��ֵ0006.000m
   	  
	  Ht1621WrOneData( 12,1 );	//С����
   	  
   	  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ 0 ][1] );// 
   	  Ht1621WrOneData( disp_data_addr[5][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[5][1],disp_data[ 0 ][1] );//
   	  Ht1621WrOneData( disp_data_addr[6][0],disp_data[ 0 ][0] );
   	  Ht1621WrOneData( disp_data_addr[6][1],disp_data[ 0 ][1] );//   	  
   }
   else
   {
      Ht1621WrOneData( disp_data_addr[ 3 ][0],0 );
   	  Ht1621WrOneData( disp_data_addr[ 3 ][1],0 );//�Ӽ�λ��˸   
   }

}

/*******************************************************************************
�������ƣ� void Position(void)
�������ܣ� ���� ���� ���󣬵�6��---
ʱ��	�� 2010-2-19
˵��    �� ����"���"��Ĭ��ֵ0010.001��������"���"���ظ�������ż���
*******************************************************************************/
void Position(void)
{
   //uchar j=0;
   Ht1621WrOneData( 0,8 );//������˾�ı�ʶ  
   Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ  
   Ht1621WrOneData( 11,4 );//������˾�ı�ʶ  
   Ht1621WrOneData( 10,0 );	//�������ɼ���ͼ��--�ر�
   Ht1621WrOneData( 13,0 );//��λ��mV---�ص�    
   /*
   if( Setting_up==2 )  //  ��˸λ
   {
      Setting_down=0;
      Position_shanshuo++;          
      if( Position_shanshuo>6 )   
        Position_shanshuo = 0;
      Position_shanshuo_Control( 0 );
   }
   if( Setting_down==2 )  
   {
      Setting_up=0;
      if( Position_shanshuo!=0 )
      {   
	     Position_shanshuo--;             
      }
      else
	     Position_shanshuo=6;
      Position_shanshuo_Control( 1 );
   } 
   */
   if( Setting_up==2 )  //  ��˸λ
   {
      Setting_up = 0;
      Position_shanshuo++;          
      if( Position_shanshuo>6 )   
        Position_shanshuo = 0;
      Position_shanshuo_Control( 0 );
   }
   //////////////////////////////////////////////////////��˸λѡ��
   
   if( Setting_up==1 )
   {
      Setting_up=0;
      Position_data[ Position_shanshuo ]++;
      SetScaleForPosition( 0 );      
      ZhuangHao_RST( );//////////////////
   }
   if( Setting_down==1 )
   {
      Setting_down=0;
      Position_data[ Position_shanshuo ]--;
      SetScaleForPosition( 1 );          
      ZhuangHao_RST( );////////////////////
   }///////////////////////////////////////�޸���˸���ֵĴ�С
   
   ///display
   if( second%2==0 )
   {      
   	  Ht1621WrOneData( disp_data_addr[0][0],disp_data[ Position_data[0] ][0] );
   	  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ Position_data[0] ][1] );//
   	  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ Position_data[1] ][0] );
   	  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ Position_data[1] ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ Position_data[2] ][0]  ); 
   	  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ Position_data[2] ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ Position_data[3] ][0] + 8 ); // ��������š�
   	  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ Position_data[3] ][1] );////
   	  
	  Ht1621WrOneData( 12,1 );	//С����
   	  
   	  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ Position_data[4] ][0] );
   	  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ Position_data[4] ][1] );// 
   	  Ht1621WrOneData( disp_data_addr[5][0],disp_data[ Position_data[5] ][0] );
   	  Ht1621WrOneData( disp_data_addr[5][1],disp_data[ Position_data[5] ][1] );//
   	  Ht1621WrOneData( disp_data_addr[6][0],disp_data[ Position_data[6] ][0] );
   	  Ht1621WrOneData( disp_data_addr[6][1],disp_data[ Position_data[6] ][1] );//  
          
           
   }
   else//�Ӽ�λ��˸ 
   {      
      if( Position_shanshuo==3 )  //  Ϊ�˷�ֹ"���"������Ҳ��˸
      {
        Ht1621WrOneData( disp_data_addr[ Position_shanshuo ][0],0+8 );  //  "���"
        Ht1621WrOneData( disp_data_addr[ Position_shanshuo ][1],0 );//�Ӽ�λ��˸ 
      }
      else
      {
        Ht1621WrOneData( disp_data_addr[ Position_shanshuo ][0],0 );
        Ht1621WrOneData( disp_data_addr[ Position_shanshuo ][1],0 );
      }
      Position_shanshuo_repair( );
   }
   
}

/*******************************************************************************
�������ƣ� void PositionControl(void)
�������ܣ� �������������
ʱ��	�� 2010-2-19
˵��    �� 
*******************************************************************************/
void PositionControl(void)
{
   if( Position_flag==1 )
   {
      Position();
   }
}

/*******************************************************************************
�������ƣ� void SettingControl(void)
�������ܣ� ���ð�����6����
ʱ��	�� 2010-2-19
˵��    �� 
*******************************************************************************/
void SettingControl(void)
{
   /*
   switch( Setting_flag )
   {
      case 1: AB_Setting();
	  	   	  break;
	  case 2:
	  case 3:
	  case 4:
	  case 5:
	  case 6:
	  default:
	         break;
   }
   */
   if( Setting_flag==1 ) AB_Setting();
   if( Setting_flag==2 ) MN_Setting();
   if( Setting_flag==3 ) FeatureSelection();
   if( Setting_flag==4 ) FrequencyPointSelection();//�ù���ȡ��
   //if( Setting_flag==4 ) Setting_flag = 5 ;
   if( Setting_flag==5 ) TimeWindow();
   if( Setting_flag==6 ) Position();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AB_shanshuo_repair(void)//Ϊ��ֹͬʱ����������˸λ
{
  uint a=0;
  if( AB_shanshuo_cmp!=AB_shanshuo )
  {
    AB_shanshuo_cmp = AB_shanshuo ;
    
    Ht1621WrOneData( 0,8 );//������˾�ı�ʶ  
    Ht1621WrOneData( 9,8+4 ); //������˾�ı�ʶ  //����1/2AB
    Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  	
    Ht1621WrOneData( 13,8 );	//��λ��m
    Ht1621WrOneData( disp_data_addr[0][0],disp_data[ 0 ][0] );
    Ht1621WrOneData( disp_data_addr[0][1],disp_data[ 0 ][1] );//
    Ht1621WrOneData( disp_data_addr[1][0],disp_data[ AB_data/1000 ][0] );
    Ht1621WrOneData( disp_data_addr[1][1],disp_data[ AB_data/1000 ][1] );//
    a=AB_data%1000;//�õ���λ��
    Ht1621WrOneData( disp_data_addr[2][0],disp_data[ a/100 ][0] );
    Ht1621WrOneData( disp_data_addr[2][1],disp_data[ a/100 ][1] );//
    a=a%100; //�õ���λ��  
    Ht1621WrOneData( disp_data_addr[3][0],disp_data[ a/10 ][0] );
    Ht1621WrOneData( disp_data_addr[3][1],disp_data[ a/10 ][1] );///////Ĭ��ֵ0006.000m
    Ht1621WrOneData( 12,1 );	//С����
    a=a%10;//�õ���λ��
    Ht1621WrOneData( disp_data_addr[4][0],disp_data[ a ][0] );
    Ht1621WrOneData( disp_data_addr[4][1],disp_data[ a ][1] );// 
    Ht1621WrOneData( disp_data_addr[5][0],disp_data[ 0 ][0] );
    Ht1621WrOneData( disp_data_addr[5][1],disp_data[ 0 ][1] );//
    Ht1621WrOneData( disp_data_addr[6][0],disp_data[ 0 ][0] );
    Ht1621WrOneData( disp_data_addr[6][1],disp_data[ 0 ][1] );// 
  }
}

void MN_shanshuo_repair(void)//Ϊ��ֹͬʱ����������˸λ
{
  uint  a=0;
  if( MN_shanshuo_cmp!=AB_shanshuo )
  {
      MN_shanshuo_cmp = AB_shanshuo ;
    
      Ht1621WrOneData( 0,8 );//������˾�ı�ʶ  
      Ht1621WrOneData( 9,8+2 ); //������˾�ı�ʶ  //����1/2MN
      Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  	
      Ht1621WrOneData( 13,8 );	//��λ��m
      Ht1621WrOneData( disp_data_addr[0][0],disp_data[ 0 ][0] );
      Ht1621WrOneData( disp_data_addr[0][1],disp_data[ 0 ][1] );//
      Ht1621WrOneData( disp_data_addr[1][0],disp_data[ MN_data/1000 ][0] );
      Ht1621WrOneData( disp_data_addr[1][1],disp_data[ MN_data/1000 ][1] );//
      a=MN_data%1000;//�õ���λ��
      Ht1621WrOneData( disp_data_addr[2][0],disp_data[ a/100 ][0] );
      Ht1621WrOneData( disp_data_addr[2][1],disp_data[ a/100 ][1] );//
      a=a%100; //�õ���λ��  
      Ht1621WrOneData( disp_data_addr[3][0],disp_data[ a/10 ][0] );
      Ht1621WrOneData( disp_data_addr[3][1],disp_data[ a/10 ][1] );///////Ĭ��ֵ0006.000m
      Ht1621WrOneData( 12,1 );	//С����
      a=a%10;//�õ���λ��
      Ht1621WrOneData( disp_data_addr[4][0],disp_data[ a ][0] );
      Ht1621WrOneData( disp_data_addr[4][1],disp_data[ a ][1] );// 
      Ht1621WrOneData( disp_data_addr[5][0],disp_data[ 0 ][0] );
      Ht1621WrOneData( disp_data_addr[5][1],disp_data[ 0 ][1] );//
      Ht1621WrOneData( disp_data_addr[6][0],disp_data[ 0 ][0] );
      Ht1621WrOneData( disp_data_addr[6][1],disp_data[ 0 ][1] );//  
  }
}
/* ����ѡ��ֻ��һ����˸λ�����Բ��ô˺���
void FeatureSelection_shanshuo_repair(void)//Ϊ��ֹͬʱ����������˸λ
{  
}
*/

void Position_shanshuo_repair(void)//Ϊ��ֹͬʱ����������˸λ
{
    if( Position_shanshuo_cmp!=Position_shanshuo )
    {
          Position_shanshuo_cmp = Position_shanshuo ;
          
          Ht1621WrOneData( disp_data_addr[0][0],disp_data[ Position_data[0] ][0] );
   	  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ Position_data[0] ][1] );//
   	  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ Position_data[1] ][0] );
   	  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ Position_data[1] ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ Position_data[2] ][0]  ); 
   	  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ Position_data[2] ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ Position_data[3] ][0] + 8 ); // ��������š�
   	  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ Position_data[3] ][1] );////
   	  
	  Ht1621WrOneData( 12,1 );	//С����
   	  
   	  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ Position_data[4] ][0] );
   	  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ Position_data[4] ][1] );// 
   	  Ht1621WrOneData( disp_data_addr[5][0],disp_data[ Position_data[5] ][0] );
   	  Ht1621WrOneData( disp_data_addr[5][1],disp_data[ Position_data[5] ][1] );//
   	  Ht1621WrOneData( disp_data_addr[6][0],disp_data[ Position_data[6] ][0] );
   	  Ht1621WrOneData( disp_data_addr[6][1],disp_data[ Position_data[6] ][1] );//  
    }
}



