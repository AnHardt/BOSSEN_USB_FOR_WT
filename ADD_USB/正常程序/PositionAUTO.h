
//////////////////////////////////// �������� /////////////////////////////////////
void ZhuangHaoAutomaticallyIncreases(void);
void SetScaleForPosition(unsigned char sign);
void ZhuangHao_RST(void);

void ZhuangHaoAutomaticallyIncreases_FeatureSelection_1(void);
void SetScaleForPosition_FeatureSelection_1(unsigned char sign);
void ZhuangHao_RST_FeatureSelection_1(void);
void CheckFeatureSelection(void);
void Position_shanshuo_Control( unsigned char sign );
//void Position_shanshuo_Control_For_0( unsigned char sign );
void ZhuangHaoAutomaticallyIncreases_FeatureSelection_0(void);//����ѡ��0
void ZhuangHao_RST_FeatureSelection_0(void);
////////////////////////////////////// END ////////////////////////////////////////

/*********************************************************************************
�������ƣ�void ZhuangHaoAutomaticallyIncreases(void)
�������ܣ���ѹ�洢������׮���Զ��� 1 ��
����ʱ�䣺2010-05-15
˵    ����
*********************************************************************************/
void ZhuangHaoAutomaticallyIncreases(void)
{
  
  if( FeatureSelection_data==0 )
  {
    ZhuangHaoAutomaticallyIncreases_FeatureSelection_0( );
  }
  else
    if( FeatureSelection_data==1 )
    {
      ZhuangHaoAutomaticallyIncreases_FeatureSelection_1( );
    }
    else
      if( FeatureSelection_data==2 )
      {
        ZhuangHaoAutomaticallyIncreases_FeatureSelection_1( );
      }
      else
      {
        ZhuangHaoAutomaticallyIncreases_FeatureSelection_1( );
      }
  /*
  if( FeatureSelection_data==0 )
  {
    ZhuangHaoAutomaticallyIncreases_FeatureSelection_0( );
  }
  if( FeatureSelection_data==1 )
  {
    ZhuangHaoAutomaticallyIncreases_FeatureSelection_1( );
  }
  if( FeatureSelection_data==2 )
  {
        ZhuangHaoAutomaticallyIncreases_FeatureSelection_1( );
  }
  if( FeatureSelection_data==3 )
  {
        ZhuangHaoAutomaticallyIncreases_FeatureSelection_1( );
  }
  */
}

void ZhuangHaoAutomaticallyIncreases_FeatureSelection_0(void)//����ѡ��0
{
  uchar *pk;
  uint  num=0;
  Position_data[6] = Position_data[6] + 1 ;
  if( Position_data[6]>3 )
  {
    Position_data[6] = 1;
    num = Position_data[2]*10 + Position_data[3];
    num = num + 1;
    if( (num>=1)&&(num<=99) )
    {
      pk=Decomposition( num );
      Position_data[2] = *(pk+1);
      Position_data[3] = *(pk+0);
      PositionRecordRun.PositionOu_InFeatureSelection_0 = num;
    }
  }
  PositionRecordRun.PositionA_InFeatureSelection_0 = Position_data[6];
}

void ZhuangHaoAutomaticallyIncreases_FeatureSelection_1(void)//����ѡ��1
{
  uchar *pk;
  uint  num=0;
  num = Position_data[4]*100 + Position_data[5]*10 + Position_data[6] + 1;  //  ע���� 1  
  if( (num>=1)&&(num<=999) )
  {
    pk=Decomposition( num );
    Position_data[6] = *(pk+0);
    Position_data[5] = *(pk+1);
    Position_data[4] = *(pk+2);
    PositionRecordRun.PositionA_InFeatureSelection_1 = num ;
  }
}

/*******************************************************************************
�������ƣ� void SetScaleForPosition(unsigned char sign)
�������ܣ� �Ե�ź�׮�ŵ���ֵ��Χ�����趨
ʱ    �䣺 2010-05-21
˵    ���� 1�����������sign---0���Ӳ�����1��������
           2��
*******************************************************************************/
void SetScaleForPosition(unsigned char sign)
{
  if( FeatureSelection_data==0 )
  {
    SetScaleForPosition_FeatureSelection_1( sign );
  }
  else
    if( FeatureSelection_data==1 )
    {
      SetScaleForPosition_FeatureSelection_1( sign );
    }
    else
      if( FeatureSelection_data==2 )
      {
        SetScaleForPosition_FeatureSelection_1( sign );
      }
      else
      {
        SetScaleForPosition_FeatureSelection_1( sign );
      }
}

void SetScaleForPosition_FeatureSelection_1(unsigned char sign)//�趨��ź�׮�ŵķ�Χ��Ҫ�� 1-999
{ 
  ///����Ҫ�󣺸���λ�ķ�Χ�� 0-9
  if( Position_data[ Position_shanshuo ]>9 )
      Position_data[ Position_shanshuo ]=0;
  if( Position_data[ Position_shanshuo ]<0 )
      Position_data[ Position_shanshuo ]=9;
  /////�ر�Ҫ�����ü� ���� ��ѹ�洢 �Զ���1ʱ������10 20 ����������������λͬ����0 ����Ҳ�ǺϷ��ģ����Ա�������ر𱣻�����
  if( (sign==0)&&(Position_data[ Position_shanshuo ]==0) )
  {
      if( Position_shanshuo==3 )//��ŵĸ�λ����˸
      {
          if( (Position_data[1]==0)&&(Position_data[2]==0) )//�����ŵİ�λ��ʮλҲΪ 0
          {
                Position_data[ Position_shanshuo ]=1;
          }
      }
      else
          if( Position_shanshuo==6 )//׮�ŵĸ�λ��˸
          {
              if( (Position_data[4]==0)&&(Position_data[5]==0) )//��� ׮�ŵİ�λ��ʮλҲΪ 0
              {
                  Position_data[ Position_shanshuo ]=1;
              }
          }
  }
  /////////�ر�Ҫ�󣺵�ź�׮�ţ�����СֵΪ 1 �����ԣ�һ����ѹ�����ü�������0��ô�죿������д���
  if( (sign==1)&&(Position_data[ Position_shanshuo ]==0) )//���ü�
  {
      if( Position_shanshuo==3 )//��ŵĸ�λ����˸
      {
          if( (Position_data[1]==0)&&(Position_data[2]==0) )//�����ŵİ�λ��ʮλҲΪ 0
          {
                Position_data[ Position_shanshuo ]=9;
          }
      }
      else
          if( Position_shanshuo==6 )//׮�ŵĸ�λ��˸
          {
              if( (Position_data[4]==0)&&(Position_data[5]==0) )//��� ׮�ŵİ�λ��ʮλҲΪ 0
              {
                  Position_data[ Position_shanshuo ]=9;
              }
          }
  }
}

/*******************************************************************************
�������ƣ� void ZhuangHao_RST(void)
�������ܣ� ����š���ű仯��׮�Ÿ�λΪ 001
����ʱ�䣺 2010-2-20
�޸�ʱ�䣺 2010-07-19
˵��    �� 1��Position_shanshuo = 0  ����š�
           2��Position_shanshuo = 1��2 ��3  ���
           3��ֻ��Թ���ѡ��1
*******************************************************************************/
void ZhuangHao_RST(void)
{
  if( FeatureSelection_data==0 )
  {
    ZhuangHao_RST_FeatureSelection_0( );
  }
  else
    if( FeatureSelection_data==1 )
    {
      ZhuangHao_RST_FeatureSelection_1( );
    }
    else
      if( FeatureSelection_data==2 )
      {
        ZhuangHao_RST_FeatureSelection_1( );
      }
      else
      {
        ZhuangHao_RST_FeatureSelection_1( );
      }
}

void ZhuangHao_RST_FeatureSelection_0(void)
{//��Ϊֻ�����������˸�����ң���λһ�������Ӽ����㣬��������O��ź�A�����Ϊ��ʼ̬
  //uchar *pk;
  if( Position_shanshuo == 0 )
  {
    Position_data[1]=0;
    Position_data[2]=0;
    Position_data[3]=1;
    Position_data[4]=0;
    Position_data[5]=0;
    Position_data[6]=1;
    PositionRecordRun.PositionOu_InFeatureSelection_0 = Position_data[2]*10 + Position_data[3];
    PositionRecordRun.PositionA_InFeatureSelection_0 = Position_data[6];
  }
}

void ZhuangHao_RST_FeatureSelection_1(void)
{
  if( (Position_shanshuo>=0)&&(Position_shanshuo<=3) )
    {
      Position_data[4] = 0;
      Position_data[5] = 0;
      Position_data[6] = 1;
      PositionRecordRun.PositionA_InFeatureSelection_1 = 1;
    }
  
}

////////////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
�������ƣ� void CheckFeatureSelection(void)
�������ܣ� ���������ʲô����ѡ�񣬲��ҶԵ������Position_data��7�����г�ʼ��
����ʱ�䣺 2010-07-19
�޸�ʱ�䣺 2010-07-19
˵��    �� 1���ú���ʹ����   FeatureSelection();���ð����������         
*******************************************************************************/
void CheckFeatureSelection(void)
{
  uchar *pk;
  if( FeatureSelection_data==0 )
  {
    //Position_data[7]={0,0,0,1,0,0,1};
    Position_data[0] = PositionRecordRun.NumberOfXiangDao;
    Position_data[1]=0;
    Position_data[2] = PositionRecordRun.PositionOu_InFeatureSelection_0 /10;
    Position_data[3] = PositionRecordRun.PositionOu_InFeatureSelection_0 %10;
    Position_data[4]=0;
    Position_data[5]=0;
    Position_data[6] = PositionRecordRun.PositionA_InFeatureSelection_0;//1,2,3
  }
  else
    if( FeatureSelection_data==1 )
    {      
      Position_data[0] = PositionRecordRun.NumberOfXiangDao;
      pk=Decomposition( PositionRecordRun.PositionOu_InFeatureSelection_1 );
      Position_data[3] = *(pk+0);
      Position_data[2] = *(pk+1);
      Position_data[1] = *(pk+2);
      pk=Decomposition( PositionRecordRun.PositionA_InFeatureSelection_1 );
      Position_data[6] = *(pk+0);
      Position_data[5] = *(pk+1);
      Position_data[4] = *(pk+2);
    }
    else
      if( FeatureSelection_data==2 )
      {
        Position_data[0] = PositionRecordRun.NumberOfXiangDao;
        pk=Decomposition( PositionRecordRun.PositionOu_InFeatureSelection_2 );
        Position_data[3] = *(pk+0);
        Position_data[2] = *(pk+1);
        Position_data[1] = *(pk+2);
        pk=Decomposition( PositionRecordRun.PositionA_InFeatureSelection_2 );
        Position_data[6] = *(pk+0);
        Position_data[5] = *(pk+1);
        Position_data[4] = *(pk+2);
      }
      else// ==3
      {
        Position_data[0] = PositionRecordRun.NumberOfXiangDao;
        pk=Decomposition( PositionRecordRun.PositionOu_InFeatureSelection_3 );
        Position_data[3] = *(pk+0);
        Position_data[2] = *(pk+1);
        Position_data[1] = *(pk+2);
        pk=Decomposition( PositionRecordRun.PositionA_InFeatureSelection_3 );
        Position_data[6] = *(pk+0);
        Position_data[5] = *(pk+1);
        Position_data[4] = *(pk+2);
      }
}

/*******************************************************************************
�������ƣ� void Position_shanshuo_Control(void)
�������ܣ� ���������ʲô����ѡ�񣬲��Ҷ���˸λ���з�Χ���ƽ��г�ʼ��
����ʱ�䣺 2010-07-19
�޸�ʱ�䣺 2010-07-19
˵��    �� 1���ú���ʹ���� 
           2�����������sign---0���Ӳ�����1��������
*******************************************************************************/
void Position_shanshuo_Control( unsigned char sign )
{
  if( FeatureSelection_data==0 )
  {
    //Position_shanshuo_Control_For_0( sign );
  }
  else
    if( FeatureSelection_data==1 )
    {
      
    }
    else
      if( FeatureSelection_data==2 )
      {
        
      }
      else// ==3
      {
        
      }
}
/*
void Position_shanshuo_Control_For_0( unsigned char sign )//����ѡ�� 0
{//ֻ�����޸�����ţ���˸������ߵ�һλ�����ұ����һλ
  Position_shanshuo = 0;  
}
*/