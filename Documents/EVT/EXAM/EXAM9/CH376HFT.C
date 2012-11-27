/* 2008.10.18
****************************************
**  Copyright  (C)  W.ch  1999-2009   **
**  Web:  http://www.winchiphead.com  **
****************************************
**  USB Host File Interface for CH376 **
**  TC2.0@PC, KC7.0@MCS51             **
****************************************
*/
/* CH376 �����ļ�ϵͳ�ӿ� */

/* MCS-51��Ƭ��C���Ե�U���ļ���дʾ������ */
/* ������������ʾ������Ŀ¼,�Լ��򿪶༶Ŀ¼�µ��ļ�����Ŀ¼ */

/* C51   CH376HFT.C */
/* LX51  CH376HFT.OBJ */
/* OHX51 CH376HFT */

#include <reg52.h>
#include <stdio.h>
#include <string.h>

#include "..\HAL.H"
#include "..\HAL_BASE.C"
#include "..\DEBUG.H"
#include "..\DEBUG.C"
#include "..\PARA_HW.C"		/* Ӳ�����߲������ӷ�ʽ */
//#include "..\PARA_SW.C"		/* ����ģ�Ⲣ�����ӷ�ʽ */
//#include "..\SPI_HW.C"		/* Ӳ��SPI���ӷ�ʽ */
//#include "..\SPI_SW.C"		/* ����ģ��SPI��ʽ */
//#include "..\UART_HW.C"		/* Ӳ���첽�������ӷ�ʽ */
#define		EN_DIR_CREATE	1	/* ֧���½��༶��Ŀ¼ */
#include "..\FILE_SYS.H"
#include "..\FILE_SYS.C"

UINT8		idata	buf[64];

main( ) {
	UINT8	s;

	mDelaymS( 100 );  /* ��ʱ100���� */
	mInitSTDIO( );  /* Ϊ���ü����ͨ�����ڼ����ʾ���� */
	printf( "Start\n" );

	s = mInitCH376Host( );  /* ��ʼ��CH376 */
	mStopIfError( s );
/* ������·��ʼ�� */

	while ( 1 ) {
		printf( "Wait Udisk/SD\n" );
		while ( CH376DiskConnect( ) != USB_INT_SUCCESS ) {  /* ���U���Ƿ�����,�ȴ�U�̲���,����SD��,�����ɵ�Ƭ��ֱ�Ӳ�ѯSD�����Ĳ��״̬���� */
			mDelaymS( 100 );
		}
		mDelaymS( 200 );  /* ��ʱ,��ѡ����,�е�USB�洢����Ҫ��ʮ�������ʱ */

/* ���ڼ�⵽USB�豸��,���ȴ�10*50mS */
		for ( s = 0; s < 10; s ++ ) {  /* ��ȴ�ʱ��,10*50mS */
			mDelaymS( 50 );
			printf( "Ready ?\n" );
			if ( CH376DiskMount( ) == USB_INT_SUCCESS ) break;  /* ��ʼ�����̲����Դ����Ƿ���� */
		}
//		s = CH376ReadBlock( buf );  /* �����Ҫ,���Զ�ȡ���ݿ�CH376_CMD_DATA.DiskMountInq,���س��� */
//		if ( s == sizeof( INQUIRY_DATA ) ) {  /* U�̵ĳ��̺Ͳ�Ʒ��Ϣ */
//			buf[ s ] = 0;
//			printf( "UdiskInfo: %s\n", ((P_INQUIRY_DATA)buf) -> VendorIdStr );
//		}

		printf( "Create Level 1 Directory /YEAR2008 \n" );
		s = CH376DirCreate( "/YEAR2008" );  /* �½����ߴ�Ŀ¼,��Ŀ¼���ڸ�Ŀ¼�� */
		if ( s == ERR_FOUND_NAME ) printf( "Found a file with same name\n" );
		mStopIfError( s );
		CH376FileClose( FALSE );  /* �ر�Ŀ¼ */

/* �����½�������Ŀ¼ */
		printf( "Create Level 2 Directory /YEAR2008/MONTH05 \n" );
		strcpy( buf, "/YEAR2008/MONTH05" );  /* Ŀ¼��,��Ŀ¼����YEAR2008��Ŀ¼��,YEAR2008Ŀ¼�������ȴ���,CH376DirCreatePath���ļ���������������RAM�� */
		s = CH376DirCreatePath( buf );  /* �½����ߴ�Ŀ¼,��Ŀ¼���ڶ༶Ŀ¼��,����·��������RAM�� */
		if ( s == ERR_FOUND_NAME ) printf( "Found a file with same name\n" );
		mStopIfError( s );
//		CH376FileClose( FALSE );  /* ��ʱ���ر�Ŀ¼,��Ϊ����Ҫ������½����ߴ򿪵�Ŀ¼���½��ļ� */

/* Ŀ¼�½����ߴ򿪳ɹ�,�����������Ŀ¼���½�һ����ʾ�ļ�,
   ���ַ���:һ��CH376FileCreatePath�½��༶Ŀ¼�µ��ļ�,����CH376FileCreate�ڵ�ǰĿ¼���½��ļ�(���ǰ������ϼ�Ŀ¼����û�йر�) */
		printf( "Create New File /YEAR2008/MONTH05/DEMO2008.TXT \n" );

//		strcpy( buf, "/YEAR2008/MONTH05/DEMO2008.TXT" );  /* �ļ���,��Ŀ¼����YEAR2008/MONTH05�༶Ŀ¼��,Ŀ¼�������ȴ���,CH376FileCreatePath���ļ���������������RAM�� */
//		s = CH376FileCreatePath( buf );  /* �½��༶Ŀ¼�µ��ļ�,����ļ��Ѿ���������ɾ�������½�,����·��������RAM�� */

		s = CH376FileCreate( "DEMO2008.TXT" );  /* �ڵ�ǰĿ¼���½��ļ�,����ļ��Ѿ���������ɾ�������½� */

		mStopIfError( s );

		printf( "Write some data to file\n" );
		strcpy( buf, "This is ��ʾ����\xd\xa" );
		s = CH376ByteWrite( buf, strlen(buf), NULL );  /* ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */
		mStopIfError( s );

		printf( "Close\n" );
		s = CH376FileClose( TRUE );  /* �ر��ļ�,�Զ������ļ����� */
		mStopIfError( s );

/* ����򿪶༶Ŀ¼�µ��ļ� */
		printf( "Open File /YEAR2008/MONTH05/DEMO2008.TXT \n" );
		strcpy( buf, "/YEAR2008/MONTH05/DEMO2008.TXT" );  /* CH376FileOpenPath���ļ���������������RAM�� */
		s = CH376FileOpenPath( buf );  /* ֱ�Ӵ򿪶༶Ŀ¼�µ��ļ�,����CH376FileOpenPath�ӳ����ڲ��ɶ���𼶴���϶��� */
		mStopIfError( s );

		printf( "Close\n" );
		s = CH376FileClose( FALSE );  /* �ر��ļ� */
		mStopIfError( s );

		printf( "Take out\n" );
		while ( CH376DiskConnect( ) == USB_INT_SUCCESS ) {  /* ���U���Ƿ�����,�ȴ�U�̰γ� */
			mDelaymS( 100 );
		}
		mDelaymS( 200 );
	}
}