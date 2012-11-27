/* CH376оƬ Ӳ����׼8λ�����������ӵ�Ӳ������� V1.0 */
/* �ṩI/O�ӿ��ӳ��� */

#include	"HAL.H"

/* �����е�Ӳ�����ӷ�ʽ����(ʵ��Ӧ�õ�·���Բ����޸��������弰�ӳ���) */
/* ��Ƭ��������    CH376оƬ������
      P2.0                 A0
      P2.6                 CS#    ���������ֻ��CH376,��ôCS#����ֱ�ӽӵ͵�ƽ,ǿ��Ƭѡ */

UINT8V	xdata	CH376_CMD_PORT	_at_ 0xBDF1;	/* �ٶ�CH376����˿ڵ�I/O��ַ */
UINT8V	xdata	CH376_DAT_PORT	_at_ 0xBCF0;	/* �ٶ�CH376���ݶ˿ڵ�I/O��ַ */

#define CH376_INT_WIRE			INT0	/* �ٶ�CH376��INT#����,���δ������ôҲ����ͨ����ѯ״̬�˿�ʵ�� */

void	CH376_PORT_INIT( void )  /* ����ʹ�ñ�׼���ڶ�дʱ��,���������ʼ�� */
{
}

//void	mDelay0_5uS( void )  /* ������ʱ0.5uS,���ݵ�Ƭ����Ƶ���� */
//{
//}

#define	xEndCH376Cmd( )  /* ����CH376����,������SPI�ӿڷ�ʽ */

#define	xReadCH376Status( )		( CH376_CMD_PORT )  /* ��CH376��״̬,�����ڲ��ڷ�ʽ */

void	xWriteCH376Cmd( UINT8 mCmd )  /* ��CH376д���� */
{
	UINT8	i;
	CH376_CMD_PORT = mCmd;
/*	mDelay0_5uS( ); mDelay0_5uS( ); mDelay0_5uS( );*/  /* ��ʱ1.5uSȷ����д���ڴ���1.5uS,���������漸�е�״̬��ѯ���� */
	for ( i = 10; i != 0; -- i ) {  /* ״̬��ѯ,�ȴ�CH376��æ,��������һ�е���ʱ1.5uS���� */
		if ( ( xReadCH376Status( ) & PARA_STATE_BUSY ) == 0 ) break;  /* ���״̬�˿ڵ�æ��־λ */
	}
}

#ifdef	FOR_LOW_SPEED_MCU  /* ����Ҫ��ʱ */
#define	xWriteCH376Data( d )	{ CH376_DAT_PORT = d; }  /* ��CH376д���� */
#define	xReadCH376Data( )		( CH376_DAT_PORT )  /* ��CH376������ */
#else
void	xWriteCH376Data( UINT8 mData )  /* ��CH376д���� */
{
	CH376_DAT_PORT = mData;
//	mDelay0_5uS( );  /* ȷ����д���ڴ���0.6uS */
}
UINT8	xReadCH376Data( void )  /* ��CH376������ */
{
//	mDelay0_5uS( );  /* ȷ����д���ڴ���0.6uS */
	return( CH376_DAT_PORT );
}
#endif

/* ��ѯCH376�ж�(INT#�͵�ƽ) */
UINT8	Query376Interrupt( void )
{
#ifdef	CH376_INT_WIRE
	return( CH376_INT_WIRE ? FALSE : TRUE );  /* ���������CH376���ж�������ֱ�Ӳ�ѯ�ж����� */
#else
	return( xReadCH376Status( ) & PARA_STATE_INTB ? FALSE : TRUE );  /* ���δ����CH376���ж��������ѯ״̬�˿� */
#endif
}

UINT8	mInitCH376Host( void )  /* ��ʼ��CH376 */
{
	UINT8	res;
	CH376_PORT_INIT( );  /* �ӿ�Ӳ����ʼ�� */
	xWriteCH376Cmd( CMD11_CHECK_EXIST );  /* ���Ե�Ƭ����CH376֮���ͨѶ�ӿ� */
	xWriteCH376Data( 0x65 );
	res = xReadCH376Data( );
//	xEndCH376Cmd( );  // ���ڷ�ʽ����Ҫ
	if ( res != 0x9A ) return( ERR_USB_UNKNOWN );  /* ͨѶ�ӿڲ�����,����ԭ����:�ӿ������쳣,�����豸Ӱ��(Ƭѡ��Ψһ),���ڲ�����,һֱ�ڸ�λ,���񲻹��� */
	xWriteCH376Cmd( CMD11_SET_USB_MODE );  /* �豸USB����ģʽ */
	xWriteCH376Data( 0x06 );
	mDelayuS( 20 );
	res = xReadCH376Data( );
//	xEndCH376Cmd( );  // ���ڷ�ʽ����Ҫ
	if ( res == CMD_RET_SUCCESS ) return( USB_INT_SUCCESS );
	else return( ERR_USB_UNKNOWN );  /* ����ģʽ���� */
}