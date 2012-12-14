/*============================================ ͷ�ļ�˵�� ============================================================
ͷ�ļ����ƣ�
ͷ�ļ���;��
================================================ END ===============================================================*/

#ifndef __MemoryManagement_H
#define __MemoryManagement_H

//////////////////////////////////// �������� /////////////////////////////////////
void WriteANameForANewFile(void);
void ZhuangHaoDianHao(void);
void ScreenControlForMemory(void);
void SaveControl(void);
uchar MemoryInit(void);
////////////////////////////////////// END ////////////////////////////////////////
#define _EINT  __enable_interrupt
#define _DINT  __disable_interrupt
/*********************************************************************************
�������ƣ�void SaveControl(void)
�������ܣ��洢����
����ʱ�䣺2010-05-02
˵    ����1��Save_Flag ���ڶ�ʱ�� TA0 ������
*********************************************************************************/
char FileName[10]={0,0,0,0,0,0X2E,0,0,0}; 
uchar USB_Disk_Connect_Flag;
void SaveControl(void)
{  
    uchar s;

  //if( (Save_Flag==1)&&(SaveTimeCount<5) )//���� Save_Flag ���ڶ�ʱ�� TA0 ������ģ����ԣ�������ʹ�� &&(SaveTimeCount<5)����Ϊ�˷�ֹ�����д��  
  if( (Save_Flag==1) )
  {          
    if( (USB_Disk_Connect_Flag == 0) || (CH376DiskConnect() == ERR_DISK_DISCON) ){
        if(MemoryInit() == 0){
            Save_Flag=0;
            return ;
        }
    }
    _DINT();

    WriteANameForANewFile();
    
    s = CH376FileOpenPath( FileName );
   
    if ( s == ERR_MISS_FILE ){
        s = CH376FileCreatePath( FileName );  /* �½��༶Ŀ¼�µ��ļ�,֧�ֶ༶Ŀ¼·��,���뻺����������RAM�� */
        //mStopIfError( s );
        s = CH376ByteLocate(0xFFFFFFFF);
        //mStopIfError( s );
        HeadingWrite();
        s = CH376ByteWrite( Heading, strlen(Heading), NULL );  /* ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */
        //mStopIfError( s );
        
    }else{
        s = CH376ByteLocate(0xFFFFFFFF);
        //mStopIfError( s );
    }
    ZhuangHaoDianHao();
    s = CH376ByteWrite( SaveBuffer, strlen(SaveBuffer), NULL );  /* ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */
    //mStopIfError( s );
    s = CH376FileClose( TRUE );  /* �ر��ļ�,�Զ������ļ�����,���ֽ�Ϊ��λд�ļ�,�����ó����ر��ļ��Ա��Զ������ļ����� */
    //mStopIfError( s );
    
    //FAT32_WriteFile( &FileInfo,SaveBuffer, SaveLength );
    ZhuangHaoAutomaticallyIncreases( );
    
    _EINT();
    Save_Flag = 2;
    
  }
}

/*********************************************************************************
�������ƣ�void ScreenControlForMemory(void)
�������ܣ��洢�����Կ���
����ʱ�䣺2010-05-02
˵    ����
*********************************************************************************/
void ScreenControlForMemory(void)
{
  
}

/*********************************************************************************
�������ƣ�void MemoryInit(void)
�������ܣ��洢����ʼ��
����ʱ�䣺2010-05-02
˵    ����
*********************************************************************************/
uchar MemoryInit(void)
{
    int i;
    uchar res;

    res = mInitCH376Host();
    if(res != USB_INT_SUCCESS){
        for(i = 0;i<30000;i++);
            res = mInitCH376Host();
        if(res != USB_INT_SUCCESS)
            goto MemoryInitRes;
    }
/* ��ѯU���Ƿ����ӣ�����USB_INT_SUCCESS��˵����ǰ������ */ 
    res = CH376DiskConnect();
    if(res != USB_INT_SUCCESS){
        for(i = 0;i<30000;i++);
            res = CH376DiskConnect();
        if(res != USB_INT_SUCCESS)
            goto MemoryInitRes;
    }

/* ��ѯU�̻�SD���Ƿ�׼���ã���ЩU�̿������ε��ò��ܳɹ� */  
    res = CH376DiskMount();
    if(res != USB_INT_SUCCESS){
        for(i = 0;i<30000;i++);
            res = CH376DiskMount();
        if(res != USB_INT_SUCCESS)
            goto MemoryInitRes;
    }
    USB_Disk_Connect_Flag = 1;
    return USB_Disk_Connect_Flag;
MemoryInitRes:
    USB_Disk_Connect_Flag = 0;
    return USB_Disk_Connect_Flag;
}

/*********************************************************************************
�������ƣ�void ZhuangHaoDianHao(void)
�������ܣ�
����ʱ�䣺2010-05-02
˵    ����
*********************************************************************************/
void ZhuangHaoDianHao(void)
{
    uchar i=0;

    SaveBuffer[0] = Position_data[1] + Parameter; //  ������
    SaveBuffer[1] = Position_data[2] + Parameter;
    SaveBuffer[2] = Position_data[3] + Parameter;
    SaveBuffer[3] = ',';
    SaveBuffer[4] = Position_data[4] + Parameter; //  ���� ׮��
    SaveBuffer[5] = Position_data[5] + Parameter;
    SaveBuffer[6] = Position_data[6] + Parameter;
    SaveBuffer[7] = ','; 

    for( i=0;i<7;i++ ){  // �����ѹ
        SaveBuffer[8+i] = mmmm[6-i] + Parameter ;
    }
    SaveBuffer[15] = ','; 

    for( i=0;i<7;i++ ){  //  ���� ����
    SaveBuffer[16+i] = mmma[6-i] + Parameter ;
    }

    SaveBuffer[23] = '\r'; // ����
    SaveBuffer[24] = '\n'; // ����
    SaveBuffer[25] = '\0';
}

/*********************************************************************************
�������ƣ�void WriteANameForANewFile(void)
�������ܣ�
����ʱ�䣺2010-05-02
˵    ����
*********************************************************************************/
void WriteANameForANewFile(void)
{
    FileName[0] = 0x5C;                       
    FileName[1] = 0x5C;                       
    FileName[2] = Position_data[0] + Parameter; //�����  
    FileName[3] = 0x5F;                       //���»���
    FileName[4] = FeatureSelection_data + Parameter;//����ѡ��
    FileName[5] = 0X2E;                       //.
    FileName[6] = 68;
    FileName[7] = 65;
    FileName[8] = 84;
    FileName[9] = '\0';
}

#endif
