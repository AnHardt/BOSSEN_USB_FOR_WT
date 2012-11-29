
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
    UINT8	res;
    UINT8	s;
    UINT8	NameBuf[20] = {0};
    
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR_bit.P1DIR0 = 1;
    P1OUT_bit.P1OUT0 = 1;

    UartInit();
code_start:
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

    strcpy( NameBuf, "\\NEWFILE000.TXT" );  /* Ŀ���ļ��� */
    printf( "Create\n" );
    s = CH376FileCreatePath( NameBuf );  /* �½��༶Ŀ¼�µ��ļ�,֧�ֶ༶Ŀ¼·��,���뻺����������RAM�� */
    mStopIfError( s );
    
    printf( "Write\n" );
    strcpy( buf, "�Ҳ���/C51/CH376HFT.C�ļ�\xd\n" );
    s = CH376ByteWrite( buf, strlen(buf), NULL );  /* ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */
    mStopIfError( s );
    
    printf( "Close\n" );
    s = CH376FileClose( TRUE );  /* �ر��ļ�,�����ֽڶ�д�����Զ������ļ����� */
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
