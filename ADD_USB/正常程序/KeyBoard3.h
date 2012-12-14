/*============================================ ͷ�ļ�˵�� ============================================================
ͷ�ļ����ƣ�KeyBoard.h
ͷ�ļ���;������ʽ���̣�3��4��
����ʱ��  ��2010-02-18
˵��	  ��P2.6----��1��
		  	P2.5----��2��
			P2.4----��3��
			P2.3----��4��
			P2.2----��3��
			P2.1----��2��
			P2.0----��1��
================================================ END ===============================================================*/

//*********************************************   ��������   **********************************************
void keyboard_RST(void);
void FeatureSelectionPortReset(void);
void key_flag_del(void);
void key_time_calculate(void);
void key_scan(void);
void key_use1(void);
void key_use(void);
void SaveUseWorkStop(void);
//*************************************************** END *************************************************

/*******************************************************************************************************
�������ƣ�	void key_RST(void)
�������ܣ�	���̸�λ
�޸����ڣ�      2010-02-28
˵    ����      1����ֵ keyboard_value ����
��              2��������ʱ�� 
*******************************************************************************************************/
void keyboard_RST(void)
{
  keytime_start	 = 0;//�رռ�ʱ���˴���Ϊ�˱�֤���������£�����ֵ������仯
  keyboard_value = 0; 
  keytime	 = 0;
  keytime_save   = 0;  
  keylong_flag   = 0;
}

/*******************************************************************************************************
�������ƣ�	void key_flag_del(void)
�������ܣ�	������̵ı�־λ
�޸����ڣ�      2010-02-28
˵    ����      1����־λ��ȫ����Ϊ�еİ������ܻ�û�м��ϣ�
��              2��������һ����־λû�����㣬��ִ�С���������
*******************************************************************************************************/
void key_flag_del(void)
{
  uchar sum=0;
  sum = WorkOn_Transmit_STA + WorkOn_flag + Acquisition_flag + Position_flag + Setting_flag + ZengYi_flag + Rst_flag;
  
  if( sum!=0 )  //  ������һ����־λû�����㣬��ִ�С���������
    HT1621_all_off();	
  
  WorkOn_Transmit_STA     =       0;      //  Ƶ�ʷ��俪ʼ��־
  WorkOn_flag             =       0;      //  ����������������
  Acquisition_flag        =       0;      //�ɼ�
  Position_flag	          =	  0;	  //���� --���
  Setting_flag	          =	  0;	  //���� ���á�
  ZengYi_flag		  =	  0;	  //�����桰
  Rst_flag		  =	  0;      //��λ  
}

/*******************************************************************************************************
�������ƣ�	void key_scan(void)	
�������ܣ�	����ʽ���̰���ɨ��
�޸����ڣ�      2010-02-17
˵    ����      1��ȷ���Ƿ��а������£�
                2���õ������ļ�ֵ��
*******************************************************************************************************/
void key_scan(void)
{
	
	uchar X,Y;
	uchar ZZ; 
	uchar key;
	P2SEL = 0X00;
	P2DIR = 0XFF;     // ���÷������
	P2OUT = 0x8F;	  // P2.6-P2.4��0��������1
	P2DIR = 0XF0;     // ���÷�������
	key   = P2IN;	  // ��ȡP2�ܽ�״̬
	key   = key<<1;		//����һλ��ȥ��P2.7
	
	if(key!=0x1E)	//	0x1E	=	0B00011110	
	{	 	
		//DelayMS(2100);//DelayMS(100);		
		DelayMS(1500);
                key=P2IN;	  // ��ȡP2�ܽ�״̬
		key=key<<1;		//����һλ��ȥ��P2.7
		if(key!=0x1E)//ȷ���а�������
		{
			if( keylong_flag == 0 ) keyon=1; // ȷ���а������µı�־
                        //keyon=1;
		 	X=key;	//�洢���С�
			P2OUT = 0x1F;	  // P2.4��1��������0			
			key	  =	P2IN;	  // ��ȡP2�ܽ�״̬
			key	  =	key<<4;		  //����һλ��ȥ��P2.7,P2.6,P2.5,P2.4;
			if( key==0xF0 )	  // P2.4 ���ڵ���
			{
			   Y=0xC0;
			}
			else
			{			   
			   P2OUT = 0x2F;	  // P2.5��1��������0			   
			   key	 = P2IN;	  // ��ȡP2�ܽ�״̬
			   key   = key<<4;		  //����һλ��ȥ��P2.7,P2.6,P2.5,P2.4;
			   if( key==0xF0 )	  // P2.5 ���ڵ���
			   {
			      Y=0xA0;
			   }
			   else//ֱ��ʹ��P2.6���ڵ���
			   {			      
			   	  P2OUT = 0x4F;	  // P2.6��1��������0				  
			   	  key	= P2IN;	  // ��ȡP2�ܽ�״̬
			   	  key   = key<<4;		  //����һλ��ȥ��P2.7,P2.6,P2.5,P2.4;
				  if( key==0xF0 )	  // P2.5 ���ڵ���
				     Y=0x60;
			   }
			}			
			ZZ=X|Y;           //ȡ����ֵ		
			
			//switch ( ZZ )     //�жϼ�ֵ����һ�������£�
			{
			 	
                                if( ZZ==0x7C )  {//line:1, column:1
							   keyboard_value	=	0X7C; 							 
							}					
				 if( ZZ==0x7A )	{//line:1, column:2					 				   
								keyboard_value	=	0X7A; 
							}
				if( ZZ==0x76 )	{//line:1, column:3
					 			keyboard_value	=	0X76; 
							}
				if( ZZ==0x6E )	{//line:1, column:4
					 			keyboard_value	=	0X6E; 
							}
				if( ZZ==0xBC )	{//line:2, column:1
					 			keyboard_value	=	0XBC; 
							}
				if( ZZ==0xBA )	{//line:2, column:2
					 			keyboard_value	=	0XBA; 
							}
				if( ZZ==0xB6 )	{//line:2, column:3
					 			keyboard_value	=	0XB6; 
							}
				if( ZZ==0xAE )	{//line:2, column:4
					 			keyboard_value	=	0XAE; 
							}
				if( ZZ==0xDC )	{//line:3, column:1
					 			keyboard_value	=	0XDC; 
							}							
				if( ZZ==0xDA )	{//line:3, column:2
					 			keyboard_value	=	0XDA; 
							}
				if( ZZ==0xD6 )	{//line:3, column:3
					 			keyboard_value	=	0XD6; 
							}
				if( ZZ==0xCE )	{//line:3, column:4
					 			keyboard_value	=	0XCE; 
							}		
				
			}
			
                        key_time_calculate(); 	// ����ʱ�����
		}
		
	}
	
	else //���κΰ���
	{
	    keyon = 0; // ȷ�� û�� �������µı�־
            keytime_start = 0;//�رռ�ʱ
            
	}								
	
}

void key_use(void)
{
  key_scan();
  key_use1();
}

/*******************************************************************************************************
�������ƣ�	void key_use(void)	
�������ܣ�	ȡ�ü�ֵ��ִ����ع���
˵����		1��ÿ����һ��case,���Ƚ�keyboard_value��ֵΪ0��
			2��ÿ����һ��case,������ǡ����桰�����üӡ������ü���������������ôZengYi_flag	=	0;
*******************************************************************************************************/
void key_use1(void)
{
    uchar j=0;
    //key_scan();
    if( keyon==0 )//�������º󡣡���
    {
	switch(keyboard_value)
	{
	    
	 	case 0X7C:	{  //L1,C1---��λ
		                              keyboard_value=0;		   	   
						   Rst_flag		=	1;	
						   Started();
						   Rst_flag		=	0;	
						   ZengYi_flag	=	0;
						   Setting_flag	=   0;
						   Position_flag=0;
                                                   Acquisition_flag=0;//�رա��ɼ���
                                                   WorkOn_flag=0;//�رա���������	
                                                   FatBuffer.RecordNumber = 0;//�ر�"��ѯ"
                                                   AutoZengYiRun.ZengYi_Ever_Used = 0;//��⡰���桱���Ƿ��£�����λ�󣬴�ֵ�����0
                                                   keyboard_RST();
					   
					}break;
					//goto AA2;
					
		case 0X7A:	{  //L1,C2-----��ѯ
			 		   Setting_flag	=   0;
					   ZengYi_flag	=	0;
					   keyboard_value=0;
					   Position_flag=0;
                                           Acquisition_flag=0;//�رղɼ�
                                           WorkOn_flag=0;//�رա���������
                                           
                                           FatBuffer.RecordNumber = 1;
                                           FatBuffer.NoRecord_flag_InFile = 0;
                                           
                                           keyboard_RST();
		            }break;
		case 0X76:	{  //L1,C3------���� ��
			 		   keyboard_value	=	0;
			 		   Acquisition_flag=0;//�رղɼ�
                                           WorkOn_flag=0;//�رա���������
                                           /*
					   if( keytime_save>keylongtime ) //������	,3s				
					   {
					 	   if( (Setting_flag!=0)||(Position_flag!=0) )
						      Setting_up	=	2;
						   keytime_save=0;
					   }
                                           */
					   //else	// �̰���					   
					   {	
					       				   
					       if( ZengYi_flag==1 )
						   {
					   	      ZengYi_disp++;	
						   	  if( ZengYi_disp>= ZengYi_MAX )
						   	     ZengYi_disp=0;
						   	  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ZengYi_disp/10][0] );
						   	  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ZengYi_disp/10][1] );
						   	  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ZengYi_disp%10][0] );
						   	  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ZengYi_disp%10][1] );
							  Ht1621WrOneData( 1,8+5 );//���ϵ������־
						   }
						   else
						   {
						      //if( (Setting_flag!=0)||(Position_flag!=0)||(BIAOXIAO_flag==2) )
                                                      if( (Setting_flag!=0)||(Position_flag!=0) )
							     Setting_up	=	1;
						   }
                                               if( FatBuffer.RecordNumber > 0)//�ڲ�ѯ״����
                                               {
                                                  FatBuffer.LastRecordNumber = FatBuffer.RecordNumber ;
                                                  FatBuffer.RecordNumber++;//����¼�����ﵽ����ʱ����ĵط�����������
                                               }
					   }
                                           
                                           keyboard_RST();
		            }break;
		case 0X6E:	{ //L1,C4-----����ͣ
		
			 		   Setting_flag	=   0;
					   ZengYi_flag	=	0;
					   keyboard_value=0;
					   Position_flag=0;
                                           //Acquisition_flag=0;//�رղɼ�
                                           
					   /////////////////////////////////////////////////
                                           Acquisition_flag = 0;//��ѹ������ͣ�����رղɼ�
                                           WorkOn_flag      =   0;//
                                           FatBuffer.RecordNumber = 0;//�ر�"��ѯ"
                                           HT1621_all_off();	
					   aStatic_Show();  //��ʾȫ0----
                                           //ShowCurrentPosition( );  //��ѹ������ͣ����������ʾ��ǰ�ĵ�ţ�����ʾȫ0----
                                           //GUOLIU;  //�������������͡�
                                           keyboard_RST();
		            }break;		
		case 0XBC:	{ //L2,C1---�����桰
		               keyboard_value	=	0;
					   ZengYi_flag		=	1;
                                           
					   Setting_flag	=   0;
					   Position_flag=0;
					   Acquisition_flag=0;//�ر� �ɼ�
                                           WorkOn_flag=0;//�رա���������
                                           FatBuffer.RecordNumber = 0;//�ر�"��ѯ"
			 		   //if(keytime_save>600) //������	,3s				
					   {
					 	
					   }
					   //else	// �̰���
					   {
					   	   HT1621_all_off();
   						   Ht1621WrOneData( 0,8 );
   						   Ht1621WrOneData( 9,8 ); 
						   Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  				   
   						   for( j=0;j<7;j++ )
   						   {
   						      Ht1621WrOneData( disp_data_addr[j][0],disp_data[0][0] );
							  Ht1621WrOneData( disp_data_addr[j][1],disp_data[0][1] );
   						   }
						   Ht1621WrOneData( disp_data_addr[2][0],disp_data[ZengYi_disp/10][0] );
						   Ht1621WrOneData( disp_data_addr[2][1],disp_data[ZengYi_disp/10][1] );
						   Ht1621WrOneData( disp_data_addr[3][0],disp_data[ZengYi_disp%10][0] );
						   Ht1621WrOneData( disp_data_addr[3][1],disp_data[ZengYi_disp%10][1] );
						   Ht1621WrOneData( 1,8+5 );//���ϵ������־
   						   Ht1621WrOneData( 12,1 );	//С����
						   
                                                   //GainControl();//���ƽ�
                                                   AutoZengYiRun.ZengYi_Ever_Used = 1;//////��ֵΪ1��������ʹ���Զ�����
					   }
                                           keyboard_RST();
		            }break;	
		case 0XBA:	{ //L2,C2-----�ɼ�
			 		   
					   Setting_flag	=   0;
					   ZengYi_flag	=	0;
					   keyboard_value=0;
					   Position_flag=0;	
                                           ////////////////////////////////////////////////////////////////
                                           HT1621_all_off();	//����
                                           Acquisition_flag = 1;
                                           GAIN_AUTO_MAX(  ); // ���Զ�����ֵ��Ϊ���ֵ( ZengYi_MAX-1 )
                                           WorkOn_flag=0;//�رա���������	
                                           FatBuffer.RecordNumber = 0;//�ر�"��ѯ"
                                           
                                           keyboard_RST();
					   
		            }break;	
		case 0XB6:	{  //L2,C3----���� ��
		
			 		   keyboard_value	=	0;
					   Acquisition_flag=0;//�رղɼ�
                                           WorkOn_flag=0;//�رա���������
                                           
                                           //if( BIAOXIAO_flag==0 )
                                           {
			 		      if(keytime_save>600) //������	,3s				
					      {
					        if( (Setting_flag!=0)||(Position_flag!=0) )
					 	      Setting_down	=	2;
						   keytime_save=0;
					      }
					      else	// �̰���
					      {
					   	   if( ZengYi_flag==1 )
						   {					   	          
                                                          if( ZengYi_disp!=0 )
                                                            ZengYi_disp--;	
                                                          else
                                                            ZengYi_disp=ZengYi_MAX-1;
                                                          
						   	  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ZengYi_disp/10][0] );
						   	  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ZengYi_disp/10][1] );
						   	  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ZengYi_disp%10][0] );
						   	  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ZengYi_disp%10][1] );
							  Ht1621WrOneData( 1,8+5 );//���ϵ������־
						   }
						   else
						   {
						      //if( (Setting_flag!=0)||(Position_flag!=0)||(BIAOXIAO_flag==2)||(BIAOXIAO_flag==1) )
                                                      if( (Setting_flag!=0)||(Position_flag!=0) )
						         Setting_down	=	1;
						   }
                                                   if( FatBuffer.RecordNumber > 0)//�ڲ�ѯ״����
                                                   {
                                                      FatBuffer.LastRecordNumber = FatBuffer.RecordNumber ;
                                                      FatBuffer.RecordNumber --;
                                                      if( FatBuffer.RecordNumber==0 )
                                                      {
                                                        FatBuffer.RecordNumber = 1;//��ʱ��Ϊ1����ӦΪ��ǰ���������¼
                                                      }
                                                   }
						   
					      }
                                           }
                                           
                                           keyboard_RST();
		            }break;		
		case 0XAE:	{  //L2,C4------ɾ��
			 		   
					   Setting_flag	=   0;
					   ZengYi_flag	=	0;
					   keyboard_value=0;
					   Position_flag=0;
					   Acquisition_flag=0;//�رղɼ�
                                           WorkOn_flag=0;//�رա���������
                                           //FatBuffer.RecordNumber = 0;//�ر�"��ѯ"--ɾ���ǲ�ѯ���������ܣ��������������������ѯ���ı�ʶ
                                           /*
					   if(keytime_save>600) //������	,3s				
					   {					 	
					   }
					   else	// �̰���
					   {     
					   }
                                           */
                                           Delete_flag = 1; //��ʼɾ��
                                           keyboard_RST();
		            }break;		
		case 0XDC:	{  //L3,C1-----����
			 		   keyboard_value	=	0;
					   ZengYi_flag		=	0;
					   Position_flag=0;
					   Acquisition_flag=0;//�رղɼ�
                                           WorkOn_flag=0;//�رա���������
                                           FatBuffer.RecordNumber = 0;//�ر�"��ѯ"
                                           
					   Setting_flag++;
					   if( Setting_flag>6 ) Setting_flag=1;//����һ��ѭ��ģʽ
					   
					   HT1621_all_off();	
                                           
                                           keyboard_RST();
					   
		            }break;
					//goto AA2;
		case 0XDA:	{  //L3,C2----������
			 		   
					   Setting_flag	=   0;
					   ZengYi_flag	=	0;
					   keyboard_value=0;
					   Position_flag=0;
                                           Acquisition_flag=0;//�رղɼ�
                                           FatBuffer.RecordNumber = 0;//�ر�"��ѯ"
					   /////////////////////////////////////////////////////////////
                                           FeatureSelectionPortReset();//�Ƚ���������Ÿ�λ
                                           SetTimeB0( FrequencyPointSelection_data );//���ö�ʱ���ж�ʱ��,
                                           WorkOn_flag    =   1;
                                           GAIN_AUTO_MAX(  ); //���Զ�����ֵ��Ϊ���ֵ( ZengYi_MAX-1 )
                                           WorkOn_Transmit_STA = 1;//��ʼ����Ƶ��
                                           
                                           
                                           HT1621_all_off();
                                           
                                           keyboard_RST();
		            }break;		
		case 0XD6:	{  //L3,C3----���
			 		   
					   //Setting_flag	=   0;
					   ZengYi_flag	=	0;
					   keyboard_value=0;
					   Acquisition_flag=0;//�رղɼ�
                                           WorkOn_flag=0;//�رա���������
                                           FatBuffer.RecordNumber = 0;//�ر�"��ѯ"
                                           
					   //Position_flag	=	1;//���
                                           
                                           if( keytime_save > keylongtime ) //������	,3s				
					   {	
                                             Setting_flag	=   0;
                                             
					   }
					   else	// �̰���
                                             if( Setting_flag != 0 )
					     {   
                                                Setting_up	=	2;
					     }
                                           
                                           keyboard_RST();
		            }break;		
		case 0XCE:	{  //L3,C4-----�洢
			 		   Position_flag=0;					   
					   Setting_flag	=   0;
					   ZengYi_flag	=	0;
					   keyboard_value=0;
                                           FatBuffer.RecordNumber = 0;//�ر�"��ѯ"
                                           /*
                                           if( (Acquisition_flag==0)&&(WorkOn_flag==0) )
                                           {
					      Acquisition_flag=0;//�رղɼ�
                                              WorkOn_flag=0;//�رա���������
                                           }
                                           */
					   /////////////////////////////////////////////////////
                                           if( (Acquisition_flag!=0)||(WorkOn_flag!=0) )
                                              Save_Flag       =   1;  //���д洢----�κΰ��������Զԡ��洢�����㣡����
                                           //////////////////////////////////////////////////
                                           keyboard_RST();
		            }break;																						
		default:	{
					   //keyboard_value=0;
                                            keyboard_RST();
					}break;
					
	}
    }
}

/*******************************************************************************************************
�������ƣ�	void key_time_calculate(void)	
�������ܣ�	����ʱ�����
˵����		1��ǰ�����Ѿ��а������£�
                2��ǰ������ļ�ֵ��һ������Ҫ���¼�ʱ��
*******************************************************************************************************/
void  key_time_calculate(void)
{
 	if(Z==key_save)
	{
	 	 keytime_start	=	1;//��ʼ��ʱ
	}
	else
	{
	  	 key_save = Z;
		 keytime_start	=	0;
		 keytime		=	0;
		 keytime_save	=	0;
	}
}

/**************************************************************************************
�������ƣ�void FeatureSelectionPortReset(void)
�������ܣ�2��Ƶ������Ÿ�λ������һ��һ��
����ʱ�䣺2010-04-28
˵    ����1���ú������ڼ���ͷ�ļ��У������ڡ���������
          2��
**************************************************************************************/
void FeatureSelectionPortReset(void)
{
  P15_H;
  //P16_L;
}

/**************************************************************************************
�������ƣ�void FeatureSelectionPortSTOP(void)
�������ܣ�2��Ƶ����������ͣ����ڲ�����Ƶ��ʱ
����ʱ�䣺2010-04-28
˵    ����1��������������
          2��
**************************************************************************************/
void FeatureSelectionPortSTOP(void)
{
  if( WorkOn_flag!=1 )//û�а��°�������������
  {
    P15_L;
    //P16_L;
  }
}


/**************************************************************************************
�������ƣ�void SaveUseWorkStop(void)
�������ܣ��洢��ɺ�ִ�С�����ͣ���Ĺ��ܡ�
����ʱ�䣺2010-04-28
�޸�ʱ�䣺2010-09-06
˵    ����1������������ʹ�ã�
          2����ѹ���洢����������ʾ��һ����ţ�����ʾȫ0----
          3��
**************************************************************************************/
void SaveUseWorkStop(void)
{
  if( Save_WorkStop_flag==1 )
  {
    Save_WorkStop_flag = 0; //���־
    Acquisition_flag = 0;//��ѹ������ͣ�����رղɼ�
    WorkOn_flag      =   0;//
    FatBuffer.RecordNumber = 0;//�ر�"��ѯ"
    HT1621_all_off();
    //aStatic_Show();       ///��ѹ���洢����������ʾ��һ����ţ�����ʾȫ0----
    ShowNextPosition( );  //������ʾ��һ�����
    //GUOLIU;               //�����������ͣ�ʹ��Դģ���޸�ѹ��������޷���Ƶ�����
  }
}