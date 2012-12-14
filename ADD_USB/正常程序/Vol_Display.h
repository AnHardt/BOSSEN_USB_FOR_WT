/*============================================ ͷ�ļ�˵�� ============================================================
ͷ�ļ����ƣ�Vol_Display.h
ͷ�ļ���;����AD��������ת��������ʾ
��      �ߣ���Ĵ�˵
ʱ      �䣺2010-02-25
================================================ END ===============================================================*/
signed long VolResultEnd(signed long real);
signed long AD2VOL(signed long data);

signed long VolFiltering(void);
signed long VolNOFiltering(void);///Ϊ�Զ�������д



/*******************************************************************************
�������ƣ�signed long AD2VOL(signed long data)
�������ܣ���ADֵ�����ʵ�ʵ�ѹֵ�����棺1
˵    ����signed long �����ݳ�����: -2147483648��+2147483647
��    �ߣ���Ĵ�˵
ʱ    �䣺2010-02-25
*******************************************************************************/
signed long AD2VOL(signed long data)
{
  float ah=0;
  ah = ( (float)(data) )*( (float)(RefInput) );
  //ah = ah>>24;
  ah = ah/( (float)(16777216) );
  return (signed long)(ah);
}

/*******************************************************************************
�������ƣ�signed long VolFiltering(void)
�������ܣ����õ���ʵ�ʵ�ѹ���о�ֵ����
˵    ����1�����˲��ܷ�ʱ��
          2�����ϱ�Уֵ�ļ���
��    �ߣ���Ĵ�˵
ʱ    �䣺2010-02-25
*******************************************************************************/
#define     VolFiltering_count      11
signed long VolFiltering(void)
{
  uchar i=0;
  float sum1=0.0000;
  for( i=0;i<VolFiltering_count;i++ )
  {
    sum1 = sum1+AD2VOL( Read24DataFromAd7710() );//ʵ�ʵ�ѹֵ
  }
  sum1 = sum1/( (float)(VolFiltering_count) );
  sum1 = VolResultEnd( (signed long)(sum1) );
  
  //return (signed long)(sum1);
  return LINEAR( (signed long)(sum1) ) ;
}

/*******************************************************************************
�������ƣ�signed long VolNOFiltering(void)
�������ܣ�����Զ����棬����ʵ�ʵ�ѹ
˵    �����Զ�������Ҫ��ʱ�俪֧�Ƚϴ󣬻�Ӱ�조���������ķ���Ļ��ʾЧ��������
          ��ѹ��ʾ��ʱ��̫�̣�������ʾ�����������ԣ�������ͽ������ֵ�Ĺ���ʡ�ԡ�
          ������ʵAD7711��ѹ��
��    �ߣ���Ĵ�˵
ʱ    �䣺2010-07-10
*******************************************************************************/
signed long VolNOFiltering(void)///Ϊ���Զ�������д
{
  uchar i=0;
  float sum1=0.0000;
  for( i=0;i<1;i++ )
  {
    sum1 = sum1+AD2VOL( Read24DataFromAd7710() );//ʵ�ʵ�ѹֵ
  }
  //sum1 = sum1/( (float)(VolFiltering_count) );
  sum1 = VolResultEnd( (signed long)(sum1) );
  return (signed long)(sum1);
  //return LINEAR( (signed long)(sum1) ) ;
}

signed long VolResultEnd( signed long real )
{
  
  if( real<0 )
  {
    real = 0;
  }
  return real;
}
