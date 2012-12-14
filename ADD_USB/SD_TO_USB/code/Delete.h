



//////////////////////////////////// �������� /////////////////////////////////////
unsigned int DeleteOneRecord(void);
void DeleteControl(void);
////////////////////////////////////// END ////////////////////////////////////////
#if 1
/*********************************************************************************
�������ƣ�void DeleteOneRecord(void)
�������ܣ�ɾ��һ����¼
����ʱ�䣺2010-05-17
˵    ����1������ɾ���ļ�¼�������ڼ�����¼
*********************************************************************************/
unsigned int DeleteOneRecord(void)
{
    int i;
    char str[SaveLength+1];
    
    UINT32 RecordAddr;

    str[SaveLength] = '\0';
    
    if( ( CH376FileOpenPath( FileName )!= USB_INT_SUCCESS )||( CH376GetFileSize() <= strlen(Heading) ) ){
        //���ļ�ʧ�ܣ������ļ������м�¼��ɾ��
        NOTOpenFile();
        return FatBuffer.RecordNumber;
    }
    
    RecordAddr = CH376GetFileSize() - FatBuffer.RecordNumber * (SaveLength-1);

    for( i = 0;i < SaveLength ;i++){
        str[i] = ' ';
    }
    str[SaveLength - 3] = '\r';
    str[SaveLength - 2] = '\n';
    str[SaveLength - 1] = '\0';
    
    //Locate tail
    CH376ByteLocate(RecordAddr);
    CH376ByteWrite( str, strlen(str), NULL );  /* ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */

    CH376FileClose( TRUE );
    
    FatBuffer.RecordNumber --;
    return FatBuffer.RecordNumber;
}
#endif
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