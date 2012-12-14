/*============================================ ͷ�ļ�˵�� ============================================================
ͷ�ļ����ƣ�
ͷ�ļ���;��������Ƭ��
================================================ END ===============================================================*/

//*********************************************   ��������   **********************************************
void Disp_0_9(void);
void Started(void);
void aStatic_Show(void);
void First_Check(void);
void PositionRecordInit(void);
void ShowNextPosition(void);
void ShowCurrentPosition(void);
//*************************************************** END *************************************************

/*******************************************************************************
�������ƣ� void Disp_0_9(void)
�������ܣ� ������7�������ͳһ��ʾ 0-9
˵��    �� 
*******************************************************************************/
void Disp_0_9(void)
{
  unsigned char i;
  HT1621_all_off();
  Ht1621WrOneData( 0,8 );//������˾�ı�ʶ 
  Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ 
  Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  
  Ht1621WrOneData( 12,1 );	//С����
  for(i=0;i<10;i++)
  //for(j=0;j<10;j++)
  {
      Ht1621WrOneData( disp_data_addr[0][0],disp_data[i][0] );
      Ht1621WrOneData( disp_data_addr[0][1],disp_data[i][1] );//��һ�� 8
      Ht1621WrOneData( disp_data_addr[1][0],disp_data[i][0] );
  	 Ht1621WrOneData( disp_data_addr[1][1],disp_data[i][1] );//��2�� 8
	 Ht1621WrOneData( disp_data_addr[2][0],disp_data[i][0] );
  	 Ht1621WrOneData( disp_data_addr[2][1],disp_data[i][1] );//��3�� 8
	 Ht1621WrOneData( disp_data_addr[3][0],disp_data[i][0] );
  	 Ht1621WrOneData( disp_data_addr[3][1],disp_data[i][1] );//��4�� 8
	 Ht1621WrOneData( disp_data_addr[4][0],disp_data[i][0] );
  	 Ht1621WrOneData( disp_data_addr[4][1],disp_data[i][1] );//��5�� 8
	 Ht1621WrOneData( disp_data_addr[5][0],disp_data[i][0] );
  	 Ht1621WrOneData( disp_data_addr[5][1],disp_data[i][1] );//��6�� 8
	 Ht1621WrOneData( disp_data_addr[6][0],disp_data[i][0] );
  	 Ht1621WrOneData( disp_data_addr[6][1],disp_data[i][1] );//��7�� 8
	 //DelayMS(7000);
    DelayMS(4000);	 
  }
}
/*******************************************************************************
�������ƣ� void Started(void)
�������ܣ� ��������ʾ���0-9��ֹͣ�ڴ�״̬
˵��    �� ���ֻ�0����˸2��
*******************************************************************************/
void Started(void)
{
   uchar j=0;
   HT1621_all_off();
   Ht1621WrOneData( 0,8 );//������˾�ı�ʶ 
   Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ 
   Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  
   DelayMS(9000);   
   for( j=0;j<7;j++ )
   {
      Ht1621WrOneData( disp_data_addr[j][0],disp_data[0][0] );
	  Ht1621WrOneData( disp_data_addr[j][1],disp_data[0][1] );
   }
   Ht1621WrOneData( 12,1 );	//С����
   DelayMS(9000);
   HT1621_all_off();
   
   Ht1621WrOneData( 0,8 );//������˾�ı�ʶ 
   Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ 
   Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  
   DelayMS(9000);
   for( j=0;j<7;j++ )
   {
      Ht1621WrOneData( disp_data_addr[j][0],disp_data[0][0] );
	  Ht1621WrOneData( disp_data_addr[j][1],disp_data[0][1] );
   }
   Ht1621WrOneData( 12,1 );	//С����
}

/*********************************************************************************************************
�������ƣ�void Static_Show(void)
�������ܣ���̬��ʾ 7 ����0��
˵    ����
ʱ    �䣺2010-02-28
*********************************************************************************************************/
void aStatic_Show(void)
{
   uchar j=0;
   Ht1621WrOneData( 0,8 );//������˾�ı�ʶ 
   Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ 
   Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  
   for( j=0;j<7;j++ )
   {
      Ht1621WrOneData( disp_data_addr[j][0],disp_data[0][0] );
	  Ht1621WrOneData( disp_data_addr[j][1],disp_data[0][1] );
   }
   Ht1621WrOneData( 12,1 );	//С����
}

/*********************************************************************************************************
�������ƣ�void First_Check(void)
�������ܣ������Լ�
ʱ    �䣺2010-02-28
˵    ����1����ȡ��Ƭ���ڲ� Flash �����ݣ����Ҷ�����г�ʼ����
          2����ȡ SD ���ڵ���ؼ�¼��Ϣ��
*********************************************************************************************************/
void First_Check(void)
{
  //uchar i=0;
  //uchar pig[64];
  /*
  read_array((uchar *)BIAOXIAO_save, &memory[0],64);//---->�����󣬽���Ϣ���� memory[64]
  if( memory[0]==255 )//��һ�ο���
  {
    for( i=0;i<64;i++ )
      memory[i]=0;
    Write_Flash_String(BIAOXIAO_save,memory,128);
  }
  */
  ///////////////////////////////////////////////////////////////////////
  AutoZengYiRun.which_grade_yichu = 0;//�Զ�����ĳ�ʼ��
  AutoZengYiRun.ZengYi_Ever_Used = 0;
  //////////////////////////////////////////////////////////////////////
  PositionRecordInit( );//��ŵ���ʱ��¼����ʼ��  
}

void PositionRecordInit(void)//��ŵ���ʱ��¼����ʼ��
{
  PositionRecordRun.PositionOu_InFeatureSelection_0 = 1;
  PositionRecordRun.PositionA_InFeatureSelection_0 = 1;
  PositionRecordRun.PositionOu_InFeatureSelection_1 = 1;
  PositionRecordRun.PositionA_InFeatureSelection_1 = 1;
  PositionRecordRun.PositionOu_InFeatureSelection_2 = 1;
  PositionRecordRun.PositionA_InFeatureSelection_2 = 1;
  PositionRecordRun.PositionOu_InFeatureSelection_3 = 1;
  PositionRecordRun.PositionA_InFeatureSelection_3 = 1;
  PositionRecordRun.NumberOfXiangDao = 0;
}

/*********************************************************************************************************
�������ƣ�void ShowNextPosition(void)
�������ܣ���ѹ���洢����������ʾ��һ����ţ�����ʾȫ0----
����ʱ�䣺2010-09-06
�޸�ʱ�䣺
˵    ����1���ں��� SaveUseWorkStop(void) ��ʹ�ã�
*********************************************************************************************************/
void ShowNextPosition(void)
{
  //uchar j=0;
  Ht1621WrOneData( 0,8 );//������˾�ı�ʶ 
  Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ 
  Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ 
  /*
  for( j=0;j<7;j++ )
  {
    Ht1621WrOneData( disp_data_addr[j][0],disp_data[ Position_data[j] ][0] );
    Ht1621WrOneData( disp_data_addr[j][1],disp_data[ Position_data[j] ][1] );
  }
  */
  Ht1621WrOneData( disp_data_addr[0][0],disp_data[ Position_data[0] ][0] );
  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ Position_data[0] ][1] );//
  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ Position_data[1] ][0] );
  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ Position_data[1] ][1] );//
   	  
  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ Position_data[2] ][0]  ); 
  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ Position_data[2] ][1] );//
   	  
  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ Position_data[3] ][0] + 8 ); // ��������š�
  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ Position_data[3] ][1] );//
   	  
  Ht1621WrOneData( 12,1 );	//С����
   	  
  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ Position_data[4] ][0]  ); //  
  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ Position_data[4] ][1] );// 
  Ht1621WrOneData( disp_data_addr[5][0],disp_data[ Position_data[5] ][0] );
  Ht1621WrOneData( disp_data_addr[5][1],disp_data[ Position_data[5] ][1] );//
  Ht1621WrOneData( disp_data_addr[6][0],disp_data[ Position_data[6] ][0] );
  Ht1621WrOneData( disp_data_addr[6][1],disp_data[ Position_data[6] ][1] );//
}

/*********************************************************************************************************
�������ƣ�void ShowCurrentPosition(void)
�������ܣ���ѹ������ͣ����������ʾ��ǰ�ĵ�ţ�����ʾȫ0----
����ʱ�䣺2010-09-06
�޸�ʱ�䣺
˵    ����1���ں��� key_use1(void) ��ʹ�ã�
*********************************************************************************************************/
void ShowCurrentPosition(void)
{
  Ht1621WrOneData( 0,8 );//������˾�ı�ʶ 
  Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ 
  Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ 
  ////
  Ht1621WrOneData( disp_data_addr[0][0],disp_data[ Position_data[0] ][0] );
  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ Position_data[0] ][1] );//
  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ Position_data[1] ][0] );
  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ Position_data[1] ][1] );//   	  
  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ Position_data[2] ][0]  ); 
  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ Position_data[2] ][1] );//   	  
  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ Position_data[3] ][0] + 8 ); // ��������š�
  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ Position_data[3] ][1] );//   	  
  Ht1621WrOneData( 12,1 );	//С����   	  
  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ Position_data[4] ][0]  ); //  
  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ Position_data[4] ][1] );// 
  Ht1621WrOneData( disp_data_addr[5][0],disp_data[ Position_data[5] ][0] );
  Ht1621WrOneData( disp_data_addr[5][1],disp_data[ Position_data[5] ][1] );//
  Ht1621WrOneData( disp_data_addr[6][0],disp_data[ Position_data[6] ][0] );
  Ht1621WrOneData( disp_data_addr[6][1],disp_data[ Position_data[6] ][1] );//
}