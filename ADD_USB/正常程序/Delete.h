



//////////////////////////////////// �������� /////////////////////////////////////
unsigned int DeleteOneRecord(void);
void DeleteControl(void);
////////////////////////////////////// END ////////////////////////////////////////

/*********************************************************************************
�������ƣ�void DeleteOneRecord(void)
�������ܣ�ɾ��һ����¼
����ʱ�䣺2010-05-17
˵    ����1������ɾ���ļ�¼�������ڼ�����¼
*********************************************************************************/
unsigned int DeleteOneRecord(void)
{  
  uint  offset_start = FatBuffer.OffsetInBuffer_Start_RecordNumber;//0--511,���� FAT32_Buffer ���±�
  //uint  offset_end = FatBuffer.OffsetInBuffer_RecordNumber;
  //uchar offsetCount_FromZero = 0;
  //�����ж�Ҫɾ����������¼�Ƿ�������������
  if( FatBuffer.TheFirstPartForDemand_Sector==FatBuffer.TheSecondPartForDemand_Sector )//һ��������
  {
      FAT32_ReadSector((((FatBuffer.TheFirstPartForDemand_Cluster)-2)*(Init_Arg.SectorsPerClust))+Init_Arg.FirstDataSector + FatBuffer.TheFirstPartForDemand_Sector,FAT32_Buffer);//
      for( ;offset_start<FatBuffer.OffsetInBuffer_RecordNumber;offset_start++ )
        FAT32_Buffer[offset_start] = Space;//ע��FAT32_Buffer[FatBuffer.OffsetInBuffer_RecordNumber]��Ļ��з�����
      ///������������д������
      FAT32_WriteSector( (((FatBuffer.TheFirstPartForDemand_Cluster)-2)*(Init_Arg.SectorsPerClust))+Init_Arg.FirstDataSector + FatBuffer.TheFirstPartForDemand_Sector, FAT32_Buffer );
  }
  else//����������
  {
      //���ȶԼ�¼��ǰ�벿�ֲ���
      FAT32_ReadSector((((FatBuffer.TheFirstPartForDemand_Cluster)-2)*(Init_Arg.SectorsPerClust))+Init_Arg.FirstDataSector + FatBuffer.TheFirstPartForDemand_Sector,FAT32_Buffer);//
      for( ;offset_start<Init_Arg.BytesPerSector; offset_start++ )
        FAT32_Buffer[offset_start] = Space;
      FAT32_WriteSector( (((FatBuffer.TheFirstPartForDemand_Cluster)-2)*(Init_Arg.SectorsPerClust))+Init_Arg.FirstDataSector + FatBuffer.TheFirstPartForDemand_Sector, FAT32_Buffer );
      //�Լ�¼�� ��� ���ֲ���
      FAT32_ReadSector((((FatBuffer.TheSecondPartForDemand_Cluster)-2)*(Init_Arg.SectorsPerClust))+Init_Arg.FirstDataSector + FatBuffer.TheSecondPartForDemand_Sector,FAT32_Buffer);//
      for( offset_start=0;offset_start<FatBuffer.OffsetInBuffer_RecordNumber;offset_start++ )
        FAT32_Buffer[offset_start] = Space;
      FAT32_WriteSector( (((FatBuffer.TheSecondPartForDemand_Cluster)-2)*(Init_Arg.SectorsPerClust))+Init_Arg.FirstDataSector + FatBuffer.TheSecondPartForDemand_Sector, FAT32_Buffer );
  }
  return FatBuffer.RecordNumber;
}

/*********************************************************************************
�������ƣ�void DeleteControl(void)
�������ܣ�
����ʱ�䣺2010-05-17
˵    ����1����ѹ��ɾ��������Ļ������ɾ������-----�ڲ�ѯ����ʾ��ʵ��
          2����Ļ������ɾ����ʱ��Ҫ��ʾ����Ա���ڲ�ѯ�ļ�¼��Ϣ��
          3����Ļ��ɾ��������󣬾���ʾ FatBuffer.RecordNumber - 1 �ļ�¼
*********************************************************************************/
void DeleteControl(void)
{
  if( Delete_flag == 1 )//�հ�ѹ��ɾ����
  {     
      DemandControl();//ɾ�����ڲ�ѯ�Ļ����ϵĲ��������ԣ�һ��Ҫ��֤��ѯ������
      DeleteOneRecord();
      Delete_flag = 2;
  }
}