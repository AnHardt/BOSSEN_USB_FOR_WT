

void Vol_Disp(signed long vol);




/*******************************************************************************
�������ƣ�void Vol_Disp(signed long vol)
�������ܣ�������õ��ĵ�ѹֵ����Ļ����ʾ�����ȣ�1uV
˵    ����
��    �ߣ���Ĵ�˵
����ʱ�䣺2010-02-25
�޸�ʱ�䣺2010-04-30
*******************************************************************************/
//uchar  mmmm[8];
/*
void Vol_Disp(signed long vol)
{
  uchar  *p;
  uchar i=0;
  
  if( (Acquisition_flag==1)||(WorkOn_flag==1) )
  {
    if( Vol_Calculate_One_Time == 1 )
    {
      p=Decomposition8(vol); 
      Vol_Calculate_One_Time =0;
      for( i=0;i<8;i++ )
      {
        mmmm[i]= *(p+i) ;
      }
    }
  }
  else
  {
    p=Decomposition8(vol); 
    for( i=0;i<8;i++ )
    {
      mmmm[i]= *(p+i) ;
    }
  }
  
  if( Save_Flag==0 )//û�а�ѹ���洢�������ߴ洢û�н���
  {
    if( vol<FullData )
    {
      Ht1621WrOneData( disp_data_addr[0][0],disp_data[ mmmm[6] ][0] );
      Ht1621WrOneData( disp_data_addr[0][1],disp_data[ mmmm[6] ][1] );//
      Ht1621WrOneData( disp_data_addr[1][0],disp_data[ mmmm[5] ][0] );
      Ht1621WrOneData( disp_data_addr[1][1],disp_data[ mmmm[5] ][1] );//
      Ht1621WrOneData( disp_data_addr[2][0],disp_data[ mmmm[4] ][0] );
      Ht1621WrOneData( disp_data_addr[2][1],disp_data[ mmmm[4] ][1] );//
      Ht1621WrOneData( disp_data_addr[3][0],disp_data[ mmmm[3] ][0] );
      Ht1621WrOneData( disp_data_addr[3][1],disp_data[ mmmm[3] ][1] );//
      Ht1621WrOneData( disp_data_addr[4][0],disp_data[ mmmm[2] ][0] );
      Ht1621WrOneData( disp_data_addr[4][1],disp_data[ mmmm[2] ][1] );//
      Ht1621WrOneData( disp_data_addr[5][0],disp_data[ mmmm[1] ][0] );
      Ht1621WrOneData( disp_data_addr[5][1],disp_data[ mmmm[1] ][1] );//
      Ht1621WrOneData( disp_data_addr[6][0],disp_data[ mmmm[0] ][0] );
      Ht1621WrOneData( disp_data_addr[6][1],disp_data[ mmmm[0] ][1] );//
      Ht1621WrOneData( 13,1 );//��λ��mV
      Ht1621WrOneData( 12,1 );	//С����
    }
    else  //  �����̣���ʾ��FULL��
    {
      Ht1621WrOneData( disp_data_addr[0][0],7 );
      Ht1621WrOneData( disp_data_addr[0][1],8 );//
      Ht1621WrOneData( disp_data_addr[1][0],5 );
      Ht1621WrOneData( disp_data_addr[1][1],7 );//
      Ht1621WrOneData( disp_data_addr[2][0],5 );
      Ht1621WrOneData( disp_data_addr[2][1],1 );//
      Ht1621WrOneData( disp_data_addr[3][0],5 );
      Ht1621WrOneData( disp_data_addr[3][1],1 );//
      Ht1621WrOneData( disp_data_addr[4][0],0 );
      Ht1621WrOneData( disp_data_addr[4][1],0 );//
      Ht1621WrOneData( disp_data_addr[5][0],0 );
      Ht1621WrOneData( disp_data_addr[5][1],0 );//
      Ht1621WrOneData( disp_data_addr[6][0],0 );
      Ht1621WrOneData( disp_data_addr[6][1],0 );//
      Ht1621WrOneData( 13,1 );//��λ��mV
      Ht1621WrOneData( 12,0 );	//С����+ma ���ε�
    }
  }
  else
  {
    if( vol<FullData )
    {
      Ht1621WrOneData( disp_data_addr[0][0],disp_data[ mmmm[6] ][0] );
      Ht1621WrOneData( disp_data_addr[0][1],disp_data[ mmmm[6] ][1] );//
      Ht1621WrOneData( disp_data_addr[1][0],disp_data[ mmmm[5] ][0] );
      Ht1621WrOneData( disp_data_addr[1][1],disp_data[ mmmm[5] ][1] );//
      Ht1621WrOneData( disp_data_addr[2][0],disp_data[ mmmm[4] ][0] );
      Ht1621WrOneData( disp_data_addr[2][1],disp_data[ mmmm[4] ][1] );//
      Ht1621WrOneData( disp_data_addr[3][0],disp_data[ mmmm[3] ][0] );
      Ht1621WrOneData( disp_data_addr[3][1],disp_data[ mmmm[3] ][1] );//
      Ht1621WrOneData( disp_data_addr[4][0],disp_data[ mmmm[2] ][0]+8 );//// + ����
      Ht1621WrOneData( disp_data_addr[4][1],disp_data[ mmmm[2] ][1] );//
      Ht1621WrOneData( disp_data_addr[5][0],disp_data[ mmmm[1] ][0] );
      Ht1621WrOneData( disp_data_addr[5][1],disp_data[ mmmm[1] ][1] );//
      Ht1621WrOneData( disp_data_addr[6][0],disp_data[ mmmm[0] ][0] );
      Ht1621WrOneData( disp_data_addr[6][1],disp_data[ mmmm[0] ][1] );//
      Ht1621WrOneData( 13,1 );//��λ��mV
      Ht1621WrOneData( 12,1 );	//С����
    }
    else  //  �����̣���ʾ��FULL��
    {
      Ht1621WrOneData( disp_data_addr[0][0],7 );
      Ht1621WrOneData( disp_data_addr[0][1],8 );//
      Ht1621WrOneData( disp_data_addr[1][0],5 );
      Ht1621WrOneData( disp_data_addr[1][1],7 );//
      Ht1621WrOneData( disp_data_addr[2][0],5 );
      Ht1621WrOneData( disp_data_addr[2][1],1 );//
      Ht1621WrOneData( disp_data_addr[3][0],5 );
      Ht1621WrOneData( disp_data_addr[3][1],1 );//
      Ht1621WrOneData( disp_data_addr[4][0],0  +8 );//// + ����
      Ht1621WrOneData( disp_data_addr[4][1],0 );//
      Ht1621WrOneData( disp_data_addr[5][0],0 );
      Ht1621WrOneData( disp_data_addr[5][1],0 );//
      Ht1621WrOneData( disp_data_addr[6][0],0 );
      Ht1621WrOneData( disp_data_addr[6][1],0 );//
      Ht1621WrOneData( 13,1 );//��λ��mV
      Ht1621WrOneData( 12,0 );	//С����+ma ���ε�
    }
  }
}
*/

void Vol_Disp(signed long vol)
{
  uchar  *p;
  uchar i=0;
  
  
  
  if( (Acquisition_flag==1)||(WorkOn_flag==1) )
  {
    if( Vol_Calculate_One_Time == 1 )
    {
      //AutoZengyi();/////////////////////////////////////////////////////�����Զ�������
      ZengYiTEST();//////
      p=Decomposition8(vol); 
      Vol_Calculate_One_Time =0;
      for( i=0;i<8;i++ )
      {
        mmmm[i]= *(p+i) ;
      }
    }
  }
  else
  {
    p=Decomposition8(vol); 
    for( i=0;i<8;i++ )
    {
      mmmm[i]= *(p+i) ;
    }
  }
  //AutoZengyi();/////////////////////////////////////////////////////�����Զ�������
  if( Save_Flag==0 )//û�а�ѹ���洢�������ߴ洢û�н���
  {
      if( AutoZengYiRun.which_grade_yichu == 0 )//���κ����
      {
          Ht1621WrOneData( disp_data_addr[0][0],disp_data[ mmmm[6] ][0] );
          Ht1621WrOneData( disp_data_addr[0][1],disp_data[ mmmm[6] ][1] );//
          Ht1621WrOneData( disp_data_addr[1][0],disp_data[ mmmm[5] ][0] );
          Ht1621WrOneData( disp_data_addr[1][1],disp_data[ mmmm[5] ][1] );//
          Ht1621WrOneData( disp_data_addr[2][0],disp_data[ mmmm[4] ][0] );
          Ht1621WrOneData( disp_data_addr[2][1],disp_data[ mmmm[4] ][1] );//
          Ht1621WrOneData( disp_data_addr[3][0],disp_data[ mmmm[3] ][0] );
          Ht1621WrOneData( disp_data_addr[3][1],disp_data[ mmmm[3] ][1] );//
          Ht1621WrOneData( disp_data_addr[4][0],disp_data[ mmmm[2] ][0] );
          Ht1621WrOneData( disp_data_addr[4][1],disp_data[ mmmm[2] ][1] );//
          Ht1621WrOneData( disp_data_addr[5][0],disp_data[ mmmm[1] ][0] );
          Ht1621WrOneData( disp_data_addr[5][1],disp_data[ mmmm[1] ][1] );//
          Ht1621WrOneData( disp_data_addr[6][0],disp_data[ mmmm[0] ][0] );
          Ht1621WrOneData( disp_data_addr[6][1],disp_data[ mmmm[0] ][1] );//
          Ht1621WrOneData( 13,1 );//��λ��mV
          Ht1621WrOneData( 12,1 );	//С����
      }
      else///FULL
      {
          Ht1621WrOneData( disp_data_addr[0][0],7 );
          Ht1621WrOneData( disp_data_addr[0][1],8 );//
          Ht1621WrOneData( disp_data_addr[1][0],5 );
          Ht1621WrOneData( disp_data_addr[1][1],7 );//
          Ht1621WrOneData( disp_data_addr[2][0],5 );
          Ht1621WrOneData( disp_data_addr[2][1],1 );//
          Ht1621WrOneData( disp_data_addr[3][0],5 );
          Ht1621WrOneData( disp_data_addr[3][1],1 );//
          Ht1621WrOneData( disp_data_addr[4][0],disp_data[ AutoZengYiRun.which_grade_yichu ][0] );
          Ht1621WrOneData( disp_data_addr[4][1],disp_data[ AutoZengYiRun.which_grade_yichu ][1] );//
          Ht1621WrOneData( disp_data_addr[5][0],0 );
          Ht1621WrOneData( disp_data_addr[5][1],0 );//
          Ht1621WrOneData( disp_data_addr[6][0],0 );
          Ht1621WrOneData( disp_data_addr[6][1],0 );//
          Ht1621WrOneData( 13,1 );//��λ��mV
          Ht1621WrOneData( 12,0 );	//С����+ma ���ε�
      }
  }
  else
  {
      if( AutoZengYiRun.which_grade_yichu == 0 )//���κ����
      {
          Ht1621WrOneData( disp_data_addr[0][0],disp_data[ mmmm[6] ][0] );
          Ht1621WrOneData( disp_data_addr[0][1],disp_data[ mmmm[6] ][1] );//
          Ht1621WrOneData( disp_data_addr[1][0],disp_data[ mmmm[5] ][0] );
          Ht1621WrOneData( disp_data_addr[1][1],disp_data[ mmmm[5] ][1] );//
          Ht1621WrOneData( disp_data_addr[2][0],disp_data[ mmmm[4] ][0] );
          Ht1621WrOneData( disp_data_addr[2][1],disp_data[ mmmm[4] ][1] );//
          Ht1621WrOneData( disp_data_addr[3][0],disp_data[ mmmm[3] ][0] );
          Ht1621WrOneData( disp_data_addr[3][1],disp_data[ mmmm[3] ][1] );//
          Ht1621WrOneData( disp_data_addr[4][0],disp_data[ mmmm[2] ][0]+8 );//// + ����
          Ht1621WrOneData( disp_data_addr[4][1],disp_data[ mmmm[2] ][1] );//
          Ht1621WrOneData( disp_data_addr[5][0],disp_data[ mmmm[1] ][0] );
          Ht1621WrOneData( disp_data_addr[5][1],disp_data[ mmmm[1] ][1] );//
          Ht1621WrOneData( disp_data_addr[6][0],disp_data[ mmmm[0] ][0] );
          Ht1621WrOneData( disp_data_addr[6][1],disp_data[ mmmm[0] ][1] );//
          Ht1621WrOneData( 13,1 );//��λ��mV
          Ht1621WrOneData( 12,1 );	//С����
      }
      else
      {
          Ht1621WrOneData( disp_data_addr[0][0],7 );
          Ht1621WrOneData( disp_data_addr[0][1],8 );//
          Ht1621WrOneData( disp_data_addr[1][0],5 );
          Ht1621WrOneData( disp_data_addr[1][1],7 );//
          Ht1621WrOneData( disp_data_addr[2][0],5 );
          Ht1621WrOneData( disp_data_addr[2][1],1 );//
          Ht1621WrOneData( disp_data_addr[3][0],5 );
          Ht1621WrOneData( disp_data_addr[3][1],1 );//
          Ht1621WrOneData( disp_data_addr[4][0],disp_data[ AutoZengYiRun.which_grade_yichu ][0]  +8 );//// + ����
          Ht1621WrOneData( disp_data_addr[4][1],disp_data[ AutoZengYiRun.which_grade_yichu ][1] );//
          Ht1621WrOneData( disp_data_addr[5][0],0 );
          Ht1621WrOneData( disp_data_addr[5][1],0 );//
          Ht1621WrOneData( disp_data_addr[6][0],0 );
          Ht1621WrOneData( disp_data_addr[6][1],0 );//
          Ht1621WrOneData( 13,1 );//��λ��mV
          Ht1621WrOneData( 12,0 );	//С����+ma ���ε�
      }
  }
}
//*/