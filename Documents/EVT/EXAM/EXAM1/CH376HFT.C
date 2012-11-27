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
/* ��������ʾ�ֽڶ�д,�ļ�ö��,�ļ�����, ���ڽ�U���е�/C51/CH376HFT.C�ļ��е�Сд��ĸת�ɴ�д��ĸ��, д���½����ļ�NEWFILE.TXT��,
   ����Ҳ���ԭ�ļ�CH376HFT.C, ��ô�ó�����ʾC51��Ŀ¼��������CH376��ͷ���ļ���, ���½�NEWFILE.TXT�ļ���д����ʾ��Ϣ,
   ����Ҳ���C51��Ŀ¼, ��ô�ó�����ʾ��Ŀ¼�µ������ļ���, ���½�NEWFILE.TXT�ļ���д����ʾ��Ϣ */

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
#define		EN_DISK_QUERY		1	/* ���ô��̲�ѯ */
#include "..\FILE_SYS.H"
#include "..\FILE_SYS.C"

UINT8		idata	buf[64];

UINT8	CopyAndConvertFile( PUINT8 SrcFileName, PUINT8 TarFileName ) {  /* �ļ�����,���ֽڷ�ʽ����,������Խ���ٶ�Խ�� */
/* SrcFileName Դ�ļ���,֧��·���ָ����Ͷ༶Ŀ¼,�ַ�����������RAM��
   TarFileName Ŀ���ļ���,֧��·���ָ����Ͷ༶Ŀ¼,�ַ�����������RAM�� */
	UINT8	s;
	UINT16	ThisLen, cnt;
	UINT32	FileSize, ByteCount;
	UINT8	TarName;
	UINT32	TarUpDirClust;
	ByteCount = 0;
	do {
		printf( "OpenSrc\n" );  /* ע���ӡ������˷�ʱ��,����ƽ�������ٶ� */
		s = CH376FileOpenPath( SrcFileName );  /* �򿪶༶Ŀ¼�µ��ļ�,���뻺����������RAM�� */
		if ( s != USB_INT_SUCCESS ) return( s );
		if ( ByteCount == 0 ) {  /* �״� */
			FileSize = CH376GetFileSize( );  /* ��ȡ��ǰ�ļ����� */
			printf( "SrcFileSz=%ld\n", FileSize );
		}
		else {  /* �ٴν��� */
			s = CH376ByteLocate( ByteCount );  /* ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ�뵽�ϴθ��ƽ���λ�� */
			if ( s != USB_INT_SUCCESS ) return( s );
		}
		printf( "Read\n" );
		s = CH376ByteRead( buf, sizeof( buf ), &ThisLen );  /* ���ֽ�Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ�,���󳤶�ͬ��������С,����ʵ�ʳ�����ThisLen�� */
		if ( s != USB_INT_SUCCESS ) return( s );
//		s = CH376FileClose( FALSE );  /* �ر��ļ�,���ڶ��������Բ��عر��ļ� */
//		if ( s != USB_INT_SUCCESS ) return( s );

		for ( cnt=0; cnt < ThisLen; cnt ++ ) {  /* ���������е�Сд�ַ�ת��Ϊ��д */
			s = buf[ cnt ];
			if ( s >= 'a' && s <= 'z' ) buf[ cnt ] = s - ( 'a' - 'A' );
		}

		if ( ByteCount == 0 ) {  /* �״�,Ŀ���ļ���δ���� */
			printf( "CreateTar\n" );
			TarName = CH376SeparatePath( TarFileName );  /* ��·���з�������һ���ļ�����Ŀ¼��,�������һ���ļ�����Ŀ¼����ƫ�� */
			if ( TarName ) {  /* �Ƕ༶Ŀ¼ */
				s = CH376FileOpenDir( TarFileName, TarName );  /* �򿪶༶Ŀ¼�µ����һ��Ŀ¼,�����½��ļ����ϼ�Ŀ¼ */
				if ( s != ERR_OPEN_DIR ) {  /* ��Ϊ�Ǵ��ϼ�Ŀ¼,����,������ǳɹ�����Ŀ¼,��ô˵�������� */
					if ( s == USB_INT_SUCCESS ) return( ERR_FOUND_NAME );  /* �м�·��������Ŀ¼��,������ļ�������� */
					else if ( s == ERR_MISS_FILE ) return( ERR_MISS_DIR );  /* �м�·����ĳ����Ŀ¼û���ҵ�,������Ŀ¼���ƴ��� */
					else return( s );  /* �������� */
				}
				TarUpDirClust = CH376ReadVar32( VAR_START_CLUSTER );  /* �ϼ�Ŀ¼����ʼ�غ� */
			}
			else TarUpDirClust = 0;  /* Ĭ���Ǹ�Ŀ¼����ʼ�غ� */
/* �ڵ�ǰĿ¼�½����ļ��½����ߴ򿪲���,��ȫ·���༶Ŀ¼�µ��ļ��½����ߴ򿪲������ٶȿ�,
   ����Ŀ���ļ����½����ߴ򿪲��ô˷�����(������Դ�ļ���ֱ�Ӵ�ȫ·���༶Ŀ¼�µ��ļ�,Ϊ����ٶ�,Ҳ�ɲ��մ˷��ӿ��ļ���),
   Ϊ��ʵ�ֵ�ǰĿ¼�µ��ļ��½����ߴ򿪲���,�ο����漸�д���,
   ����,Ҫ����ļ����ڵ��ϼ�Ŀ¼����ʼ�غ�,�൱�ڴ��ϼ�Ŀ¼,ͨ��CH376FileOpenPath���ϼ�Ŀ¼���,
   ���,Ҫ����ļ���ֱ�Ӷ��ļ���(ȥ���ϼ�Ŀ¼��,�����κ�·���ָ���,�������һ���ļ���),ͨ��CH376SeparatePath����Ŀ���ļ������ */
			s = CH376FileCreate( &TarFileName[TarName] );  /* �ڸ�Ŀ¼���ߵ�ǰĿ¼���½��ļ�,����ļ��Ѿ�������ô��ɾ�� */
			if ( s != USB_INT_SUCCESS ) return( s );
		}
		else {  /* �ٴν���,Ŀ���ļ��Ѵ��� */
			printf( "OpenTar\n" );
			CH376WriteVar32( VAR_START_CLUSTER, TarUpDirClust );  /* ��Ŀ���ļ����ڵ��ϼ�Ŀ¼����ʼ�غ�����Ϊ��ǰ�غ�,�൱�ڴ��ϼ�Ŀ¼ */
			s = CH376FileOpen( &TarFileName[TarName] );  /* ���ļ� */
			if ( s != USB_INT_SUCCESS ) return( s );
			s = CH376ByteLocate( ByteCount );  /* ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ�뵽�ϴθ��ƽ���λ�� */
			if ( s != USB_INT_SUCCESS ) return( s );
		}
		printf( "Write\n" );
		s = CH376ByteWrite( buf, ThisLen, NULL );  /* ���ֽ�Ϊ��λ��ǰλ��д�����ݿ�,����û�д��̿ռ�,���򷵻�ʵ�ʳ���������ThisLen��� */
		if ( s != USB_INT_SUCCESS ) return( s );
		printf( "CloseTar\n" );
		s = CH376FileClose( TRUE );  /* �ر��ļ�,�����ֽڶ�д�����Զ������ļ����� */
		if ( s != USB_INT_SUCCESS ) return( s );
		ByteCount += ThisLen;
		if ( ThisLen < sizeof( buf ) ) {  /* ʵ�ʶ����ֽ���С����������ֽ���,˵��ԭ�ļ����� */
			if ( ByteCount != FileSize ) printf( "Error on SourceFile reading" );
			break;
		}
	} while( ByteCount < FileSize );
	return( USB_INT_SUCCESS );
}

main( ) {
	UINT8			i, s;
	P_FAT_DIR_INFO	pDir;
	UINT8	xdata	SrcName[64];
	UINT8	xdata	TarName[64];
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

/* ���ڼ�⵽USB�豸��,���ȴ�100*50mS,��Ҫ�����ЩMP3̫��,���ڼ�⵽USB�豸��������DISK_MOUNTED��,���ȴ�5*50mS,��Ҫ���DiskReady������ */
		for ( i = 0; i < 100; i ++ ) {  /* ��ȴ�ʱ��,100*50mS */
			mDelaymS( 50 );
			printf( "Ready ?\n" );
			s = CH376DiskMount( );  /* ��ʼ�����̲����Դ����Ƿ���� */
			if ( s == USB_INT_SUCCESS ) break;  /* ׼���� */
			else if ( s == ERR_DISK_DISCON ) break;  /* ��⵽�Ͽ�,���¼�Ⲣ��ʱ */
			if ( CH376GetDiskStatus( ) >= DEF_DISK_MOUNTED && i >= 5 ) break;  /* �е�U�����Ƿ���δ׼����,�������Ժ���,ֻҪ�佨������MOUNTED�ҳ���5*50mS */
		}
		if ( s == ERR_DISK_DISCON ) {  /* ��⵽�Ͽ�,���¼�Ⲣ��ʱ */
			printf( "Device gone\n" );
			continue;
		}
		if ( CH376GetDiskStatus( ) < DEF_DISK_MOUNTED ) {  /* δ֪USB�豸,����USB���̡���ӡ���� */
			printf( "Unknown device\n" );
			goto UnknownUsbDevice;
		}
		i = CH376ReadBlock( buf );  /* �����Ҫ,���Զ�ȡ���ݿ�CH376_CMD_DATA.DiskMountInq,���س��� */
		if ( i == sizeof( INQUIRY_DATA ) ) {  /* U�̵ĳ��̺Ͳ�Ʒ��Ϣ */
			buf[ i ] = 0;
			printf( "UdiskInfo: %s\n", ((P_INQUIRY_DATA)buf) -> VendorIdStr );
		}

/* ��ȡԭ�ļ� */
		strcpy( SrcName, "\\C51\\CH376HFT.C" );  /* Դ�ļ���,�༶Ŀ¼�µ��ļ�����·�������븴�Ƶ�RAM���ٴ���,����Ŀ¼���ߵ�ǰĿ¼�µ��ļ���������RAM����ROM�� */
		strcpy( TarName, "\\NEWFILE.TXT" );  /* Ŀ���ļ��� */
		printf( "Open\n" );
		s = CH376FileOpenPath( SrcName );  /* ���ļ�,���ļ���C51��Ŀ¼�� */
		if ( s == ERR_MISS_DIR || s == ERR_MISS_FILE ) {  /* û���ҵ�Ŀ¼����û���ҵ��ļ� */
/* �г��ļ�,����ö�ٿ��Բο�EXAM13ȫ��ö�� */
			if ( s == ERR_MISS_DIR ) strcpy( buf, "\\*" );  /* C51��Ŀ¼���������г���Ŀ¼�µ��ļ� */
			else strcpy( buf, "\\C51\\CH376*" );  /* CH376HFT.C�ļ����������г�\C51��Ŀ¼�µ���CH376��ͷ���ļ� */
			printf( "List file %s\n", buf );
			s = CH376FileOpenPath( buf );  /* ö�ٶ༶Ŀ¼�µ��ļ�����Ŀ¼,���뻺����������RAM�� */
			while ( s == USB_INT_DISK_READ ) {  /* ö�ٵ�ƥ����ļ� */
				CH376ReadBlock( buf );  /* ��ȡö�ٵ����ļ���FAT_DIR_INFO�ṹ,���س�������sizeof( FAT_DIR_INFO ) */
				pDir = (P_FAT_DIR_INFO)buf;  /* ��ǰ�ļ�Ŀ¼��Ϣ */
				if ( pDir -> DIR_Name[0] != '.' ) {  /* ���Ǳ��������ϼ�Ŀ¼�������,������붪�������� */
					if ( pDir -> DIR_Name[0] == 0x05 ) pDir -> DIR_Name[0] = 0xE5;  /* �����ַ��滻 */
					pDir -> DIR_Attr = 0;  /* ǿ���ļ����ַ��������Ա��ӡ��� */
					printf( "*** EnumName: %s\n", pDir -> DIR_Name );  /* ��ӡ����,ԭʼ8+3��ʽ,δ�����ɺ�С����ָ��� */
				}
				xWriteCH376Cmd( CMD0H_FILE_ENUM_GO );  /* ����ö���ļ���Ŀ¼ */
				xEndCH376Cmd( );
				s = Wait376Interrupt( );
			}
			if ( s != ERR_MISS_FILE ) mStopIfError( s );  /* �������� */
			printf( "Create\n" );
			s = CH376FileCreatePath( TarName );  /* �½��༶Ŀ¼�µ��ļ�,֧�ֶ༶Ŀ¼·��,���뻺����������RAM�� */
			mStopIfError( s );
			printf( "Write\n" );
			strcpy( buf, "�Ҳ���/C51/CH376HFT.C�ļ�\xd\n" );
			s = CH376ByteWrite( buf, strlen(buf), NULL );  /* ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */
			mStopIfError( s );
			printf( "Close\n" );
			s = CH376FileClose( TRUE );  /* �ر��ļ�,�����ֽڶ�д�����Զ������ļ����� */
			mStopIfError( s );
		}
		else {  /* �ҵ��ļ����߳��� */
			mStopIfError( s );
			s = CopyAndConvertFile( SrcName, TarName );  /* �ļ����� */
			mStopIfError( s );
		}

/* ɾ��ĳ�ļ� */
/*		printf( "Erase\n" );
		s = CH376FileErase( "/OLD" );  ɾ���ļ�
		if ( s != USB_INT_SUCCESS ) printf( "Error: %02X\n", (UINT16)s );  ��ʾ����
*/

/* ���U�̻���SD����ʣ��ռ� */
/*		printf( "DiskQuery: " );
		s = CH376DiskQuery( (PUINT32)buf );  ��ѯ����ʣ��ռ���Ϣ,������
		mStopIfError( s );
//		printf( "free cap = %ld MB\n", *(PUINT32)buf * DEF_SECTOR_SIZE / 1000000 );  δ������������������С��,����1M����Ϊ���ֽڵ�λ
		printf( "free cap = %ld MB\n", *(PUINT32)buf / ( 1000000 / DEF_SECTOR_SIZE ) );  ����һ�еļ�����ܻ����,����˳����� */

UnknownUsbDevice:
		printf( "Take out\n" );
		while ( CH376DiskConnect( ) == USB_INT_SUCCESS ) {  /* ���U���Ƿ�����,�ȴ�U�̰γ� */
			mDelaymS( 100 );
		}
		mDelaymS( 200 );
	}
}