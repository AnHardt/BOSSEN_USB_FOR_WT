


#define RealVol_A0  (((float)(MCU_Ref)*(float)(A0result))/((float)(4095)))
#define RealVol_A1  (((float)(MCU_Ref)*(float)(A1result))/((float)(4095)))

#define FULL0 1200///��һ�����棬�����ѹΪ 1.2 ��
#define FULL1 1200///�� 2 �����棬�����ѹΪ 1.2 ��


void ArtificialGain_TEST(void);

void AutoZengyi_PortInit(void);//���ų�ʼ����ȫΪ��
void AutoZengyi(void);
void ZengYiTEST(void);

void AutoZengyi(void)
{
  unsigned char zengyi = 0;
  /*
  if( AutoZengYiRun.ZengYi_Ever_Used == 0 )
    GAIN_AUTO( ZengYi_MAX );
  */
  //AutoZengyi_PortInit();
  AutoZengYiRun.which_grade_yichu = 0;
  
  if( RealVol_A0 > FULL0 )//1
  {
      AutoZengYiRun.which_grade_yichu = 1;      
      /*
          zengyi = 9;
          GAIN_AUTO( zengyi );      
          do
          {
              zengyi--;
              GAIN_AUTO( zengyi );
          }while( (RealVol_A0 > FULL0)&&(zengyi>6) );
      */
      zengyi = ZengYi_disp;
      zengyi--;
      /*
      if( zengyi<0 )
        zengyi = 0;
      */
      GAIN_AUTO( zengyi ); 
          
          if( RealVol_A0 > FULL0 )
            AutoZengYiRun.which_grade_yichu = 1;
          else
            AutoZengYiRun.which_grade_yichu = 0;
      
  }
  if( AutoZengYiRun.which_grade_yichu == 0 )//�����һ��û�����
  {
      if( RealVol_A1 > FULL1 )
      {
          AutoZengYiRun.which_grade_yichu = 2;
          /*
          zengyi = 6;
          GAIN_AUTO( zengyi );          
          do
          {
              zengyi--;
              GAIN_AUTO( zengyi );
          }while( (RealVol_A1 > FULL1)&&(zengyi>3) );///
          */
          
          zengyi = ZengYi_disp;
          zengyi--;
          /*
          if( zengyi<0 )
            zengyi = 0;
          */
          GAIN_AUTO( zengyi );          
          
          if( RealVol_A1 > FULL1 )
              AutoZengYiRun.which_grade_yichu = 2;
          else
              AutoZengYiRun.which_grade_yichu = 0;
      }
  }
  if( AutoZengYiRun.which_grade_yichu == 0 )//�����1�� 2��û�����
  {
      if( VolNOFiltering()>=FullData )//3
      {
          AutoZengYiRun.which_grade_yichu = 3;
          //zengyi = ZengYi_MAX;
          /*
          zengyi = 3;
          GAIN_AUTO( zengyi );          
          do
          {
              zengyi--;
              GAIN_AUTO( zengyi );
          }while( (VolNOFiltering()>=FullData )&&(zengyi>0) );///
          */
          
          zengyi = ZengYi_disp;
          zengyi--;
          /*
          if( zengyi<0 )
            zengyi = 0;
          */
          GAIN_AUTO( zengyi );
          
          if( VolNOFiltering()>=FullData  )
              AutoZengYiRun.which_grade_yichu = 3;
          else
              AutoZengYiRun.which_grade_yichu = 0;
      }
  }  
}

void AutoZengyi_PortInit(void)//���ų�ʼ����ȫΪ��
{
  A0_H;
  A1_H;
  A3_H;
  A2_H;
  A4_H;
  A5_H;
}



void ArtificialGain_TEST(void)//�ֶ����������ж�
{
  //uchar tt=0;
  AutoZengYiRun.which_grade_yichu = 0;
  if( RealVol_A0 > FULL0 )//1
  {
      AutoZengYiRun.which_grade_yichu = 1;
      AutoZengYiRun.NO1_GAIN = 1;
  }
  else//������������ʶ����
  {
      AutoZengYiRun.which_grade_yichu = 0;
      AutoZengYiRun.NO1_GAIN = 0;
  }
  //////////////////////////////////////////////////////
  if( RealVol_A1 > FULL1 )//2
  {
      AutoZengYiRun.which_grade_yichu = 2;
      AutoZengYiRun.NO2_GAIN = 1;
  }
  else
  {
      AutoZengYiRun.which_grade_yichu = 0;
      AutoZengYiRun.NO2_GAIN = 0;
  }
  ////////////////////////////////////////////////////
  if( VolNOFiltering()>=FullData )//3
  {
      AutoZengYiRun.which_grade_yichu = 3;
      AutoZengYiRun.NO3_GAIN = 1;
  }
  else
  {
      AutoZengYiRun.which_grade_yichu = 0;
      AutoZengYiRun.NO3_GAIN = 0;    
  }
  /////////////////////////////////
  if( AutoZengYiRun.which_grade_yichu != 0 )
  {
      if( AutoZengYiRun.loop==0 )
      {
          
          if( AutoZengYiRun.NO1_GAIN==1 )
              AutoZengYiRun.loop = (AutoZengYiRun.NO1_GAIN<<2);
          if( AutoZengYiRun.NO2_GAIN==1 )
              AutoZengYiRun.loop = AutoZengYiRun.loop + (AutoZengYiRun.NO2_GAIN<<1);
          if( AutoZengYiRun.NO3_GAIN==1 )
              AutoZengYiRun.loop = AutoZengYiRun.loop + (AutoZengYiRun.NO3_GAIN<<0);
      }
      if( AutoZengYiRun.loop!=0 )
      {        
          AutoZengYiRun.iloop++;
          if( AutoZengYiRun.iloop == 1 )
          {
              if( AutoZengYiRun.loop&0x01 == 1 )
                  AutoZengYiRun.which_grade_yichu = 3;
              else
              {
                  AutoZengYiRun.iloop++;
                  if( (AutoZengYiRun.loop&0x02)>>1 == 0x01 )
                      AutoZengYiRun.which_grade_yichu = 2;
                  else
                  {
                      AutoZengYiRun.iloop++;
                      if( (AutoZengYiRun.loop&0x04)>>2 == 0x01 )
                          AutoZengYiRun.which_grade_yichu = 1;
                      
                  }
              }
          }
          if( AutoZengYiRun.iloop == 2 )
          {
              if( (AutoZengYiRun.loop&0x02)>>1 == 0x01 )
                  AutoZengYiRun.which_grade_yichu = 2;
              else
              {
                   AutoZengYiRun.iloop++;
                   if( (AutoZengYiRun.loop&0x04)>>2 == 0x01 )
                       AutoZengYiRun.which_grade_yichu = 1;
              }
          }
          if( AutoZengYiRun.iloop == 3 )
          {
              if( (AutoZengYiRun.loop&0x04)>>2 == 0x01 )
                  AutoZengYiRun.which_grade_yichu = 1;
          }
          if( AutoZengYiRun.iloop == 3 )//���һ��ѭ��������
          {  
              AutoZengYiRun.iloop = 0 ;
              AutoZengYiRun.loop = 0 ;
          }
      }
  }
}


/*********************************************************************************************************
�������ƣ�void ZengYiTEST(void)
�������ܣ����淽ʽ�ļ��
˵    ����һ���������淽ʽ��1���Զ����棻2���ֶ����档
          �����ú����� Vol_Disp(signed long vol) �б����ã�
����ʱ�䣺2010-07-12
�޸�ʱ�䣺
*********************************************************************************************************/
void ZengYiTEST(void)
{
  if( AutoZengYiRun.ZengYi_Ever_Used == 0 )//�Զ�������Ч
    AutoZengyi();
  if( AutoZengYiRun.ZengYi_Ever_Used == 1 )//�ֶ�������Ч
    ArtificialGain_TEST();
}
