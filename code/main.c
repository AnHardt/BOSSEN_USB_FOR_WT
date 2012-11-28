
#include "io430.h"
#include "HAL.h"
#include "FILE_SYS.H"

#ifndef NULL
#define NULL (void *)0
#endif

void UartInit(void)
{
    P4SEL_bit.P4SEL4 = 1;
    P4SEL_bit.P4SEL5 = 1;
    P4DIR_bit.P4DIR4 = 1;
    P4DIR_bit.P4DIR5 = 0;

    UCA1CTL0 = 0x00;
    UCA1CTL1 = 0x60;
    UCA1BRW = 0x03;
    UCA1MCTL = 0x06;
    UCA1IE = 0x01;
}
int putchar( int x )//ע�ⲻҪ�Ĳ��������ͺͷ���ֵ�����ͣ�����printf�����Ǿ��������ˡ�
{
    while(!UCA1IFG__SPI_bit.UCTXIFG);
    UCA1TXBUF = x;
    return x;
}
volatile unsigned char RxBuffer;
volatile unsigned char FlagRx;
#pragma vector=USCI_A1_VECTOR
__interrupt void UART1RX (void)
{
    RxBuffer = UCA1RXBUF;
    //U0TXBUF = RxBuffer;
    FlagRx = 1;
}
void printk(char *str)
{
    if(str == NULL)
        return;
    while(*str != '\0'){
        putchar(*str++);
    }
}
#if 0
#define IsHexChar(x)  ((((x)>=0)&&((x)<=9)) ? ('0'+(x)) : ('A' - 10 +(x)))
#else
char IsHexChar(unsigned char x)
{
    if( x<=9 )
        return '0' + x;
    else
        return 'A' - 10 + x;
}
#endif
void printHex(unsigned int x)
{
    //unsigned temp;
    printk("0x");
    putchar(IsHexChar((x>>12) & 0xF));
    putchar(IsHexChar((x>> 8) & 0xF));
    putchar(IsHexChar((x>> 4) & 0xF));
    putchar(IsHexChar((x>> 0) & 0xF));
}
void print10(unsigned int x)
{
    putchar('0' + x/10000);
    putchar('0' + x/1000%10);
    putchar('0' + x/100%10);
    putchar('0' + x/10%10);
    putchar('0' + x%10);
}

#define mWaitInterrupt  Wait376Interrupt /* �ȴ�CH376�жϲ���ȡ״̬,�����˵ȴ��������,���ز���״̬ */
void	mStopIfError( UINT8 iErrCode ) {	/* ���������ֹͣ���в���ʾ����״̬,��ʽӦ�û���Ҫ�������� */
	if ( iErrCode == USB_INT_SUCCESS ) return;
	printf( "Error status, %02X\n", (UINT16)iErrCode );
}

int main( void )
{
    int i;
    UINT8	res;
    UINT8	s;
    //UINT8 name[] = "asdf.txt";
    //unsigned char RD_Data;
    
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR_bit.P1DIR0 = 1;
    P1OUT_bit.P1OUT0 = 1;
    //AppUart_init();
    UartInit();

    for(i = 0;i<30000;i++);
    printk("Code Start !\r\n");
    
    
#if 0
    res = mInitCH376Host();
    if(res == USB_INT_SUCCESS)
        printk("USB_INT_SUCCESS !\r\n");
    else
        printk("USB_INT_ERR_USB_UNKNOWN !\r\n");
    
        res = CH376DiskConnect( ); /* ��ѯU���Ƿ����ӣ�����USB_INT_SUCCESS��˵����ǰ������ */ 
        if ( res==USB_INT_SUCCESS ) /* �Ѿ����� */ 
            printk("  Connect SUCCESS\r\n");
        else if ( res==ERR_DISK_DISCON ) /* �Ѿ��Ͽ� */
            printk("  ERR_DISK_DISCON\r\n");
        else
            printk("  ---------------\r\n");
        
        
//��ʼ�������U�̻���SD���Ƿ�׼���ã�׼���ú���ܽ����ļ���д��ʾ���� 
        s=CH376DiskMount( ); /* ��ѯU�̻�SD���Ƿ�׼���ã���ЩU�̿������ε��ò��ܳɹ� */ 
        if ( s!=USB_INT_SUCCESS ) 
            printk("  -- U is not OK !\r\n");/* ��δ׼���� */ 
        else 
            printk("  -- U is OK !\r\n");/* ׼�����ˣ����Զ�д���� */
        
        /* �ڸ�Ŀ¼���ߵ�ǰĿ¼���½��ļ�������ļ��Ѿ���������ɾ�����½� */ 
        CH376FileCreate( "/dBC.txt" );  
        
    CH376FileClose( TRUE );     /* �رյ�ǰ�Ѿ��򿪵��ļ�����Ŀ¼(�ļ���) */ 
    while(1){
        for(i = 0;i<30000;i++);
        P1OUT_bit.P1OUT0 = 1;
        for(i = 0;i<30000;i++);
        P1OUT_bit.P1OUT0 = 0;
    };
#else

	//mDelaymS( 10 );  /* ��ʱ100���� */
    res = mInitCH376Host();
    if(res == USB_INT_SUCCESS)
        printk("USB_INT_SUCCESS !\r\n");
    else
        printk("USB_INT_ERR_USB_UNKNOWN !\r\n");
	while ( 1 ) {
		printk( "Insert USB disk\n" );
		while ( CH376DiskConnect( ) != USB_INT_SUCCESS );  /* �ȴ�U������,SD��ģʽ����Ҫ��Ƭ�����м��SD����� */
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
				printk( "Name: ");
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
#endif
    //return 0;
}
