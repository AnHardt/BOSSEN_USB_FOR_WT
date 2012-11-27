/* �ó�����80��C������ܹ���ȡFAT32/FAT16/FAT12�ļ�ϵͳU�̻���SD���ĸ�Ŀ¼,���Կ�����Ŀ¼�µ��ļ���,�ó���û���κδ�����,����Ϊʵ��ο� */
/* ��Ƭ����дU�̵ĳ����Ϊ4��: Ӳ��USB�ӿڲ�, BulkOnly����Э���, RBC/SCSI�����, FAT�ļ�ϵͳ�� */

#include <stdio.h>
#include "..\CH376INC.H"		/* ����CH376������뼰����״̬ */
#include <reg52.h>			/* ���¶���������MCS-51��Ƭ��,������Ƭ�������޸� */
UINT8V	xdata	CH376_CMD_PORT _at_ 0xBDF1;	/* CH376����˿ڵ�I/O��ַ */
UINT8V	xdata	CH376_DAT_PORT _at_ 0xBCF0;	/* CH376���ݶ˿ڵ�I/O��ַ */

/* ********** Ӳ��USB�ӿڲ�,����������ʡ����,��Ƭ����Ҫ��CH376�ӿڰ� ************************************************************ */
void	mDelaymS( UINT8 delay ) {		/* �Ժ���Ϊ��λ��ʱ,����ȷ,������24MHzʱ��MCS51 */
	UINT8	i, j, c;
	for ( i = delay; i != 0; i -- ) {
		for ( j = 200; j != 0; j -- ) c += 3;  /* ��24MHzʱ������ʱ500uS */
		for ( j = 200; j != 0; j -- ) c += 3;  /* ��24MHzʱ������ʱ500uS */
	}
}
void	xWriteCH376Cmd( UINT8 cmd ) {	/* ��CH376������˿�д������,���ڲ�С��2uS,�����Ƭ���Ͽ�����ʱ */
	CH376_CMD_PORT=cmd;
	for ( cmd = 2; cmd != 0; cmd -- );	/* ����������ǰ��Ӧ�ø���ʱ1.5uS,����MCS51���Բ���Ҫ��ʱ */
}
#define	xWriteCH376Data( d )	{ CH376_DAT_PORT=d; }	/* ��CH376�����ݶ˿�д������,���ڲ�С��0.6uS,�����Ƭ���Ͽ�����ʱ,MCS51��Ƭ����������������ʱ */
#define	xReadCH376Data( )		( CH376_DAT_PORT )		/* ��CH376�����ݶ˿ڶ�������,���ڲ�С��0.6uS,�����Ƭ���Ͽ�����ʱ,MCS51��Ƭ����������������ʱ */
UINT8 mWaitInterrupt( void ) {	/* �ȴ�CH376�жϲ���ȡ״̬,�����˵ȴ��������,���ز���״̬ */
	while( CH376_CMD_PORT & PARA_STATE_INTB );  /* ��ѯ�ȴ�CH376��������ж�(INT#�͵�ƽ) */
	xWriteCH376Cmd( CMD_GET_STATUS );  /* ������������ж�,��ȡ�ж�״̬ */
	return( xReadCH376Data( ) );
}
/* ********** BulkOnly����Э���,��CH376������,�����д��Ƭ������ ************************************************************ */
/* ********** RBC/SCSI�����,��CH376������,�����д��Ƭ������ **************************************************************** */
/* ********** FAT�ļ�ϵͳ��,��Ȼ��CH376������,����Ҫд���򷢳�����շ����� ************************************************** */
void	mInitSTDIO( void ) {	/* �����ڵ�����;����ʾ���ݵ�PC��,��ó�������ȫ�޹�,Ϊprintf��getkey���������ʼ������ */
	SCON = 0x50; PCON = 0x80; TMOD = 0x20; TH1 = 24000000/32/9600; TR1 = 1; TI = 1;  /* 24MHz����, 9600bps */
}
void	mStopIfError( UINT8 iErrCode ) {	/* ���������ֹͣ���в���ʾ����״̬,��ʽӦ�û���Ҫ�������� */
	if ( iErrCode == USB_INT_SUCCESS ) return;
	printf( "Error status, %02X\n", (UINT16)iErrCode );
}
main( ) {
	UINT8	s;
	mDelaymS( 100 );  /* ��ʱ100���� */
	mInitSTDIO( );
	xWriteCH376Cmd( CMD_SET_USB_MODE );  /* ��ʼ��CH376,����USB����ģʽ */
	xWriteCH376Data( 6 );  /* ģʽ����,�Զ����USB�豸����,����3����SD�� */
	while ( 1 ) {
		printf( "Insert USB disk\n" );
		while ( mWaitInterrupt( ) != USB_INT_CONNECT );  /* �ȴ�U������,SD��ģʽ����Ҫ��Ƭ�����м��SD����� */
		mDelaymS( 250 );  /* ��ʱ�ȴ�U�̽�����������״̬ */
		xWriteCH376Cmd( CMD_DISK_MOUNT );  /* ��ʼ��U�̲������Ƿ����,ʵ����ʶ��U�̵����ͺ��ļ�ϵͳ,�����ж�д����֮ǰ������д˲��� */
		s = mWaitInterrupt( );  /* �ȴ��жϲ���ȡ״̬ */
		if ( s != USB_INT_SUCCESS ) {  /* �е�U��һ�γ�ʼ�����ɹ�,����һ�� */
			mDelaymS( 100 );  /* �������� */
			xWriteCH376Cmd( CMD_DISK_MOUNT );  /* ��ʼ�����̲����Դ����Ƿ���� */
			s = mWaitInterrupt( );  /* �ȴ��жϲ���ȡ״̬ */
		}
		mStopIfError( s );
		xWriteCH376Cmd( CMD_SET_FILE_NAME );  /* ���ý�Ҫ�������ļ����ļ���,ͨ���֧�������ļ�����Ŀ¼ */
		xWriteCH376Data( '/' );
		xWriteCH376Data( '*' );
		xWriteCH376Data( 0 );
		xWriteCH376Cmd( CMD_FILE_OPEN );  /* ö���ļ���Ŀ¼ */
		while ( 1 ) {
			s = mWaitInterrupt( );
			if ( s == USB_INT_DISK_READ ) {  /* �������ݶ��� */
				xWriteCH376Cmd( CMD01_RD_USB_DATA0 );
				printf( "Name: ");
				xReadCH376Data( );  /* ��������sizeof(FAT_DIR_INFO) */
				for ( s = 0; s != 8+3; s ++ ) printf( "%c", xReadCH376Data( ) );
				printf( "         (%c)\n", xReadCH376Data( )&ATTR_DIRECTORY?'#':'*' );  /* Ŀ¼��ʾ#��׺,�ļ���ʾ*��׺ */
				for ( s = 11; s != sizeof( FAT_DIR_INFO ); s ++ ) xReadCH376Data( );  /* ȡ���������� */
				xWriteCH376Cmd( CMD0H_FILE_ENUM_GO );  /* ����ö���ļ���Ŀ¼ */
			}
			else if ( s == ERR_MISS_FILE ) break;  /* û���ҵ������ƥ���ļ�,�������� */
			else mStopIfError( s );  /* �������� */
		}
		while ( mWaitInterrupt( ) != USB_INT_DISCONNECT );  /* �ȴ�U�̰γ� */
		mDelaymS( 250 );
	}
}