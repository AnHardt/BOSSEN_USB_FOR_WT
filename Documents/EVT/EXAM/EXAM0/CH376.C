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

/* CH376��������ʾ����: ��ʾUSB-HOST�����ӿں�USB-DEVICE�豸�ӿڵ�Ӧ�� */

/* ���ڱ������е�CH376�����ӿ�: HOST.C
       ��������U��, ֧��U���ļ�ϵͳFAT12/FAT16/FAT32, ��������,
       ����U�̺�, �ó���U���е�/C51/CH376HFT.C�ļ��е�ǰ200���ַ���ʾ����,
       ����Ҳ���ԭ�ļ�CH376HFT.C, ��ô�ó�����ʾC51��Ŀ¼��������CH376��ͷ���ļ���,
       ����Ҳ���C51��Ŀ¼, ��ô�ó�����ʾ��Ŀ¼�µ������ļ���,
       ������˿���ͨ�����ڼ��/���Թ���������9600bps�鿴��ʾ���, Ҳ����ʹ��CH341�Ĵ��ڹ��߻���ģ�����ʾ���� */
/* ���ڱ������е�CH376�豸�ӿ�: DEVICE.C
       ��������+Ӧ��ģʽͨѶ�ṹ, ǿ���ɿ��Ժͽ�����, ��׷�����ٶ�,
       ������˿���ͨ��CH372/CH375/CH376�ĵ��Թ����е�MCS51��ع��߳���CH37XDBG.EXEʵ�ֶ�MCS51��Ƭ����"��ȫ"����,
       ���Զ�дMCS51��Ƭ���������ⲿRAM���ڲ�RAM�Լ��������SFR, ��ȻҲ�ܹ���������ͨѶ */
/* ���������л�:
       ������Ĭ�Ϲ�����USB-HOST������ʽ, ����USB�豸����ʱ�Զ�����, ��Ҫ��ΪUSB�豸������ͨѶʱ, ���԰��������ϵİ�ť������������л� */

/* C51   CH376.C */
/* C51   HOST.C */
/* C51   DEVICE.C */
/* LX51  CH376.OBJ, HOST.OBJ, DEVICE.OBJ */
/* OHX51 CH376 */


#include "CH376.H"

UINT8	IsKeyPress( )
{
	if ( USER_KEY_IN == 0 ) {  /* �м����� */
		LED_OUT_INACT( );  /* LED�� */
		mDelaymS( 50 );
		if ( USER_KEY_IN == 0 ) {
			while ( USER_KEY_IN == 0 );  /* �ȴ������ͷ� */
			mDelaymS( 50 );
			while ( USER_KEY_IN == 0 );  /* ����ȥ���� */
			LED_OUT_ACT( );  /* LED����ʾ���� */
			return( 1 );
		}
		LED_OUT_ACT( );  /* LED����ʾ���� */
	}
	return( 0 );
}

main( ) {
	LED_OUT_INIT( );
	LED_OUT_ACT( );  /* ������LED��˸һ����ʾ���� */
	mDelaymS( 100 );  /* ��ʱ100���� */
	LED_OUT_INACT( );
	mDelaymS( 100 );

	mInitSTDIO( );  /* Ϊ���ü����ͨ�����ڼ����ʾ���� */
	printf( "Start CH376 demo ...\n" );

	EA = 1;
	LED_OUT_ACT( );  /* LED����ʾ���� */
	while ( 1 ) {  /* �û���������USB����ģʽ�����л� */
		LED_HOST( );
		printf( "Set USB host mode\n" );
		host( );
		LED_DEVICE( );
		printf( "Set USB device mode\n" );
		device( );
	}
}