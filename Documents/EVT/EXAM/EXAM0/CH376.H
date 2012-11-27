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

#include <reg52.h>
#include <stdio.h>
#include <string.h>

#include "..\HAL.H"
#include "..\DEBUG.H"

extern	UINT8		idata	buf[64];

#define	USER_KEY_IN				INT1	/* P3.3, INT1, Ĭ��Ϊ�ߵ�ƽ, ���û�������Ϊ�͵�ƽ, �����������ѯ */

#ifdef __C51__
#pragma NOAREGS
#endif

/* ��P1.4����һ��LED���ڼ����ʾ����Ľ���,�͵�ƽLED��,��������ʱ��,����ʱ�� */
sbit P1_4  = P1^4;
#define LED_OUT_INIT( )		{ P1_4 = 1; }	/* P1.4 �ߵ�ƽ */
#define LED_OUT_ACT( )		{ P1_4 = 0; }	/* P1.4 �͵�ƽ����LED��ʾ */
#define LED_OUT_INACT( )	{ P1_4 = 1; }	/* P1.4 �͵�ƽ����LED��ʾ */
sbit P1_5  = P1^5;
/* ��P1.5����һ��LED���ڼ����ʾ����Ľ���,�͵�ƽLED��,��U�̲������ */
#define LED_UDISK_IN( )		{ P1_5 = 0; }	/* P1.5 �͵�ƽ����LED��ʾ */
#define LED_UDISK_OUT( )	{ P1_5 = 1; }	/* P1.5 �͵�ƽ����LED��ʾ */
sbit P1_6  = P1^6;
/* ��P1.6����һ��LED���ڼ����ʾ����Ľ���,�͵�ƽLED��,����U��д����ʱ�� */
#define LED_WR_NOW( )		{ P1_6 = 0; }	/* P1.6 �͵�ƽ����LED��ʾ */
#define LED_NOT_WR( )		{ P1_6 = 1; }	/* P1.6 �͵�ƽ����LED��ʾ */
sbit P1_7  = P1^7;
/* ��P1.7����һ��LED���ڼ�ص�ǰUSBģʽ,��ΪUSB�豸��ʽ,��ΪUSB������ʽ */
#define LED_DEVICE( )		{ P1_7 = 0; }	/* P1.7 �͵�ƽ����LED��ʾ */
#define LED_HOST( )			{ P1_7 = 1; }	/* P1.7 �͵�ƽ����LED��ʾ */

/* �����ӳ��� */
UINT8	IsKeyPress( void );
void	device( void );
void	host( void );