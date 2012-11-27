/* 2008.10.18
****************************************
**  Copyright  (C)  W.ch  1999-2009   **
**  Web:  http://www.winchiphead.com  **
****************************************
**  USB Host File Interface for CH376 **
**  TC2.0@PC, KC7.0@MCS51			 **
****************************************
*/
/* CH376 �����ļ�ϵͳ�ӿ� */

/* MCS-51��Ƭ��C���Ե�U���ļ���дʾ������ */
/* �������ǳ��ļ�������ʾ��, �����������ļ����ʹӶ��ļ�����ö�Ӧ�ĳ��ļ��� */

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
#define		EN_LONG_NAME		1	/* ֧�ֳ��ļ��� */
#include "..\FILE_SYS.H"

UINT8		idata	buf[64];
#define		GlobalBuf	buf		/* ���ļ����ӳ�����Ҫ�ṩȫ�ֻ�����,���Ȳ�С��64�ֽ� */

#include "..\FILE_SYS.C"


//#define		MAX_PATH_LEN		80
//UINT8	xdata	PathNameBuf[ MAX_PATH_LEN ];		/* ���ȫ·���Ķ��ļ��� */
//#define		LONG_NAME_BUF_LEN	( LONG_NAME_PER_DIR * 20 )	/* ���ж���ĳ��ļ�������������,��СֵΪLONG_NAME_PER_DIR*1 */
UINT8	xdata	LongNameBuf[ LONG_NAME_BUF_LEN ];	/* ��ų��ļ��� */

/* ���ļ���ʾ��1, ����UNICODE����С�˱���(ע:MCS51�Ǵ�˸�ʽ�ĵ�Ƭ��,��ÿ�����ֽڵ�ǰ�����ֽڻ���), ������LongName1���������(���ĳ��ļ���):
�������ļ������������������� 1.����(unicode ���)���ַ���ĩβ������0��ʾ����;2.ANSI������ļ���.TXT */
UINT8	code	LongName1[] =
{
	0xFA, 0x5E, 0xCB, 0x7A, 0x7F, 0x95, 0x87, 0x65, 0xF6, 0x4E, 0x0D, 0x54, 0x0C, 0xFF, 0x93, 0x8F,
	0x65, 0x51, 0x24, 0x4E, 0x2A, 0x4E, 0xC2, 0x53, 0x70, 0x65, 0x1A, 0xFF, 0x20, 0x00, 0x31, 0x00,
	0x2E, 0x00, 0xC7, 0x91, 0x28, 0x75, 0x28, 0x00, 0x75, 0x00, 0x6E, 0x00, 0x69, 0x00, 0x63, 0x00,
	0x6F, 0x00, 0x64, 0x00, 0x65, 0x00, 0x20, 0x00, 0x27, 0x59, 0xEF, 0x7A, 0x29, 0x00, 0x0C, 0xFF,
	0x57, 0x5B, 0x26, 0x7B, 0x32, 0x4E, 0x2B, 0x67, 0x3E, 0x5C, 0x28, 0x75, 0x24, 0x4E, 0x2A, 0x4E,
	0x30, 0x00, 0x68, 0x88, 0x3A, 0x79, 0xD3, 0x7E, 0x5F, 0x67, 0x3B, 0x00, 0x32, 0x00, 0x2E, 0x00,
	0x41, 0x00, 0x4E, 0x00, 0x53, 0x00, 0x49, 0x00, 0x16, 0x7F, 0x01, 0x78, 0xED, 0x77, 0x87, 0x65,
	0xF6, 0x4E, 0x0D, 0x54, 0x2E, 0x00, 0x54, 0x00, 0x58, 0x00, 0x54, 0x00
};

/* ���ļ���ʾ��2, �˴���ֻ����ͨ���ֽ�Ӣ���ַ���ʾ, ���������л��Ƚ���ת��Ϊ���ֽڵ�С��UNICODE����, Ȼ������UNICODE������Ϊ�����ĳ��ļ��� */
UINT8	code	LongName2[] =
{
	"This is Long Name File !!!.H"
};

main( )
{
	UINT8	s;
	UINT16	j;

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

/*==================== ������ʾ��������ȡ���ļ���,��������(��Ӣ�ĸ�һ��),Ȼ���ȡ������ ============================*/
		printf( "Create file with Chinese long name\n" );
		memcpy( LongNameBuf, LongName1, sizeof(LongName1) );  // ���Ƴ��ļ�����LongNameBuf���ļ���������
		LongNameBuf[sizeof(LongName1)] = 0x00;  // ĩβ������0��ʾ����
		LongNameBuf[sizeof(LongName1)+1] = 0x00;
//		strcpy( PathNameBuf, "/C51/���ļ���.TXT" );  // ���Ƹó��ļ�����ANSI�����ȫ·���Ķ��ļ���(8+3��ʽ),���ļ����ɳ��ļ�������
/* �������ļ���, ������������: 1.ANSI�����ȫ·���Ķ��ļ���; 2.������0��ʾ������unicode�ַ��ĳ��ļ��� */
		s = CH376CreateLongName( "/C51/���ļ���.TXT", LongNameBuf );  /* �½����г��ļ������ļ� */
		if ( s == USB_INT_SUCCESS ) printf( "Created Chinese Long Name OK!!\n" );
		else if ( s == ERR_NAME_EXIST ) printf( "The short name already exist !\n" );
		else printf( "Error Code: %02X\n", (UINT16)s );

		printf( "Create file with English long name\n" );
		for ( j = 0; LongName2[j] != 0; j++ ) {  /* ���Ʋ�ת�����ļ�����LongNameBuf���ļ��������� */
			LongNameBuf[j*2] = LongName2[j];  /* ��Ӣ���ַ�ת��Ϊ���ֽڵ�С��UNICODE���� */
			LongNameBuf[j*2+1] = 0x00;
		}
		LongNameBuf[j*2] = 0x00;  // ĩβ������0��ʾ����
		LongNameBuf[j*2+1] = 0x00;
//		strcpy( PathNameBuf, "/LONGNAME.H" );  // ���Ƹó��ļ�����ANSI�����ȫ·���Ķ��ļ���(8+3��ʽ),���ļ����ɳ��ļ�������(ֻҪ����ͻ,��ʵ��㶨)
		s = CH376CreateLongName( "/LONGNAME.H", LongNameBuf );  /* �½����г��ļ������ļ� */
		if ( s == USB_INT_SUCCESS ) printf( "Created English Long Name OK!!\n" );
		else if ( s == ERR_NAME_EXIST ) printf( "The short name already exist !\n" );
		else printf( "Error Code: %02X\n", (UINT16)s );

		printf( "Get Chinese long name from short name\n" );
//		strcpy( PathNameBuf, "/C51/���ļ���.TXT" );  // ���ļ���������·��
		s = CH376GetLongName( "/C51/���ļ���.TXT", LongNameBuf );  /* �ɶ��ļ�������Ŀ¼(�ļ���)�������Ӧ�ĳ��ļ��� */
		if ( s == USB_INT_SUCCESS ) {
			printf( "LongNameBuf: " );  // ������ʾ��������ĳ��ļ���,���ļ�����UNICODEС�˱��뷽ʽ���,����0��ʾ����
			for ( j=0; j<LONG_NAME_BUF_LEN; j+=2 ) {
				printf( "%02X-%02X,", (UINT16)(LongNameBuf[j]), (UINT16)(LongNameBuf[j+1]) );  /* UNICODE���벻����ֱ����ʾ,�Ȱ�ʮ���������ݴ�ӡ��� */
				if ( *(PUINT16)(&LongNameBuf[j]) == 0 ) break;  /* ���� */
			}
			printf( "END\n" );
		}
		else printf( "Error Code: %02X\n", (UINT16)s );

		printf( "Get English long name from short name\n" );
//		strcpy( PathNameBuf, "/LONGNAME.H" );  // ���ļ���������·��
		s = CH376GetLongName( "/LONGNAME.H", LongNameBuf );  /* �ɶ��ļ�������Ŀ¼(�ļ���)�������Ӧ�ĳ��ļ��� */
		if ( s == USB_INT_SUCCESS ) {
			printf( "LongNameBuf: " );  // ������ʾ��������ĳ��ļ���,���ļ�����UNICODEС�˱��뷽ʽ���,����0��ʾ����
			for ( j=0; j<LONG_NAME_BUF_LEN; j+=2 ) {
				printf( "%02X-%02X,", (UINT16)(LongNameBuf[j]), (UINT16)(LongNameBuf[j+1]) );  /* UNICODE���벻����ֱ����ʾ,�Ȱ�ʮ���������ݴ�ӡ��� */
				if ( *(PUINT16)(&LongNameBuf[j]) == 0 ) break;  /* ���� */
			}
			printf( "END\n" );
			printf( "LongName is: " );  // �����Ӣ���ַ���UNICODE����,��ô����ֱ�Ӵ�ӡ���
			for ( j=0; j<LONG_NAME_BUF_LEN; j+=2 ) {  /* */
				printf( "%c", LongNameBuf[j] );  /* Ӣ��UNICODE�ַ����Դ�ӡ��� */
				if ( *(PUINT16)(&LongNameBuf[j]) == 0 ) break;  /* ���� */
			}
			printf( "\n" );
		}
		else printf( "Error Code: %02X\n", (UINT16)s );
/*==============================================================================*/

		printf( "Take out\n" );
		while ( CH376DiskConnect( ) == USB_INT_SUCCESS ) {  /* ���U���Ƿ�����,�ȴ�U�̰γ� */
			mDelaymS( 100 );
		}
		mDelaymS( 200 );
	}
}