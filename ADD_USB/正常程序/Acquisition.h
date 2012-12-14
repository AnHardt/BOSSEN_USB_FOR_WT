/*============================================ ͷ�ļ�˵�� ============================================================
ͷ�ļ����ƣ�Acquisition.h
ͷ�ļ���;���ɼ�����
ʱ      �䣺2010-02-27
================================================ END ===============================================================*/

#ifndef __Acquisition_H
#define __Acquisition_H

//*********************************************   ��������   **********************************************
void PositionShow(void);
void CurrentShow( signed long  current_xiuzheng );
//void ClockShow(void);
void AcquisitionControl(void);
void WorkOnControl(void);
//*************************************************** END *************************************************

/**********************************************************************************************
�������ƣ�void PositionShow(void)
�������ܣ���ʾĳ�����
˵    ����1���ú������롱��š��������ʹ��
ʱ    �䣺2010-02-27
**********************************************************************************************/
void PositionShow(void)
{
    if( Save_Flag==0 )//û�а�ѹ���洢�������ߴ洢û�н���
    {
          Ht1621WrOneData( disp_data_addr[0][0],disp_data[ Position_data[0] ][0] );
   	  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ Position_data[0] ][1] );//
   	  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ Position_data[1] ][0] );
   	  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ Position_data[1] ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ Position_data[2] ][0]  ); 
   	  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ Position_data[2] ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ Position_data[3] ][0] + 8 ); // ��������š�
   	  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ Position_data[3] ][1] );//
   	  
	  Ht1621WrOneData( 12,1 );	//С����
   	  
   	  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ Position_data[4] ][0] );
   	  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ Position_data[4] ][1] );// 
   	  Ht1621WrOneData( disp_data_addr[5][0],disp_data[ Position_data[5] ][0] );
   	  Ht1621WrOneData( disp_data_addr[5][1],disp_data[ Position_data[5] ][1] );//
   	  Ht1621WrOneData( disp_data_addr[6][0],disp_data[ Position_data[6] ][0] );
   	  Ht1621WrOneData( disp_data_addr[6][1],disp_data[ Position_data[6] ][1] );//
          
          Ht1621WrOneData( 13,0 );//��λ��mV---�ص�
    }
    else
    {
          Ht1621WrOneData( disp_data_addr[0][0],disp_data[ Position_data[0] ][0] );
   	  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ Position_data[0] ][1] );//
   	  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ Position_data[1] ][0] );
   	  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ Position_data[1] ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ Position_data[2] ][0]  ); 
   	  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ Position_data[2] ][1] );//
   	  
   	  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ 0 ][0] + 8 ); // ��������š�
   	  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ 0 ][1] );//
   	  
	  Ht1621WrOneData( 12,1 );	//С����
   	  
   	  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ Position_data[4] ][0] + 8 ); //   + "����"
   	  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ Position_data[4] ][1] );// 
   	  Ht1621WrOneData( disp_data_addr[5][0],disp_data[ Position_data[5] ][0] );
   	  Ht1621WrOneData( disp_data_addr[5][1],disp_data[ Position_data[5] ][1] );//
   	  Ht1621WrOneData( disp_data_addr[6][0],disp_data[ Position_data[6] ][0] );
   	  Ht1621WrOneData( disp_data_addr[6][1],disp_data[ Position_data[6] ][1] );//
          
          Ht1621WrOneData( 13,0 );//��λ��mV---�ص�
    }
}

/**********************************************************************************************
�������ƣ�void CurrentShow(void)
�������ܣ���ʾ����
˵    ����1���ڡ���������ʱ�������ɼ�ֻȡ�ɵ��ĵ�һ��ֵ
          2��
ʱ    �䣺2010-02-27
**********************************************************************************************/
/*
#define current    (long)( (((float)(MCU_Ref)*(float)(A4result)*1000.0)/((float)(4095)))/((float)(Current_R)) )  //  ֱ�ӻ���ɵ���
#define Current_K   2.1683  //  б��
#define Current_B   6729.8  //  ����
*/
//#define vol_430    (long)( (((float)(MCU_Ref)*(float)(A4result))/((float)(4095))) )
//uchar  mmma[8];
#define current_xiuzheng_max  200000  //  ��ֹ��������̫�������
void CurrentShow( signed long  current_xiuzheng )
{
  //long current=1234567;          
  uchar *p;
  uchar i=0;
  
  current_xiuzheng = XiuZheng_Result;
  //current_xiuzheng = ScreenValueForCurrent(  ); //
  //current_xiuzheng = Current_K * current - Current_B;// ��ֵû�б�У������
  /*
  if( biaojiao_cur_sign==0 )  //  �����У������
  {
    current_xiuzheng = current_xiuzheng + biaojiao_cur_chazhi;
  }
  else
  {
    current_xiuzheng = current_xiuzheng - biaojiao_cur_chazhi;
  }
  */
  if( current_xiuzheng<=0 )
  {
    current_xiuzheng = 0;
  }
  if( current_xiuzheng > current_xiuzheng_max )
  {
    current_xiuzheng = current_xiuzheng_max;
  }
  
  if( (Acquisition_flag==1)||(WorkOn_flag==1) )
  {
    if( Cur_Calculate_One_Time == 1 )
    {
      p=Decomposition8( current_xiuzheng );
      Cur_Calculate_One_Time =0;
      for( i=0;i<8;i++ )
      {
        mmma[i]= *(p+i) ;
      }
    }
  }
  else
  {
    p=Decomposition8( current_xiuzheng );
    for( i=0;i<8;i++ )
    {
      mmma[i]= *(p+i) ;
    }
  }
  if( Save_Flag==0 )//û�а�ѹ���洢�������ߴ洢û�н���
  {
    Ht1621WrOneData( disp_data_addr[0][0],disp_data[ mmma[6] ][0] );
    Ht1621WrOneData( disp_data_addr[0][1],disp_data[ mmma[6] ][1] );//
    Ht1621WrOneData( disp_data_addr[1][0],disp_data[ mmma[5] ][0] );
    Ht1621WrOneData( disp_data_addr[1][1],disp_data[ mmma[5] ][1] );//
    Ht1621WrOneData( disp_data_addr[2][0],disp_data[ mmma[4] ][0] );
    Ht1621WrOneData( disp_data_addr[2][1],disp_data[ mmma[4] ][1] );//
    Ht1621WrOneData( disp_data_addr[3][0],disp_data[ mmma[3] ][0] );
    Ht1621WrOneData( disp_data_addr[3][1],disp_data[ mmma[3] ][1] );//
    Ht1621WrOneData( disp_data_addr[4][0],disp_data[ mmma[2] ][0] );
    Ht1621WrOneData( disp_data_addr[4][1],disp_data[ mmma[2] ][1] );//
    Ht1621WrOneData( disp_data_addr[5][0],disp_data[ mmma[1] ][0] );
    Ht1621WrOneData( disp_data_addr[5][1],disp_data[ mmma[1] ][1] );//
    Ht1621WrOneData( disp_data_addr[6][0],disp_data[ mmma[0] ][0] );
    Ht1621WrOneData( disp_data_addr[6][1],disp_data[ mmma[0] ][1] );//
    Ht1621WrOneData( 12,1+2 );	//С����+ma
    Ht1621WrOneData( 13,0 );//��λ��mV---�ص�
    //Ht1621WrOneData( 13,1 );//��λ��mV
  }
  else
  {
    Ht1621WrOneData( disp_data_addr[0][0],disp_data[ mmma[6] ][0] );
    Ht1621WrOneData( disp_data_addr[0][1],disp_data[ mmma[6] ][1] );//
    Ht1621WrOneData( disp_data_addr[1][0],disp_data[ mmma[5] ][0] );
    Ht1621WrOneData( disp_data_addr[1][1],disp_data[ mmma[5] ][1] );//
    Ht1621WrOneData( disp_data_addr[2][0],disp_data[ mmma[4] ][0] );
    Ht1621WrOneData( disp_data_addr[2][1],disp_data[ mmma[4] ][1] );//
    Ht1621WrOneData( disp_data_addr[3][0],disp_data[ mmma[3] ][0] );
    Ht1621WrOneData( disp_data_addr[3][1],disp_data[ mmma[3] ][1] );//
    Ht1621WrOneData( disp_data_addr[4][0],disp_data[ mmma[2] ][0]+8 );  //  + ����
    Ht1621WrOneData( disp_data_addr[4][1],disp_data[ mmma[2] ][1] );//
    Ht1621WrOneData( disp_data_addr[5][0],disp_data[ mmma[1] ][0] );
    Ht1621WrOneData( disp_data_addr[5][1],disp_data[ mmma[1] ][1] );//
    Ht1621WrOneData( disp_data_addr[6][0],disp_data[ mmma[0] ][0] );
    Ht1621WrOneData( disp_data_addr[6][1],disp_data[ mmma[0] ][1] );//
    Ht1621WrOneData( 12,1+2 );	//С����+ma
    Ht1621WrOneData( 13,0 );//��λ��mV---�ص�
  }
}


/**********************************************************************************************
�������ƣ�
�������ܣ���ѹ�ɼ����������Ӧ��ʾ
˵    ����1����ѹ �ɼ� ����ʱ�����ڰ���������ʹ��HT1621_all_off();����
          2����ѹ �ɼ� ����ʱ��Acquisition_flag = 1;  ֱ����ѹ������ͣ���������Ž��丳ֵΪ0
          3��
          4��
ʱ    �䣺2010-02-27
**********************************************************************************************/
//#define     Basic_Time      (500/2)
#define     Basic_Time      (160)
void AcquisitionControl(void)
{
  if( Acquisition_flag==1 )
  {
    Ht1621WrOneData( 0,8 );//������˾�ı�ʶ  
    Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ 
    Ht1621WrOneData( 11,4 );	//������˾�ı�ʶ 
    Ht1621WrOneData( 10,2 );	//�������ɼ���ͼ��
    
    if( AcquisitionTime<=Basic_Time ) 
    {
      PositionShow();//��ʾ���
      Vol_Calculate_One_Time = 1;
      //GAIN_AUTO_MAX(  );
    }
    if( (AcquisitionTime>Basic_Time)&&(AcquisitionTime<=Basic_Time*2) )  Vol_Disp( VolFiltering() );//��ʾ��ѹ��24λAD
    
  }
}


/**********************************************************************************************
�������ƣ�void WorkOnControl(void)
�������ܣ���ѹ�������������������Ӧ��ʾ
˵    ����1����ѹ ���������� ����ʱ�����ڰ���������ʹ��HT1621_all_off();����
          2����ѹ �ɼ� ����ʱ��WorkOn_flag = 1;  ֱ����ѹ������ͣ���������Ž��丳ֵΪ0
          3��
          4��
ʱ    �䣺2010-02-27
**********************************************************************************************/
void WorkOnControl(void)
{
  if( WorkOn_flag==1 )
  {
    if( GUOLIU_Flag==0 )//û�з�������
    {
      FeatureSelection_Port();//Ƶ�ʿ��ƽ������ã�����Ƶ��    
      Ht1621WrOneData( 0,8 );//������˾�ı�ʶ  
      Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ 
      Ht1621WrOneData( 11,4 );	//������˾�ı�ʶ 
      Ht1621WrOneData( 10,4 );	//������������ͼ��
      if( WorkOnTime<=Basic_Time ) 
      {
        PositionShow();//��ʾ���
        Cur_Calculate_One_Time  =  1;
        //GAIN_AUTO_MAX(  );
      }
      if( (WorkOnTime>Basic_Time)&&(WorkOnTime<=Basic_Time*2 -60) )  
      {
        CurrentShow( XiuZheng_Result );//��ʾ����
        Vol_Calculate_One_Time = 1;
      }
      if( (WorkOnTime>Basic_Time*2-60)&&(WorkOnTime<=Basic_Time*3) )  Vol_Disp( VolFiltering() );//��ʾ��ѹ��24λAD
    
      WorkOnControl_L;
    }
  }
  else
  {
    WorkOnControl_H;
  }
}


#endif