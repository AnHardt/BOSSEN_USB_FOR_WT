
/*
struct BufferFlag
{
  unsigned int RecordNumber;//"��ѯ"��Ļ�����Զ�Ӧ�ĵڼ�����¼
  unsigned int OffsetInSectorOfTheFile;
};
struct BufferFlag FatBuffer;
*/
//////////////////////////////////// �������� /////////////////////////////////////
uchar BackOrFore_Demand(void);
void NOTOpenFile(void);//���ļ�ʧ��
void Position_Demand(void);//���---��ѯʱ����ʾ
void Vol_Demand(void);//��ѹ---��ѯʱ����ʾ
void Current_Demand(void);////����---��ѯʱ��ʹ��

void DemandControl(void);
////////////////////////////////////// END ////////////////////////////////////////


void ReadTheRecord(void)
{
    int i;
    uchar str[DemandLength];
    UINT16     RealCount;
    UINT32 RecordAddr;
    
    
    
    RecordAddr = CH376GetFileSize() - FatBuffer.RecordNumber * (SaveLength-1);
        //Locate tail
    CH376ByteLocate(RecordAddr);
    
    CH376ByteRead( str, DemandLength, &RealCount );
    HeadingWrite();
    if( (str[DemandLength-3] == Heading[HeadingLength - 3])&&
        (str[DemandLength-5] == Heading[HeadingLength - 5])&&
        (str[DemandLength-7] == Heading[HeadingLength - 7]))
    {
        FatBuffer.RecordNumber = 1;
        FatBuffer.LastRecordNumber = 1;
        RecordAddr = CH376GetFileSize() - (SaveLength-1);
        CH376ByteLocate(RecordAddr);
        CH376ByteRead( str, DemandLength, &RealCount );
    }
    
    for( i = 0;i < DemandLength;i ++){
        FatBuffer.Demand [i] = str[i];
    }

}
void Position_Demand(void)//���---��ѯʱ����ʾ
{
  Ht1621WrOneData( 10,0 );	//�������ɼ���ͼ��--�ر�
  Ht1621WrOneData( 13,0 );//��λ��mV---�ص� 
  
  ///////////������ʾ--�����---���Ǳ��β�ѯ�Ķ�ֵ
  Ht1621WrOneData( disp_data_addr[0][0],disp_data[ Position_data[0] ][0] );
  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ Position_data[0] ][1] );//
  
  /////////////���
  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ FatBuffer.Demand[0]-Parameter ][0] );
  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ FatBuffer.Demand[0]-Parameter ][1] );//
  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ FatBuffer.Demand[1]-Parameter ][0] );
  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ FatBuffer.Demand[1]-Parameter ][1] );//
  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ FatBuffer.Demand[2]-Parameter ][0] + 8 ); // ��������š�
  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ FatBuffer.Demand[2]-Parameter ][1] );//
    
  //////////////////׮��
    Ht1621WrOneData( disp_data_addr[4][0],disp_data[ FatBuffer.Demand[4]-Parameter ][0] );
    Ht1621WrOneData( disp_data_addr[4][1],disp_data[ FatBuffer.Demand[4]-Parameter ][1] );//
    if( Delete_flag==2 )
    {
      Ht1621WrOneData( disp_data_addr[5][0],disp_data[ FatBuffer.Demand[5]-Parameter ][0] +8);
      Ht1621WrOneData( disp_data_addr[5][1],disp_data[ FatBuffer.Demand[5]-Parameter ][1] );//
    }
    else
    {
      Ht1621WrOneData( disp_data_addr[5][0],disp_data[ FatBuffer.Demand[5]-Parameter ][0] );
      Ht1621WrOneData( disp_data_addr[5][1],disp_data[ FatBuffer.Demand[5]-Parameter ][1] );
    }
    Ht1621WrOneData( disp_data_addr[6][0],disp_data[ FatBuffer.Demand[6]-Parameter ][0] +8);////��������ʾ��
    Ht1621WrOneData( disp_data_addr[6][1],disp_data[ FatBuffer.Demand[6]-Parameter ][1] );//
    
    Ht1621WrOneData( 12,1+0 );	//С����+  ma
}
void Vol_Demand(void)//��ѹ---��ѯʱ����ʾ
{
  Ht1621WrOneData( 10,0 );	//�������ɼ���ͼ��--�ر�
  Ht1621WrOneData( 13,1 );//��λ��mV
  
  Ht1621WrOneData( disp_data_addr[0][0],disp_data[ FatBuffer.Demand[8]-Parameter ][0] );
  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ FatBuffer.Demand[8]-Parameter ][1] );//
  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ FatBuffer.Demand[9]-Parameter ][0] );
  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ FatBuffer.Demand[9]-Parameter ][1] );//
  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ FatBuffer.Demand[10]-Parameter ][0] );
  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ FatBuffer.Demand[10]-Parameter ][1] );//
  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ FatBuffer.Demand[11]-Parameter ][0] );
  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ FatBuffer.Demand[11]-Parameter ][1] );//
  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ FatBuffer.Demand[12]-Parameter ][0] );
  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ FatBuffer.Demand[12]-Parameter ][1] );//
  if( Delete_flag==2 )
  {
      Ht1621WrOneData( disp_data_addr[5][0],disp_data[ FatBuffer.Demand[13]-Parameter ][0] +8);
      Ht1621WrOneData( disp_data_addr[5][1],disp_data[ FatBuffer.Demand[13]-Parameter ][1] );//
  }
  else
  {
      Ht1621WrOneData( disp_data_addr[5][0],disp_data[ FatBuffer.Demand[13]-Parameter ][0] );
      Ht1621WrOneData( disp_data_addr[5][1],disp_data[ FatBuffer.Demand[13]-Parameter ][1] );//
  }
  Ht1621WrOneData( disp_data_addr[6][0],disp_data[ FatBuffer.Demand[14]-Parameter ][0] +8);////��������ʾ��
  Ht1621WrOneData( disp_data_addr[6][1],disp_data[ FatBuffer.Demand[14]-Parameter ][1] );//
    
  Ht1621WrOneData( 12,1+0 );	//С����+  ma
}
void Current_Demand(void)////����---��ѯʱ��ʹ��
{
  Ht1621WrOneData( 10,0 );	//�������ɼ���ͼ��--�ر�
  Ht1621WrOneData( 13,0 );//��λ��mV--�ر�
  Ht1621WrOneData( disp_data_addr[0][0],disp_data[ FatBuffer.Demand[16]-Parameter ][0] );
  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ FatBuffer.Demand[16]-Parameter ][1] );//
  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ FatBuffer.Demand[17]-Parameter ][0] );
  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ FatBuffer.Demand[17]-Parameter ][1] );//
  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ FatBuffer.Demand[18]-Parameter ][0] );
  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ FatBuffer.Demand[18]-Parameter ][1] );//
  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ FatBuffer.Demand[19]-Parameter ][0] );
  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ FatBuffer.Demand[19]-Parameter ][1] );//
  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ FatBuffer.Demand[20]-Parameter ][0] );
  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ FatBuffer.Demand[20]-Parameter ][1] );//
  if( Delete_flag==2 )
  {
    Ht1621WrOneData( disp_data_addr[5][0],disp_data[ FatBuffer.Demand[21]-Parameter ][0] +8);///������ɾ����
    Ht1621WrOneData( disp_data_addr[5][1],disp_data[ FatBuffer.Demand[21]-Parameter ][1] );//
  }
  else
  {
    Ht1621WrOneData( disp_data_addr[5][0],disp_data[ FatBuffer.Demand[21]-Parameter ][0] );
    Ht1621WrOneData( disp_data_addr[5][1],disp_data[ FatBuffer.Demand[21]-Parameter ][1] );//
  }
  Ht1621WrOneData( disp_data_addr[6][0],disp_data[ FatBuffer.Demand[22]-Parameter ][0] +8);////��������ʾ��
  Ht1621WrOneData( disp_data_addr[6][1],disp_data[ FatBuffer.Demand[22]-Parameter ][1] );//
    
  Ht1621WrOneData( 12,1+2 );	//С����+  ma
}
#if 1
/*********************************************************************************
�������ƣ�void DemandControl(void)
�������ܣ���������ѯ������
����ʱ�䣺2010-05-17
˵    ����
*********************************************************************************/
void DemandControl(void)
{
    unsigned int i=0;
    uchar del=0;
    
    if( FatBuffer.RecordNumber == 0)//���ڲ�ѯ״����
        return ;
    
    //�ڲ�ѯ״����
    //printk("�ڲ�ѯ״����\r\n");
    WriteANameForANewFile();//���ﲻ�Ǹ����ļ������֣�ֻ�����ô˺��������� FileName ��ֵ
    //USB ����ʧ�ܻ����Ѱγ�����������
    if( (USB_Disk_Connect_Flag == 0) || (CH376DiskConnect() == ERR_DISK_DISCON) ){
        if(MemoryInit() == 0){
            return ;
        }
    }

    if( ( CH376FileOpenPath( FileName )!= USB_INT_SUCCESS )||( CH376GetFileSize() <= strlen(Heading) ) ){
        //���ļ�ʧ�ܣ������ļ������м�¼��ɾ��
        NOTOpenFile();
        CH376FileClose( TRUE );
        return ;
    }
    
    //���ļ��ɹ��������ļ������м�¼û�ж�ɾ��       
    if( Delete_flag==0 )//���û�а���ɾ����
    {
        //for(i=0;( i<((unsigned long)(FileInfo.FileSize)/(unsigned long)(DemandLength)) )&&(del==0);i++)
        //{   //�и�����ѭ���Ļ��ᣬ��Ϊ�п��ܶ���ɾ���ļ�¼
            for( i=0,
                 FatBuffer.Demand[0]=Space,
                 FatBuffer.Demand[1]=Space,
                 FatBuffer.Demand[2]=Space;
                     (FatBuffer.Demand[0]==Space)&&
                     (FatBuffer.Demand[1]==Space)&&
                     (FatBuffer.Demand[2]==Space)&&
                     ( i<(CH376GetFileSize()/(unsigned long)(DemandLength)) )&&
                     (del==0);
                         i++ )
            {//�������ѭ������Ϊ����Ƿ������ɾ���ļ�¼
                ReadTheRecord( );
                if( (FatBuffer.Demand[0]==Space)&&
                    (FatBuffer.Demand[1]==Space)&&
                    (FatBuffer.Demand[2]==Space) ){//������ɾ���ļ�¼
                   if( BackOrFore_Demand()==2 ){//��ѹ�� --���ü�
                        FatBuffer.LastRecordNumber = FatBuffer.RecordNumber ;
                        FatBuffer.RecordNumber --;
                        if( FatBuffer.RecordNumber==0 )
                           FatBuffer.RecordNumber = 1;//��ʱ��Ϊ1����ӦΪ��ǰ���������¼                        
                   }else{//��ѹ�� ���ü� �������Ǹհ�ѹ�� ��ѯ
                        FatBuffer.LastRecordNumber = FatBuffer.RecordNumber ;
                        FatBuffer.RecordNumber ++;
                   }
                }else{////������ȡ�ɹ���û�ж��� ɾ���ļ�¼
                  del=1;//��������ѭ����������ʾ��������
                }
            }// end for
        //}        
    }   
    if( i<(CH376GetFileSize()/(unsigned long)(DemandLength)) )  //�������������б��¼�Ƿ�ȫ��ɾ��
    {   
      Ht1621WrOneData( 0,8 );//������˾�ı�ʶ  
      Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ  
      Ht1621WrOneData( 11,4 );		//������˾�ı�ʶ  
      if( WorkOnTime<=Basic_Time )   Position_Demand();//��ʾ���                   
      if( (WorkOnTime>Basic_Time)&&(WorkOnTime<=Basic_Time*2) )  Current_Demand();//��ʾ����                  
      if( (WorkOnTime>Basic_Time*2)&&(WorkOnTime<=Basic_Time*3) )  Vol_Demand();//��ʾ��ѹ��24λAD   
    }
    else  //��Ч��¼ȫ��ɾ��
    {
      FatBuffer.NoRecord_flag_InFile=1;//NOTOpenFile();
    }
    CH376FileClose( TRUE );
}
#endif
void NOTOpenFile(void)//���ļ�ʧ��
{
  //��Ļ�ϡ���ʾ��ͼ���������߸����ִ��ھ�̬�� 0
  Ht1621WrOneData( 0,8 );//������˾�ı�ʶ  
  Ht1621WrOneData( 9,8 ); //������˾�ı�ʶ  
  Ht1621WrOneData( 11,4 );//������˾�ı�ʶ  
  Ht1621WrOneData( disp_data_addr[0][0],disp_data[ 0 ][0] );//
  Ht1621WrOneData( disp_data_addr[0][1],disp_data[ 0 ][1] );//
  Ht1621WrOneData( disp_data_addr[1][0],disp_data[ 0 ][0] );//
  Ht1621WrOneData( disp_data_addr[1][1],disp_data[ 0 ][1] );//
  Ht1621WrOneData( disp_data_addr[2][0],disp_data[ 0 ][0] );//
  Ht1621WrOneData( disp_data_addr[2][1],disp_data[ 0 ][1] );//
  Ht1621WrOneData( disp_data_addr[3][0],disp_data[ 0 ][0] );//
  Ht1621WrOneData( disp_data_addr[3][1],disp_data[ 0 ][1] );//
  Ht1621WrOneData( disp_data_addr[4][0],disp_data[ 0 ][0] );//
  Ht1621WrOneData( disp_data_addr[4][1],disp_data[ 0 ][1] );//
  Ht1621WrOneData( disp_data_addr[5][0],disp_data[ 0 ][0] );//
  Ht1621WrOneData( disp_data_addr[5][1],disp_data[ 0 ][1] );//
  if( second%2==0 )
  {
      Ht1621WrOneData( disp_data_addr[6][0],disp_data[ 0 ][0] +8);////��������ʾ��
      Ht1621WrOneData( disp_data_addr[6][1],disp_data[ 0 ][1] );//
  }
  else
  {
    Ht1621WrOneData( disp_data_addr[6][0],disp_data[ 0 ][0] );////����ʾ��---�ر�
    Ht1621WrOneData( disp_data_addr[6][1],disp_data[ 0 ][1] );//
  }
}

/*-------------------------------------------------------------------------------
�������ƣ�
�������ܣ������һ�ΰ�ѹ�����üӡ����ߡ����ü������ж��жϲ���Ա�Ĳ�ѯ���ƣ�����ǰ�������
˵    ����1�� ���ز��� �� 1--���һ�ΰ�ѹ�ˡ����üӡ�
                      2--���һ�ΰ�ѹ�ˡ����ü���
                      0--�ļ���ֻ��һ����¼��
          2������ǵ�һ�ΰ�ѹ��ѯ����������û�а�ѹ�����üӡ����ߡ����ü�����Ҳ�ᱻ��Ϊ��0
-------------------------------------------------------------------------------*/
uchar BackOrFore_Demand(void)
{
  uchar flag=0;
  if( FatBuffer.LastRecordNumber > FatBuffer.RecordNumber )
  {
      if( FatBuffer.LastRecordNumber-FatBuffer.RecordNumber==1 )
        flag=2;
      else
        flag=1;
  }
  if( FatBuffer.LastRecordNumber < FatBuffer.RecordNumber )
  {
      if( FatBuffer.RecordNumber-FatBuffer.LastRecordNumber == 1 )
        flag=1;
      else
        flag=2;
  }
  if( FatBuffer.LastRecordNumber == FatBuffer.RecordNumber )
  {
      flag=0;
  }
  return flag;
}