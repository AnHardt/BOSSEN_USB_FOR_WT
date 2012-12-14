/*============================================ ͷ�ļ�˵�� ============================================================
ͷ�ļ����ƣ�Battery.h
ͷ�ļ���;��1����ʾ��ص���
            2����ص�Ƿѹ����
            3�����伫�Ĺ�������
˵      ����1��P6.2/A2����ص�ѹ�ɼ��š�
            2����ѹ���裺  ����ѹ������
            3��
ʱ      �䣺2010-02-27
================================================ END ===============================================================*/

//*********************************************   ��������   **********************************************
void Current_Protect(void);
void BatteryShow(void);
void GUOLIU_Show(void);
//*************************************************** END *************************************************


/**********************************************************************************************
�������ƣ�void BatteryShow(void)
�������ܣ���ص�����ʾ
˵    ����1��
          2��
          3��
          4��
����ʱ�䣺2010-02-27
�޸�ʱ�䣺2010-05-19
**********************************************************************************************/
//����5��ֵ����ΪADֵ
#define   bat4    ( ( ((float)(4095))*((float)(12600))*(Proportional_Battery) )/MCU_Ref )//4����Ӧ��ADֵ
#define   bat3    ( ( ((float)(4095))*((float)(12000))*(Proportional_Battery) )/MCU_Ref )//3���
#define   bat2    ( ( ((float)(4095))*((float)(11000))*(Proportional_Battery) )/MCU_Ref )//2���
#define   bat1    ( ( ((float)(4095))*((float)(9500))*(Proportional_Battery) )/MCU_Ref )//1���
#define   bat0    ( ( ((float)(4095))*((float)(9000))*(Proportional_Battery) )/MCU_Ref )//0���
void BatteryShow(void)
{  
  //A2result = bat0-5;////////////////////try
  if( time%199==0 )
  {
  if( A2result>bat4 )
  {
    Ht1621WrOneData( 20,1 );//�����Ȧ
    Ht1621WrOneData( 21,1 );//��ص�4���
    Ht1621WrOneData( 22,1 );//��ص�3���
    Ht1621WrOneData( 23,1 );//��ص�2���
    Ht1621WrOneData( 24,1 );//��ص�1���
  }
  if( (A2result>bat3)&&(A2result<=bat4) )
  {
    Ht1621WrOneData( 20,1 );//�����Ȧ 
    Ht1621WrOneData( 21,0 );//��ص�4���
    Ht1621WrOneData( 22,1 );//��ص�3���
    Ht1621WrOneData( 23,1 );//��ص�2���
    Ht1621WrOneData( 24,1 );//��ص�1���
  }
  if( (A2result>bat2)&&(A2result<=bat3) )
  {
    Ht1621WrOneData( 20,1 );//�����Ȧ
    Ht1621WrOneData( 21,0 );//��ص�4���
    Ht1621WrOneData( 22,0 );//��ص�3���
    Ht1621WrOneData( 23,1 );//��ص�2���
    Ht1621WrOneData( 24,1 );//��ص�1���
  }
  if( (A2result>bat1)&&(A2result<=bat2) )
  {
    Ht1621WrOneData( 20,1 );//�����Ȧ 
    Ht1621WrOneData( 21,0 );//��ص�4���
    Ht1621WrOneData( 22,0 );//��ص�3���
    Ht1621WrOneData( 23,0 );//��ص�2���
    Ht1621WrOneData( 24,1 );//��ص�1���
  }
  if( (A2result>bat0)&&(A2result<=bat1) )
  {
    if( second%2==0 )
    {
      Ht1621WrOneData( 20,1 );//�����Ȧ
      Ht1621WrOneData( 21,0 );//��ص�4���
      Ht1621WrOneData( 22,0 );//��ص�3���
      Ht1621WrOneData( 23,0 );//��ص�2���
      Ht1621WrOneData( 24,0 );//��ص�1���
    }
    else
    {
      Ht1621WrOneData( 20,0 );//�����Ȧ
      Ht1621WrOneData( 21,0 );//��ص�4���
      Ht1621WrOneData( 22,0 );//��ص�3���
      Ht1621WrOneData( 23,0 );//��ص�2���
      Ht1621WrOneData( 24,0 );//��ص�1���
    }
  }
  }
  if( A2result<=bat0 )  //  ��9.0V�Զ��ػ�����Ƭ��P4.7�������
  {//Ƿѹ�����Ų�Ӧ�ñ����ε�������ֻ����ʱ�Ե�
    
    MCU_Start_flag = 0;    //  ��Ƭ���ر�
    QIANYABAOHU;          //  Ƿѹ������,����Ƭ��61�ţ�A2���ɼ����ĵ�ص�ѹ��9Vʱ����͡�
    
    if( second%2==0 )
    {
      Ht1621WrOneData( 20,1 );//�����Ȧ
      Ht1621WrOneData( 21,0 );//��ص�4���
      Ht1621WrOneData( 22,0 );//��ص�3���
      Ht1621WrOneData( 23,0 );//��ص�2���
      Ht1621WrOneData( 24,0 );//��ص�1���
    }
    else
    {
      Ht1621WrOneData( 20,0 );//�����Ȧ
      Ht1621WrOneData( 21,0 );//��ص�4���
      Ht1621WrOneData( 22,0 );//��ص�3���
      Ht1621WrOneData( 23,0 );//��ص�2���
      Ht1621WrOneData( 24,0 );//��ص�1���
    }
  }
}

/**********************************************************************************************
�������ƣ�void Current_Protect(void)
�������ܣ����伫�Ĺ�������
˵    ����1�������ڡ���������
          2��������ǡ�������������������������
ʱ    �䣺2010-02-27
**********************************************************************************************/
void Current_Protect(void)//���ֱ��������Իָ��𣿣���������
{
  /*
  if( WorkOn_flag==1 )
  {
    if( XiuZheng_Result > Current_Max )//��������
    {
      GUOLIU;
      GUOLIU_Flag = 1;
      GUOLIU_Show( );//��ʾ��FULLAAA����
    }
    else
    {
      GUOLIU_Normal;
      GUOLIU_Flag = 0;
    }
  }
  else
  {
    GUOLIU;
  }
  */
  /*
  if( WorkOn_flag==1 )/////2010-10-03 �޸�
  {
    if( XiuZheng_Result > Current_Max )//��������
    {
      GUOLIU;
      GUOLIU_Flag = 1;
      GUOLIU_Show( );//��ʾ��FULLAAA����
    }
    else
    {
      //GUOLIU_Normal;
      GUOLIU;
      GUOLIU_Flag = 0;
    }
  }
  else
  {
    //GUOLIU;
    GUOLIU_Normal;
  }
  */
  if( WorkOn_flag==1 )  //  2010-10-03
  {
    if( XiuZheng_Result > Current_Max )//��������
    {
      GUOLIU;
      GUOLIU_Flag = 1;
      GUOLIU_Show( );//��ʾ��FULLAAA����
    }
    else
    {
      GUOLIU_Normal;
      GUOLIU_Flag = 0;
    }
  }
  else
  {
    GUOLIU;
  }
  
}

/**********************************************************************************************
�������ƣ�void GUOLIU_Show(void)
�������ܣ�����������Ϊ��FULLAAA����
˵    ����
����ʱ�䣺2010-09-06
�޸�ʱ�䣺
**********************************************************************************************/
void GUOLIU_Show(void)
{
          Ht1621WrOneData( disp_data_addr[0][0],7 );
          Ht1621WrOneData( disp_data_addr[0][1],8 );//
          Ht1621WrOneData( disp_data_addr[1][0],5 );
          Ht1621WrOneData( disp_data_addr[1][1],7 );//
          Ht1621WrOneData( disp_data_addr[2][0],5 );
          Ht1621WrOneData( disp_data_addr[2][1],1 );//
          Ht1621WrOneData( disp_data_addr[3][0],5 );
          Ht1621WrOneData( disp_data_addr[3][1],1 );//
          
          Ht1621WrOneData( disp_data_addr[4][0],7 );
          Ht1621WrOneData( disp_data_addr[4][1],14 );//
          Ht1621WrOneData( disp_data_addr[5][0],7 );
          Ht1621WrOneData( disp_data_addr[5][1],14 );//
          Ht1621WrOneData( disp_data_addr[6][0],7 );
          Ht1621WrOneData( disp_data_addr[6][1],14 );//
          Ht1621WrOneData( 13,0 );//��λ��mV
          Ht1621WrOneData( 12,0 );	//С����+ma ���ε�
          Ht1621WrOneData( 10,0 );	//������������ͼ��-���ε�
}
