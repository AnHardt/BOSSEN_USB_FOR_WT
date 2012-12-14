
#include "io430.h"
#include "HAL.h"
#include "FILE_SYS.H"

#include <string.h>
#include <stdio.h>

#ifndef NULL
#define NULL (void *)0
#endif




UINT8		buf[64];

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
int putchar( int x )
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
/* ����:�о�ָ����ŵ�Ŀ¼�µ������ļ� */

int main( void )
{
    int i;
    int j;
    UINT8	res;
    UINT8	s;
    UINT8	NameBuf[20] = {0};
    UINT8       CountT = 0;
    UINT32      U_D;
    PUINT32     pU_D;
    pU_D = &U_D;
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR_bit.P1DIR0 = 1;
    P1OUT_bit.P1OUT0 = 1;

    UartInit();
code_start:
    CountT ++;
    for(i = 0;i<30000;i++);
    printk("Code Start !\r\n");
    printk("����ʼ !\r\n");
    
    do{
        for(i = 0;i<30000;i++);
        res = mInitCH376Host();
    }while(res != USB_INT_SUCCESS);
    printk("USB_INT_SUCCESS !\r\n");
    
    do{
        for(i = 0;i<30000;i++);
        res = CH376DiskConnect( ); /* ��ѯU���Ƿ����ӣ�����USB_INT_SUCCESS��˵����ǰ������ */ 
    }while(res!=USB_INT_SUCCESS);
    printk("  Connect SUCCESS\r\n");
    
    do{
        for(i = 0;i<30000;i++);
        res = CH376DiskMount( ); /* ��ѯU�̻�SD���Ƿ�׼���ã���ЩU�̿������ε��ò��ܳɹ� */ 
    }while(res!=USB_INT_SUCCESS);
    printk("  U is OK !\r\n");

    s = CH376DiskCapacity(pU_D);
    mStopIfError( s );
    printk("  U�̴�С:");
    printHex((unsigned int)U_D);
    printHex((unsigned int)(U_D>>16));
    printk("\r\n");
    
    s = CH376DiskQuery(pU_D);
    mStopIfError( s );
    printk("  ʣ���С:");
    printHex((unsigned int)U_D);
    printHex((unsigned int)(U_D>>16));
    printk("\r\n");
    strcpy( NameBuf, "\\2012.TXT" );  /* Ŀ���ļ��� */
    
#if 0
    
    printf( "Open\r\n" );
    s = CH376FileOpenPath( NameBuf );
    mStopIfError( s );
    if ( s == ERR_MISS_FILE ){
        printf( "Create\r\n" );
        s = CH376FileCreatePath( NameBuf );  /* �½��༶Ŀ¼�µ��ļ�,֧�ֶ༶Ŀ¼·��,���뻺����������RAM�� */
        mStopIfError( s );
    }
    
    printf( "CH376ByteLocate\r\n" );
    s = CH376ByteLocate(0xFFFFFFFF);
    mStopIfError( s );
    
    printf( "Write\r\n" );
    strcpy( buf, "ʱ��        ����  ---\xd\n" );
    s = CH376ByteWrite( buf, strlen(buf), NULL );  /* ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */
    mStopIfError( s );
    
    strcpy( buf, "2012-12-01  01    ---\xd\n" );
    buf[9] = '0' + CountT;
    
    for(i = 0; i < 100;i ++){
        buf[12] = '0' + i/10;
        buf[13] = '0' + i%10;
        printf( "Write %s" ,buf);
        s = CH376ByteWrite( buf, strlen(buf), NULL );  /* ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */
        mStopIfError( s );            
    }
    
    printf( "Close\r\n" );
    s = CH376FileClose( TRUE );  /* �ر��ļ�,�����ֽڶ�д�����Զ������ļ����� */
    mStopIfError( s );
#endif
/* ���MY_ADC.TXT�ļ��Ѿ�������������ݵ�β��,������������½��ļ� */
        printf( "Open\n" );
        s = CH376FileOpen( NameBuf );  /* ���ļ�,���ļ��ڸ�Ŀ¼�� */
        if ( s == USB_INT_SUCCESS ) {  /* �ļ����ڲ����Ѿ�����,�ƶ��ļ�ָ�뵽β���Ա�������� */
                printf( "File size = %ld\n", CH376GetFileSize( ) );  /* ��ȡ��ǰ�ļ����� */
                printf( "Locate tail\n" );
                s = CH376ByteLocate( 0xFFFFFFFF );  /* �Ƶ��ļ���β�� */
                mStopIfError( s );
        }
        else if ( s == ERR_MISS_FILE ) {  /* û���ҵ��ļ�,�����½��ļ� */
                printf( "Create\n" );
                s = CH376FileCreate( NULL );  /* �½��ļ�����,����ļ��Ѿ���������ɾ�������½�,�������ṩ�ļ���,�ղ��Ѿ��ṩ��CH376FileOpen */
                mStopIfError( s );
        }
        else mStopIfError( s );  /* ���ļ�ʱ���� */
        printf( "Write begin\n" );
        s = sprintf( buf, "��ǰ�ļ�����= %ld �ֽ�\xd\xa", CH376GetFileSize( ) );  /* ע���ַ������Ȳ������buf,����Ӵ󻺳������߷ֶ��д�� */
        s = CH376ByteWrite( buf, s, NULL );  /* ���ֽ�Ϊ��λ���ļ�д������ */
        mStopIfError( s );
        printf( "Write ADC data\n" );
        printf( "Current offset ( file point ) is :        ");
        for(i = 0;i<1000;i++){
            s = sprintf( buf, "%02d.%02d.%02d.%d\xd\xa", 2012 + i/365, 1 + (i / 30) % 12, 1 + i % 30, i );  
            /* �����������ݸ�ʽΪһ���ַ��� */
            s = CH376ByteWrite( buf, s, NULL );  /* ���ֽ�Ϊ��λ���ļ�д������ */
            /* ��ЩU�̿��ܻ�Ҫ����д���ݺ�ȴ�һ����ܼ�������,
            ����,�����ĳЩU���з������ݶ�ʧ����,
            ������ÿ��д�����ݺ�������ʱ�ټ��� */
            for(j = 0;j<30;j++);
            mStopIfError( s );
            printf( "\b\b\b\b\b\b" );
            printf( "%6ld", CH376ReadVar32( VAR_CURRENT_OFFSET ) );  
            /* ��ȡ��ǰ�ļ�ָ�� */
        }
        
        printf( "Write end\n" );
        strcpy( buf, "�����ADC���ݵ��˽���\xd\xa" );
        s = CH376ByteWrite( buf, strlen( buf ), NULL );  /* ���ֽ�Ϊ��λ���ļ�д������ */
        mStopIfError( s );
/* ���ʵ�ʲ�Ʒ����ʵʱʱ��,���Ը�����Ҫ���ļ������ں�ʱ���޸�Ϊʵ��ֵ,�ο�EXAM10��CH376DirInfoRead/CH376DirInfoSaveʵ�� */
        printf( "Close\n" );
        s = CH376FileClose( TRUE );  /* �ر��ļ�,�Զ������ļ�����,���ֽ�Ϊ��λд�ļ�,�����ó����ر��ļ��Ա��Զ������ļ����� */
        mStopIfError( s );

        
    do{
        for(i = 0;i<30000;i++);
        P1OUT_bit.P1OUT0 = 1;
        for(i = 0;i<30000;i++);
        P1OUT_bit.P1OUT0 = 0;            
        res = CH376DiskConnect( ); /* ��ѯU���Ƿ����ӣ�����USB_INT_SUCCESS��˵����ǰ������ */ 
        
    }while(res!=ERR_DISK_DISCON);
    printk("  ERR_DISK_DISCON\r\n");
    goto code_start;

}
