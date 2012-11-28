/* CH376оƬ Ӳ������� V1.0 */
/* �ṩI/O�ӿ��ӳ��� */

#include	"CH376INC.H"

#ifndef	__CH376_HAL_H__
#define __CH376_HAL_H__


/* ���ӵ�USB����״̬���� */
#define		ERR_USB_UNKNOWN		0xFA	/* δ֪����,��Ӧ�÷��������,����Ӳ�����߳������ */
//#define		DEF_INT_TIMEOUT         (30000)
/* ��ʱָ��΢��ʱ��,���ݵ�Ƭ����Ƶ����,����ȷ */
void	mDelayuS( unsigned int x );

/* ��ʱָ������ʱ��,���ݵ�Ƭ����Ƶ����,����ȷ */
void	mDelaymS( unsigned int x );

void	CH376_PORT_INIT( void );  		/* CH376ͨѶ�ӿڳ�ʼ�� */

void	xEndCH376Cmd( void );			/* ����CH376����,������SPI�ӿڷ�ʽ */

void	xWriteCH376Cmd( UINT8 command );	/* ��CH376д���� */

void	xWriteCH376Data( UINT8 temp );	/* ��CH376д���� */

UINT8	xReadCH376Data( void );			/* ��CH376������ */

UINT8	Query376Interrupt( void );		/* ��ѯCH376�ж�(INT#����Ϊ�͵�ƽ) */

UINT8	mInitCH376Host( void );			/* ��ʼ��CH376 */

#endif