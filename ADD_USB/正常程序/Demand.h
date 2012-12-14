
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
unsigned int CalculateTheOffsetInSectorOfTheFile( struct FileInfoStruct *pstru,unsigned long Cluster,unsigned char iSectorInCluster  );
unsigned char OpenFile( char *filepath );
void ReadTheRecord(void);
void DemandControl(void);
////////////////////////////////////// END ////////////////////////////////////////

/*********************************************************************************
�������ƣ�void ReadTheRecord(void)
�������ܣ���ȡ SD ���������¼���������Ϊ512���ֽ�
����ʱ�䣺2010-05-02
˵    ����
*********************************************************************************/
void ReadTheRecord(void)
{
  uchar ri=0;
  int RestOfBytes = 0;
  unsigned long BackToFore_Size=0;
  unsigned long iCluster=0;
  int  iSector=0;
  uint  TheLastSectorInFile = 0;  //  �ļ������һ������
  uint  OffsetInSectorOfTheFile = 0;  //  �ļ���ĳ���������ֽ���
  WriteANameForANewFile();//���ﲻ�Ǹ����ļ������֣�ֻ�����ô˺��������� FileName ��ֵ
  
  if( OpenFile(FileName)==1 ) //  ���ļ��ɹ�
  {
    TheLastSectorInFile = FAT32_ReadFileTheLastCluster( &FileInfo );
    FatBuffer.TheLastSectorInFile = TheLastSectorInFile ;
    FatBuffer.TheLastClusterInFile = FileInfo.FileCurCluster;//�ں���FAT32_ReadFileTheLastCluster( &FileInfo );��Ϊ  FileInfo.FileCurCluster��ֵ
    OffsetInSectorOfTheFile = CalculateTheOffsetInSectorOfTheFile( &FileInfo,FileInfo.FileCurCluster,TheLastSectorInFile  );
    FAT32_ReadSector((((FileInfo.FileCurCluster)-2)*(Init_Arg.SectorsPerClust))+Init_Arg.FirstDataSector+TheLastSectorInFile,FAT32_Buffer);//
    
    //FatBuffer.RecordNumber = 3;////////////////��ʱ��
    FatBuffer.RecordNumber_Bytes = FatBuffer.RecordNumber * DemandLength ;
    OffsetInSectorOfTheFile = 0;
    iCluster = FileInfo.FileCurCluster;//�ļ������һ����
    RestOfBytes = FatBuffer.RecordNumber_Bytes - BackToFore_Size;
    for( ;FatBuffer.RecordNumber_Bytes>BackToFore_Size;BackToFore_Size+=OffsetInSectorOfTheFile )//��һ�γ��� <=BackToFore_Size �Ͷ����������ݣ�����ֻ��һ��
    {
        if(ri==0)//��һ�ζ�ȡ���һ������
        { //ֻ�����һ���������ܲ���512���ֽڣ������Ķ���
          OffsetInSectorOfTheFile = CalculateTheOffsetInSectorOfTheFile( &FileInfo,FileInfo.FileCurCluster,TheLastSectorInFile  );
        }
        else
        {
          OffsetInSectorOfTheFile = 512;
        }
        FatBuffer.BytesAfterTheSector = BackToFore_Size;/////ע��
        iSector = TheLastSectorInFile-ri;
        ri++;
        if( iSector<0 )
        {
          iSector = 7;
          TheLastSectorInFile =7;
          ri=1;
          iCluster--;
        }
        if( RestOfBytes>=DemandLength )//����Ƿ���ܷ�������ȡ���ּ�¼��
          RestOfBytes = FatBuffer.RecordNumber_Bytes - BackToFore_Size;
    }//�����������Ƕ�ȡ��¼�������ڵ�����----���ܶ����� ���ֵļ�¼����
    FAT32_ReadSector((((iCluster)-2)*(Init_Arg.SectorsPerClust))+Init_Arg.FirstDataSector + iSector,FAT32_Buffer);//
    /////����ȡ�ļ�¼�����ܶ����� ���ֵļ�¼���ݣ����� Demand[ DemandLength ];
    OffsetInSectorOfTheFile = CalculateTheOffsetInSectorOfTheFile( &FileInfo,iCluster,iSector  );
    ri=0;
    FatBuffer.OffsetInBuffer_RecordNumber = OffsetInSectorOfTheFile-FatBuffer.RecordNumber*DemandLength+ri;
    FatBuffer.OffsetInBuffer_Start_RecordNumber = FatBuffer.OffsetInBuffer_RecordNumber;//��ֵ��ʼ�±�
    for( ri=0;(ri<DemandLength)&&(FatBuffer.OffsetInBuffer_RecordNumber<512);ri++ )
    {
      //if( OffsetInSectorOfTheFile-FatBuffer.RecordNumber*DemandLength+ri<512 )//��ֹ�����±����
        FatBuffer.OffsetInBuffer_RecordNumber = OffsetInSectorOfTheFile-(FatBuffer.RecordNumber*DemandLength -FatBuffer.BytesAfterTheSector)+ri;
        FatBuffer.Demand[ ri ] = FAT32_Buffer[ FatBuffer.OffsetInBuffer_RecordNumber ];
    }
    ///////���ˣ����衰��ѯ������ȫ������������Ҫ���˲������ݵĴغ���������������¼
    FatBuffer.TheFirstPartForDemand_Sector = iSector;
    FatBuffer.TheFirstPartForDemand_Cluster = iCluster;
    FatBuffer.TheSecondPartForDemand_Sector = FatBuffer.TheFirstPartForDemand_Sector;
    FatBuffer.TheSecondPartForDemand_Cluster = FatBuffer.TheFirstPartForDemand_Cluster;
    //////////����ͼ���Ƿ���ڡ������� ���ֵļ�¼���ݡ������⣬������FAT32_Buffer���±�>=512�������
    //if( ri!=DemandLength )//�������
    if( RestOfBytes < DemandLength )
    {
        //�ղŶ����������¶�ȡ
        //FatBuffer.OffsetInBuffer_RecordNumber = 512 - ri ;
        //FatBuffer.OffsetInBuffer_RecordNumber = 512 - (DemandLength-RestOfBytes) ;
        FatBuffer.OffsetInBuffer_RecordNumber = 512 - (RestOfBytes) ;
        FatBuffer.OffsetInBuffer_Start_RecordNumber = FatBuffer.OffsetInBuffer_RecordNumber;//��ֵ��ʼ�±�
        for( ri=0;(FatBuffer.OffsetInBuffer_RecordNumber<512);ri++ )
        { 
            FatBuffer.Demand[ ri ] = FAT32_Buffer[ FatBuffer.OffsetInBuffer_RecordNumber ];
            FatBuffer.OffsetInBuffer_RecordNumber ++;
        }
        ///////������ѯ���������ڵ�ǰ�벿�����ڵĴ�����������
        FatBuffer.TheFirstPartForDemand_Sector = iSector;
        FatBuffer.TheFirstPartForDemand_Cluster = iCluster;
        //û�ж���ļ�¼����һ��������
        iSector ++;
        if( iSector>=8 )
        {
            iSector = 0;
            iCluster ++;
        }
        ///////������ѯ���������ڵ� ��벿�� ���ڵĴ�����������
        FatBuffer.TheSecondPartForDemand_Sector = iSector;
        FatBuffer.TheSecondPartForDemand_Cluster = iCluster;//////������ϣ�����Ͷ�ȡ����ѯ�����ݵ���һ��
        FAT32_ReadSector((((iCluster)-2)*(Init_Arg.SectorsPerClust))+Init_Arg.FirstDataSector + iSector,FAT32_Buffer);//
        ///��ʣ���¼���ݷ������� FatBuffer.Demand ����ʱ��һ���Ǵ����� FAT32_Buffer ����ǰ�濪ʼ��ȡ
        FatBuffer.OffsetInBuffer_RecordNumber = 0;
        for( ;ri<DemandLength;ri++ )
        {
            FatBuffer.Demand[ ri ] = FAT32_Buffer[ FatBuffer.OffsetInBuffer_RecordNumber ];
            FatBuffer.OffsetInBuffer_RecordNumber ++;//����ֵ���ʵ��ֵ�� 1
        }          
    }
    //////����Ƿ��ȡ�˱�����
    if( (FatBuffer.Demand[DemandLength-1]=='\r')&&(FatBuffer.Demand[DemandLength-2]=='Z')&&(FatBuffer.Demand[DemandLength-3]=='H') )
    {//�ο����� Heading ���������ֵ���Ϳ���֪���Ƿ�����ˡ������С�
         //һ������ ������ ���ͱ����Ѿ��������ļ��Ŀ�ͷ������Ҫ�����ļ���β�����¶�ȡ�����غ�һ����������������¼�������ڡ�һ����¼������������������   
            //OffsetInSectorOfTheFile = CalculateTheOffsetInSectorOfTheFile( &FileInfo,iCluster,iSector  );
            TheLastSectorInFile = FAT32_ReadFileTheLastCluster( &FileInfo );
            OffsetInSectorOfTheFile = CalculateTheOffsetInSectorOfTheFile( &FileInfo,FileInfo.FileCurCluster,TheLastSectorInFile  );
            FatBuffer.RecordNumber = 1;//���ص� ��һ�� ��¼
            FatBuffer.RecordNumber_Bytes = FatBuffer.RecordNumber * DemandLength ;
            FatBuffer.OffsetInBuffer_RecordNumber = OffsetInSectorOfTheFile-FatBuffer.RecordNumber*DemandLength;
            FatBuffer.OffsetInBuffer_Start_RecordNumber = FatBuffer.OffsetInBuffer_RecordNumber;//��ֵ��ʼ�±�
            for( ri=0;(ri<DemandLength)&&(FatBuffer.OffsetInBuffer_RecordNumber<512);ri++ )
            {
                
                FatBuffer.OffsetInBuffer_RecordNumber = OffsetInSectorOfTheFile-FatBuffer.RecordNumber*DemandLength + ri;
                FatBuffer.Demand[ ri ] = FAT32_Buffer[ FatBuffer.OffsetInBuffer_RecordNumber ];
            }
    } 
    
    /////////////////////
  }  
  ri = 1;  
}

/*********************************************************************************
�������ƣ�unsigned char OpenFile( char *filepath )
�������ܣ���ĳ���Ѵ����ļ��ļ���
����ʱ�䣺2010-05-02
˵    ����
*********************************************************************************/
unsigned char OpenFile( char *filepath )
{
 unsigned char depth=0;
 unsigned char i,index;
 unsigned long iFileSec,iCurFileSec,iFile;
 unsigned long sum3=0;
 struct direntry *pFile;
 unsigned char len=strlen(filepath);
 for(i=0;i<len;i++)
 {
  if(filepath[i]=='\\')
  { 
   depth++;
   index=i+1;
  }
 } 
 //iCurFileSec=FAT32_EnterDir(filepath)/*Init_Arg.FirstDirSector*/; 
 iCurFileSec=Init_Arg.FirstDirSector; //  ֻ�����ڸ�Ŀ¼�¹���
 for(iFileSec=iCurFileSec;iFileSec<iCurFileSec+(Init_Arg.SectorsPerClust);iFileSec++)
 {
    FAT32_ReadSector(iFileSec,FAT32_Buffer);
    for(iFile=0;iFile<Init_Arg.BytesPerSector;iFile+=sizeof(struct direntry))
    {
      pFile=((struct direntry *)(FAT32_Buffer+iFile));
      if(FAT32_CompareName(filepath+index,pFile->deName))
      {    
        FileInfo.FileSize=lb2bb(pFile->deFileSize,4);
	strcpy(FileInfo.FileName,filepath+index);
	FileInfo.FileStartCluster=lb2bb(pFile->deLowCluster,2)+lb2bb(pFile->deHighClust,2)*65536;
	FileInfo.FileCurCluster=FileInfo.FileStartCluster;
	FileInfo.FileNextCluster=FAT32_GetNextCluster(FileInfo.FileCurCluster);
	FileInfo.FileOffset=0;	
	//return &FileInfo;   
        return 1;
      } 
      else
      {        
        for(i=0;i<32;i++)
          sum3 += FAT32_Buffer[ iFile + i ];
        if( sum3 == 0 )
        {            
	    return 0;
        }
        else
        {
          sum3 = 0;
        }
      }
    }
 }
 return 0;
}


/*********************************************************************************
�������ƣ�unsigned int CalculateTheOffsetInSectorOfTheFile( struct FileInfoStruct *pstru )
�������ܣ������ļ���ռ�õ�ĳ�������ı�ʹ���ֽ���
����ʱ�䣺2010-05-16
˵    �����������壺1��struct FileInfoStruct *pstru �ļ������Ϣ �� 
                    2��unsigned long Cluster �ļ���ռ�õ�ĳһ�� �� 
                    3��unsigned char iSectorInCluster ����2���г��Ĵ����ĳ��������
˼    ·��1�������ļ����ܴ�С������ļ����ܴأ����Ҫ��������Ĵ������һ���أ�
          ��ô���;���������ĸ������ģ��������Ҳ�����һ������������㣬����
          ֱ�ӷ��� 512
*********************************************************************************/
unsigned int CalculateTheOffsetInSectorOfTheFile( struct FileInfoStruct *pstru,unsigned long Cluster,unsigned char iSectorInCluster  )
{
  uint  OffsetInTheSector=0;//�������е��ֽ���
  unsigned long TheLastClusterInFile = 0;//�ļ������һ����
  unsigned long ClustersInFile; //  ������ʼ���⣬�ļ���ռ�е����д�
  unsigned long FileSizeInTheLastCluster=0;//�ļ����һ���أ������е��ֽ���
  uchar TheLastSector = 0;//�ļ������һ������
  ///////////////////////////////////////////////////////////////////////////////////
  ClustersInFile = pstru->FileSize/Init_Arg.SectorsPerClust;
  ClustersInFile = ClustersInFile/Init_Arg.BytesPerSector;
  if( pstru->FileSize - ClustersInFile*(unsigned long)(Init_Arg.SectorsPerClust)*(unsigned long)(Init_Arg.BytesPerSector) == 0 )
  {
    ClustersInFile = ClustersInFile-1;
  }
  TheLastClusterInFile = pstru->FileStartCluster+ClustersInFile;////
  ///////////////////////////////////////////////////////////////////////////////////
  FileSizeInTheLastCluster = pstru->FileSize - ClustersInFile*(unsigned long)(Init_Arg.SectorsPerClust)*(unsigned long)(Init_Arg.BytesPerSector);
  TheLastSector = FileSizeInTheLastCluster/Init_Arg.BytesPerSector;
  if( FileSizeInTheLastCluster%Init_Arg.BytesPerSector==0 )
  {
      TheLastSector = TheLastSector - 1;
  }///////////
  ///////////////////////////////////////////////////////////////////////////////////
  if( Cluster==TheLastClusterInFile )
  {
    if( iSectorInCluster == TheLastSector )
    {
      OffsetInTheSector   = pstru->FileSize - ( TheLastClusterInFile - pstru->FileStartCluster )*Init_Arg.SectorsPerClust*Init_Arg.BytesPerSector;
      OffsetInTheSector   = OffsetInTheSector - iSectorInCluster * Init_Arg.BytesPerSector;
    }
    else
    {
      return 512;
    }
  }
  else
  {
    return 512;
  }
  return  OffsetInTheSector ;
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
  if( FatBuffer.RecordNumber > 0)//�ڲ�ѯ״����
  {
    WriteANameForANewFile();//���ﲻ�Ǹ����ļ������֣�ֻ�����ô˺��������� FileName ��ֵ
    if( ( OpenFile(FileName)==1 )&&( FatBuffer.NoRecord_flag_InFile==0 ) ) //  ���ļ��ɹ��������ļ������м�¼û�ж�ɾ��
    {        
      if( Delete_flag==0 )//���û�а���ɾ����
      {
        //for(i=0;( i<((unsigned long)(FileInfo.FileSize)/(unsigned long)(DemandLength)) )&&(del==0);i++)
        {   //�и�����ѭ���Ļ��ᣬ��Ϊ�п��ܶ���ɾ���ļ�¼
            for( i=0,FatBuffer.Demand[0]=Space,FatBuffer.Demand[1]=Space,FatBuffer.Demand[2]=Space;(FatBuffer.Demand[0]==Space)&&(FatBuffer.Demand[1]==Space)&&(FatBuffer.Demand[2]==Space)&&( i<((unsigned long)(FileInfo.FileSize)/(unsigned long)(DemandLength)) )&&(del==0);i++ )
            {//�������ѭ������Ϊ����Ƿ������ɾ���ļ�¼
                ReadTheRecord( );
                if( (FatBuffer.Demand[0]==Space)&&(FatBuffer.Demand[1]==Space)&&(FatBuffer.Demand[2]==Space) )
                {//������ɾ���ļ�¼
                   if( BackOrFore_Demand()==2 )//��ѹ�� --���ü�
                   {
                        FatBuffer.LastRecordNumber = FatBuffer.RecordNumber ;
                        FatBuffer.RecordNumber --;
                        if( FatBuffer.RecordNumber==0 )
                           FatBuffer.RecordNumber = 1;//��ʱ��Ϊ1����ӦΪ��ǰ���������¼                        
                   }
                   else//��ѹ�� ���ü� �������Ǹհ�ѹ�� ��ѯ
                   {
                        FatBuffer.LastRecordNumber = FatBuffer.RecordNumber ;
                        FatBuffer.RecordNumber ++;
                   }
                }
                else////������ȡ�ɹ���û�ж��� ɾ���ļ�¼
                {
                  del=1;//��������ѭ����������ʾ��������
                }
            }
        }        
      }   
      if( i<((unsigned long)(FileInfo.FileSize)/(unsigned long)(DemandLength)) )  //�������������б��¼�Ƿ�ȫ��ɾ��
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
    }
    else
    {
        NOTOpenFile();
    }
  }
}

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