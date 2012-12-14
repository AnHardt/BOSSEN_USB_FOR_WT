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
void MemoryInit(void);
////////////////////////////////////// END ////////////////////////////////////////

/*********************************************************************************
�������ƣ�void SaveControl(void)
�������ܣ��洢����
����ʱ�䣺2010-05-02
˵    ����1��Save_Flag ���ڶ�ʱ�� TA0 ������
*********************************************************************************/
char FileName[9]={0,0,0,0,0,0X2E,0,0,0}; 
void SaveControl(void)
{  
  //if( (Save_Flag==1)&&(SaveTimeCount<5) )//���� Save_Flag ���ڶ�ʱ�� TA0 ������ģ����ԣ�������ʹ�� &&(SaveTimeCount<5)����Ϊ�˷�ֹ�����д��  
  if( (Save_Flag==1) )
  {          
    ZhuangHaoDianHao();
    _DINT();
    //(FAT32_OpenFile("\\TEST.TXT")) ; 
    /*
    memset( FileName,0,9 );    
    FileName[0] = 0x5C;
    FileName[1] = 0x5C;  
    FileName[2] = Position_data[4]+Parameter;
    FileName[3] = Position_data[5]+Parameter;
    FileName[4] = Position_data[6]+Parameter;
    FileName[5] = 0X2E;
    FileName[6] = 68;
    FileName[7] = 65;
    FileName[8] = 84;  
    */
    /*
    memset( FileName,0,7 );    
    FileName[0] = 0x5C;
    FileName[1] = 0x5C;  
    FileName[2] = Position_data[0]+Parameter;     
    FileName[3] = 0X2E;
    FileName[4] = 68;
    FileName[5] = 65;
    FileName[6] = 84;  
    */
    WriteANameForANewFile();
    FAT32_OpenFile(FileName) ;  
    FAT32_WriteFile( &FileInfo,SaveBuffer, SaveLength );
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
void MemoryInit(void)
{
  MMC_Init();
  MMC_get_volume_info();
  FAT32_Init(&Init_Arg);
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
  //uint second,hour,day,month,year;
  //uchar abc[7];
  
  SaveBuffer[0] = Position_data[1] + Parameter; //  ������
  SaveBuffer[1] = Position_data[2] + Parameter;
  SaveBuffer[2] = Position_data[3] + Parameter;
  SaveBuffer[3] = ',';
  SaveBuffer[4] = Position_data[4] + Parameter; //  ���� ׮��
  SaveBuffer[5] = Position_data[5] + Parameter;
  SaveBuffer[6] = Position_data[6] + Parameter;
  SaveBuffer[7] = ','; 
  
  for( i=0;i<7;i++ )  // �����ѹ
  {
    SaveBuffer[8+i] = mmmm[6-i] + Parameter ;
  }
  SaveBuffer[15] = ','; 
  
  for( i=0;i<7;i++ )  //  ���� ����
  {
    SaveBuffer[16+i] = mmma[6-i] + Parameter ;
  }
  /*
  SaveBuffer[23] = ','; 
  //////////////////////////////////////////
  R1302T_String( abc );//
  day = ((abc[3]&0xF0)>>4)*10 + (abc[3]&0x0F);
  month = ((abc[4]&0xF0)>>4)*10 + (abc[4]&0x0F);
  year = ((abc[6]&0xF0)>>4)*10 + (abc[6]&0x0F); 
  second=((abc[1]&0xF0)>>4)*10 + (abc[1]&0x0F); 
  hour=((abc[2]&0xF0)>>4)*10 + (abc[2]&0x0F);   
  day = 27;
  month = 02;
  year = 10;
  second = 23;
  hour = 12;
  SaveBuffer[24] = year/10 + Parameter; 
  SaveBuffer[25] = year%10 + Parameter;
  SaveBuffer[26] = '-';
  SaveBuffer[27] = month/10 + Parameter; 
  SaveBuffer[28] = month%10 + Parameter; 
  SaveBuffer[29] = '-';
  SaveBuffer[30] = day/10 + Parameter; 
  SaveBuffer[31] = day%10 + Parameter; 
  SaveBuffer[32] = ','; 
  SaveBuffer[33] = hour/10 + Parameter; 
  SaveBuffer[34] = hour%10 + Parameter; 
  SaveBuffer[35] = ':'; 
  SaveBuffer[36] = second/10 + Parameter; 
  SaveBuffer[37] = second%10 + Parameter; 
  //////////////////////////////////////
  //SaveBuffer[24] = '\n'; // �س�
  SaveBuffer[38] = '\r'; // ����
  */
  SaveBuffer[23] = '\r'; // ����
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
}

#endif
