;/* 2008.10.18
;****************************************
;**  Copyright  (C)  W.ch  1999-2009   **
;**  Web:  http://www.winchiphead.com  **
;****************************************
;**  USB Host File Interface for CH376 **
;**  TC2.0@PC, KC7.0@MCS51             **
;****************************************
;*/
;/* CH376 �����ļ�ϵͳ�ӿ� */

;/* MCS-51��Ƭ��ASM���Ե�U���ļ���дʾ������,֧��89C2051,89C51,89C52�ȵ�Ƭ�� */
;/* ��������ʾ�ֽڶ�д,���ڽ�ADCģ���ɼ����������ӵ�U�̻���SD���ļ�MY_ADC.TXT��,
;   ����ļ�������ô���������ӵ��ļ�ĩβ,����ļ���������ô�½��ļ����������� */
; 
; /* A51   CH376HFT.ASM */
; /* L51   CH376HFT.OBJ */
; /* OHX51 CH376HFT */
;

; ����89C2051��û�в������ߵĵ�Ƭ��,����ѡ������ģ�Ⲣ��,Ӳ��SPI��������ģ��SPI,�첽���ڵ�Ӳ��ͨѶ��ʽ,C��������Щ����
CH376_CMD_PORT			EQU		0BDF1H		; CH376����˿ڵ�I/O��ַ
CH376_DAT_PORT			EQU		0BCF0H		; CH376���ݶ˿ڵ�I/O��ַ

$INCLUDE		(..\CH376INC.INC)			; ASMͷ�ļ�,���ö���

LED_OUT					EQU		P1.4		; ����״ָ̬ʾ���

; Ӧ�ó���ζ���
MY_CODE				SEGMENT		CODE
MY_DATA				SEGMENT		DATA

; ��λ���ж�����
					CSEG	AT	0000H
					LJMP	ASM_MAIN		; ��Ƭ����λ������������
;					CSEG	AT	0003H		; INT0�ж�����
;					LJMP    InterruptHandle	; CH376���жϷ������,���ʹ��"�жϷ�ʽ"��������ж������޸�����

; Ӧ�ó������õ��ĳ���,ֻ�����С,��ָ����ַ,�����ӳ����Զ������ַ
					RSEG	MY_CODE
FILE_NAME:			DB	'\MY_ADC.TXT',00H
STR_WRITE_1:		DB	'This is first string,\xd\xa',00H
STR_WRITE_2:		DB	'Second string ����!\xd\xa',00H

; Ӧ�ó������õ��ı���,ֻ�����С,��ָ����ַ,�����ӳ����Զ������ַ
					RSEG	MY_DATA
MY_BUFFER:			DS	64

; Ӧ�ó������,��ָ����ַ,�����ӳ����Զ������ַ
					RSEG	MY_CODE
;
; ��ʱn΢��,����ȷ,24MHz��Ƶ
; ����: A ��ʱ΢����
; ʹ��: A, R7
mDelayuS:			MOV		R7,A
mDelayuS_loop:		DJNZ	R7,mDelayuS_loop
					RET
;
; ��ʱn����,����ȷ,24MHz��Ƶ
; ����: A ��ʱ������
; ʹ��: A, R7
mDelaymS:			MOV		R7,#0FAH
mDelaymS_loop:		NOP
					NOP
					NOP
					NOP
					NOP
					NOP
					DJNZ	R7,mDelaymS_loop
					DEC     A
					JNZ     mDelaymS
					RET
;
; ��CH376д����
; ����: A ����
; ʹ��: A, DPTR
xWriteCH376Cmd:		MOV		DPTR,#CH376_CMD_PORT	;����˿�
					MOVX	@DPTR,A
					NOP								;��ʱȷ����д���ڴ���1.5uS
					RET
; ��CH376д����
; ����: A ����
; ʹ��: A, DPTR
xWriteCH376Data:	MOV		DPTR,#CH376_DAT_PORT
					MOVX	@DPTR,A
					RET
; ��CH376������
; ���: A ����
; ʹ��: A, DPTR
xReadCH376Data:		MOV		DPTR,#CH376_DAT_PORT
					MOVX	A,@DPTR
					RET
;
; ��ѯCH376�ж�(INT#�͵�ƽ)
; ���: NC ���ж�, CY ���ж�
; ʹ��: A, DPTR
Query376Interrupt:	MOV		DPTR,#CH376_CMD_PORT	;״̬�˿�
					MOVX	A,@DPTR
					RLC		A
					RET
;
; ��ʼ��CH376ΪUSB��������ģʽ
; ���: NC �ɹ�, CY ����ʧ��
; ʹ��: A, DPTR, R7
mInitCH376Host:		MOV		A,#CMD11_SET_USB_MODE
					LCALL	xWriteCH376Cmd
					MOV		A,#06H					;03H����SD��ģʽ
					LCALL	xWriteCH376Data
					MOV		A,#20
					LCALL	xReadCH376Data
					SETB	C
					XRL		A,#CMD_RET_SUCCESS
					JNZ		mInitCH376Host0
					CLR		C
mInitCH376Host0:	RET
;
; ���ڲ���������ȡ���ݿ�
; ����: R0 ָ���ڲ�RAM������,��������
; ���: R7 ���ݿ鳤��
; ʹ��: A, DPTR, R0, R6, R7
CH376ReadBlock:		MOV		A,#CMD01_RD_USB_DATA0
					LCALL	xWriteCH376Cmd
					LCALL	xReadCH376Data			;����
					MOV		R7,A
					JZ		CH376ReadBlock0			;0����
					MOV		R6,A
CH376ReadBlock1:	LCALL	xReadCH376Data
					MOV		@R0,A
					INC		R0
					DJNZ	R6,CH376ReadBlock1
CH376ReadBlock0:	RET
;
; ���ڲ�ָ��������д����������ݿ�
; ����: R0 ָ���ڲ�RAM������,��д����
; ���: R7 ���ݿ鳤��
; ʹ��: A, DPTR, R0, R6, R7
CH376WriteReqBlock:	MOV		A,#CMD01_WR_REQ_DATA
					LCALL	xWriteCH376Cmd
					LCALL	xReadCH376Data			;����
					MOV		R7,A
					JZ		CH376WriteReqBlk0		;0����
					MOV		R6,A
CH376WriteReqBlk1:	MOV		A,@R0
					INC		R0
					LCALL	xWriteCH376Data
					DJNZ	R6,CH376WriteReqBlk1
CH376WriteReqBlk0:	RET
;
; ���ý�Ҫ�������ļ����ļ���
; ����: DPTR ָ�����ROM�е��ļ����ַ���,��0����
; ʹ��: A, DPTR
CH376SetFileName:	PUSH	DPL
					PUSH	DPH
					MOV		A,#CMD10_SET_FILE_NAME
					LCALL	xWriteCH376Cmd
					POP		DPH
					POP		DPL
CH376SetFileName1:	CLR		A
					MOVC	A,@A+DPTR
					INC		DPTR
					PUSH	DPL
					PUSH	DPH
					LCALL	xWriteCH376Data
					POP		DPH
					POP		DPL
					JNZ		CH376SetFileName1
					RET
;
; ��ȡ�ж�״̬��ȡ���ж�����
; ���: A �ж�״̬��
; ʹ��: A, DPTR
CH376GetIntStatus:	MOV		A,#CMD01_GET_STATUS
					LCALL	xWriteCH376Cmd
					LCALL	xReadCH376Data
					RET
;
; �ȴ�CH376�ж�(INT#�͵�ƽ)�������ж�״̬��
; ���: A �ж�״̬��, NC �����ɹ�(�ж�״̬����USB_INT_SUCCESS), CY ����ʧ��
; ʹ��: A, DPTR
Wait376Interrupt:	LCALL	Query376Interrupt
					JC		Wait376Interrupt		;û���ж�
					LCALL	CH376GetIntStatus		;��ȡ�ж�״̬��ȡ���ж�����
					CJNE	A,#USB_INT_SUCCESS,Wait376Interrupt0	;�Ƚ��ж�״̬��
					CLR		C
					RET
Wait376Interrupt0:	SETB	C
					RET
;
; ���U���Ƿ�����,��֧��SD��
; ���: A �ж�״̬��, NC �����ɹ�(�ж�״̬����USB_INT_SUCCESS), CY ����ʧ��
; ʹ��: A, DPTR
CH376DiskConnect:	MOV		A,#CMD0H_DISK_CONNECT
					LCALL	xWriteCH376Cmd
					LJMP	Wait376Interrupt
;
; ��ʼ�����̲����Դ����Ƿ����
; ���: A �ж�״̬��, NC �����ɹ�(�ж�״̬����USB_INT_SUCCESS), CY ����ʧ��
; ʹ��: A, DPTR
CH376DiskMount:		MOV		A,#CMD0H_DISK_MOUNT
					LCALL	xWriteCH376Cmd
					LJMP	Wait376Interrupt
;
; �ڸ�Ŀ¼���ߵ�ǰĿ¼�´��ļ�����Ŀ¼
; ����: DPTR ָ�����ROM�е��ļ����ַ���,��0����
; ���: A �ж�״̬��, NC �����ɹ�(�ж�״̬����USB_INT_SUCCESS), CY ����ʧ��
; ʹ��: A, DPTR
CH376FileOpen:		CLR		A
					MOVC	A,@A+DPTR
					PUSH	ACC
					LCALL	CH376SetFileName		;���ý�Ҫ�������ļ����ļ���
					POP		ACC
					CJNE    A,#DEF_SEPAR_CHAR1,CH376FileOpen1
					SJMP    CH376FileOpen0
CH376FileOpen1:		CJNE    A,#DEF_SEPAR_CHAR2,CH376FileOpen2
CH376FileOpen0:		MOV		A,#CMD50_WRITE_VAR32
					LCALL	xWriteCH376Cmd
					MOV		A,#VAR_CURRENT_CLUST
					LCALL	xWriteCH376Data
					CLR		A
					LCALL	xWriteCH376Data
					CLR		A
					LCALL	xWriteCH376Data
					CLR		A
					LCALL	xWriteCH376Data
					CLR		A
					LCALL	xWriteCH376Data
CH376FileOpen2:		MOV		A,#CMD0H_FILE_OPEN
					LCALL	xWriteCH376Cmd
					LJMP	Wait376Interrupt
;
; �ڸ�Ŀ¼���ߵ�ǰĿ¼���½��ļ�,����ļ��Ѿ�������ô��ɾ��
; ����: DPTR ָ�����ROM�е��ļ����ַ���,��0����
; ���: A �ж�״̬��, NC �����ɹ�(�ж�״̬����USB_INT_SUCCESS), CY ����ʧ��
; ʹ��: A, DPTR
CH376FileCreate:	LCALL	CH376SetFileName		;���ý�Ҫ�������ļ����ļ���
					MOV		A,#CMD0H_FILE_CREATE
					LCALL	xWriteCH376Cmd
					LJMP	Wait376Interrupt
;
; �رյ�ǰ�Ѿ��򿪵��ļ�
; ����: A Ϊ0���ֹ�����ļ�����, ��0�������Զ������ļ�����
; ���: A �ж�״̬��, NC �����ɹ�(�ж�״̬����USB_INT_SUCCESS), CY ����ʧ��
; ʹ��: A, DPTR
CH376FileClose:		PUSH	ACC
					MOV		A,#CMD1H_FILE_CLOSE
					LCALL	xWriteCH376Cmd
					POP		ACC
					LCALL	xWriteCH376Data
					LJMP	Wait376Interrupt
;
; ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ��
; ����: R7/R6/R5/R4 ƫ���ֽ���
; ���: A �ж�״̬��, NC �����ɹ�(�ж�״̬����USB_INT_SUCCESS), CY ����ʧ��
; ʹ��: A, DPTR, R4, R5, R6, R7
CH376ByteLocate:	MOV		A,#CMD4H_BYTE_LOCATE
					LCALL	xWriteCH376Cmd
					MOV		A,R4
					LCALL	xWriteCH376Data
					MOV		A,R5
					LCALL	xWriteCH376Data
					MOV		A,R6
					LCALL	xWriteCH376Data
					MOV		A,R7
					LCALL	xWriteCH376Data
					LJMP	Wait376Interrupt
;
; ���ֽ�Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ�
; ����: R0 ָ���ڲ�RAM������,��������,
;       R7/R6 �����ȡ���ֽ���,��0��65535,R6Ϊ���ֽ�,ʵ����ʹ���ڲ�RAM������ֻ��֧�ּ�ʮ�ֽ�,ʹ���ⲿRAM���������֧�ֵ�65535�ֽ�
; ���: A �ж�״̬��, NC �����ɹ�(�ж�״̬����USB_INT_SUCCESS), CY ����ʧ��,
;       R5/R4 ʵ�ʶ�ȡ���ֽ���,R4Ϊ���ֽ�
; ʹ��: A, DPTR, R0, R4, R5, R6, R7
CH376ByteRead:		MOV		A,#CMD2H_BYTE_READ
					LCALL	xWriteCH376Cmd
					MOV		A,R6
					LCALL	xWriteCH376Data
					MOV		A,R7
					LCALL	xWriteCH376Data
					CLR		A
					MOV		R4,A
					MOV		R5,A
CH376ByteReadLoop:	LCALL	Wait376Interrupt
					JNC		CH376ByteReadEnd		;�����������ҳɹ�
					CJNE	A,#USB_INT_DISK_READ,CH376ByteReadErr
					LCALL	CH376ReadBlock			;���ڲ���������ȡ���ݿ�,������ָ���Զ�����
					MOV		A,R4
					ADD		A,R7
					MOV		R4,A					;�ۼ�ʵ�ʽ��յ��ֽ���
					MOV		A,R5
					ADDC	A,#00H
					MOV		R5,A
					MOV		A,#CMD0H_BYTE_RD_GO
					LCALL	xWriteCH376Cmd
					SJMP    CH376ByteReadLoop		;������
CH376ByteReadErr:	SETB	C
CH376ByteReadEnd:	RET
;
; ���ֽ�Ϊ��λ��ǰλ��д�����ݿ�
; ����: R0 ָ���ڲ�RAM������,��д����,
;       R7/R6 ����д����ֽ���,��0��65535,R6Ϊ���ֽ�,ʵ����ʹ���ڲ�RAM������ֻ��֧�ּ�ʮ�ֽ�,ʹ���ⲿRAM���������֧�ֵ�65535�ֽ�
; ���: A �ж�״̬��, NC �����ɹ�(�ж�״̬����USB_INT_SUCCESS), CY ����ʧ��,
;       R5/R4 ʵ��д����ֽ���,R4Ϊ���ֽ�
; ʹ��: A, DPTR, R0, R4, R5, R6, R7
CH376ByteWrite:		MOV		A,#CMD2H_BYTE_WRITE
					LCALL	xWriteCH376Cmd
					MOV		A,R6
					LCALL	xWriteCH376Data
					MOV		A,R7
					LCALL	xWriteCH376Data
					CLR		A
					MOV		R4,A
					MOV		R5,A
CH376ByteWriteLoop:	LCALL	Wait376Interrupt
					JNC		CH376ByteWriteEnd		;�����������ҳɹ�
					CJNE	A,#USB_INT_DISK_WRITE,CH376ByteWriteErr
					LCALL	CH376WriteReqBlock		;���ڲ�ָ��������д����������ݿ�,������ָ���Զ�����
					MOV		A,R4
					ADD		A,R7
					MOV		R4,A					;�ۼ�ʵ��д����ֽ���
					MOV		A,R5
					ADDC	A,#00H
					MOV		R5,A
					MOV		A,#CMD0H_BYTE_WR_GO
					LCALL	xWriteCH376Cmd
					SJMP    CH376ByteWriteLoop		;����д
CH376ByteWriteErr:	SETB	C
CH376ByteWriteEnd:	RET
;
; ������ROM�ռ���ַ������Ƶ��ڲ�RAM��
; ����: DPTR ָ�����ROM�ռ���ַ���Դ��ַ
;       R0 ָ���ڲ�RAM��Ŀ�ĵ�ַ
; ʹ��: A, DPTR, R0
mCopyStringToIRAM:	CLR		A
					MOVC	A,@A+DPTR
					INC		DPTR
					MOV		@R0,A
					INC		R0
					JNZ		mCopyStringToIRAM
					RET
;
; ����RAM���ַ����ĳ���
; ����: R0 ָ���ڲ�RAM�е��ַ�����ʼ��ַ
; ���: A �ַ����ĳ���
; ʹ��: A, R0
mGetStringLength:	MOV		A,#0FFH
					DEC		R0
mGetStringLength1:	INC		R0
					INC		A
					CJNE	@R0,#00H,mGetStringLength1
					RET
;
; ������״̬,���������ͣ��,ʵ��Ӧ�ó�����Ҫ��������
; ����: A ״̬��
mStopIfError:		JC		ERROR_FOUND			;����
					RET							;�����ɹ��򷵻�
ERROR_FOUND:		CLR		LED_OUT				;LED��˸��ʾ
					MOV		A,#100
					LCALL	mDelaymS
					SETB	LED_OUT
					MOV		A,#100
					LCALL	mDelaymS
					SJMP	ERROR_FOUND
;
;
; Ӧ�ó���������, ������ʾ
ASM_MAIN:			MOV		SP,#0CFH			;��ջ
					CLR		LED_OUT				;������LED��һ����ʾ����
					MOV		A,#100
					LCALL	mDelaymS
					SETB	LED_OUT

					LCALL	mInitCH376Host		;��ʼ��CH376ΪUSB��������ģʽ
					LCALL	mStopIfError

; ��ѭ��, �ȴ�U�̲��벢����, ʵ���ϵ�Ƭ��������������, ����Ҫ��дU��ʱ�ٲ�ѯU��״̬
WAIT_DISK_IN:		LCALL	CH376DiskConnect	;���U���Ƿ�����,��֧��SD��,����SD�������ɵ�Ƭ��ֱ�Ӳ�ѯSD�����Ĳ��״̬����
					JNC		DISK_IN_NOW			;U���Ѿ�����,��������USB�豸�Ѿ�����
					MOV		A,#100
					LCALL	mDelaymS			;��Ƭ��������������,����Ƶ����ѯ
					SJMP	WAIT_DISK_IN
DISK_IN_NOW:		MOV		A,#250
					LCALL	mDelaymS			;��ʱ,��ѡ����,�е�USB�洢����Ҫ��ʮ������߸������ʱ
					CLR  	LED_OUT				;LED��

; ���U���Ƿ�׼����
					MOV		R2,#10
IS_DISK_READY:		LCALL	CH376DiskMount		;��ʼ�����̲����Դ����Ƿ����
					JNC		DISK_READY_OK		;׼������
					MOV		A,#50
					LCALL	mDelaymS
					DJNZ	R2,IS_DISK_READY	;�����ȴ�,�е�U�����Ƿ���δ׼����,�������Ա�����
DISK_READY_OK:

; ���Դ��ļ�
					MOV		DPTR,#FILE_NAME		;ָ�����ROM�е��ļ����ַ���
					LCALL	CH376FileOpen		;�ڸ�Ŀ¼���ߵ�ǰĿ¼�´��ļ�
					JNC     FILE_OPEN_EXIST		;�ļ��Ѿ�����
					CJNE	A,#ERR_MISS_FILE,FILE_OPEN_ERR
; �ļ����������½��ļ�
					MOV		DPTR,#FILE_NAME		;ָ�����ROM�е��ļ����ַ���
					LCALL	CH376FileCreate		;�ڸ�Ŀ¼���ߵ�ǰĿ¼���½��ļ�
					LCALL	mStopIfError
					SJMP	FILE_OPEN_CREATE
; �ļ��򿪲���ʧ��
FILE_OPEN_ERR:		SETB	C
					LCALL	mStopIfError
; �ļ��Ѿ�����,���ƶ���ǰ�ļ�ָ�뵽�ļ���β���Ա���������
FILE_OPEN_EXIST:

;					MOV		A,#30				;�����ȡ���ֽ���,���ܳ����ڲ��������Ĵ�С
;					MOV		R2,A
;					MOV		R6,A
;					MOV		R7,#00H
;					MOV		R0,#MY_BUFFER		;ָ���ڲ�RAM������,��Ŷ��������ݿ�
;					LCALL	CH376ByteRead		;���ֽ�Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ�
;					LCALL	mStopIfError
;					MOV		A,R4				;ʵ�ʶ�ȡ���ֽ���
;					XRL		A,R2				;�����ȡ���ֽ���
;					JNZ		END_OF_FILE			;ʵ���ֽ�������˵�����ļ�ĩβ��,�ļ�����
;					NOP							;�ļ���δ����,ȡ������

					MOV		R4,#0FFH			;�Ƶ��ļ���β��
					MOV		R5,#0FFH
					MOV		R6,#0FFH
					MOV		R7,#0FFH
					LCALL	CH376ByteLocate		;���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ��
					LCALL	mStopIfError
FILE_OPEN_CREATE:

; ��ʼ���ļ���д������
					MOV		DPTR,#STR_WRITE_1
					MOV		R0,#MY_BUFFER
					LCALL	mCopyStringToIRAM	;������ROM�ռ���ַ������Ƶ��ڲ�RAM��
					MOV		R0,#MY_BUFFER
					LCALL	mGetStringLength	;����RAM���ַ����ĳ���
					MOV		R6,A				;����д����ֽ���
					MOV		R7,#00H
					MOV		R0,#MY_BUFFER		;ָ���ڲ�RAM������
					LCALL	CH376ByteWrite		;���ֽ�Ϊ��λ��ǰλ��д�����ݿ�
					LCALL	mStopIfError
; ��ʼ���ļ���д������,�ڶ���
					MOV		DPTR,#STR_WRITE_2
					MOV		R0,#MY_BUFFER
					LCALL	mCopyStringToIRAM	;������ROM�ռ���ַ������Ƶ��ڲ�RAM��
					MOV		R0,#MY_BUFFER
					LCALL	mGetStringLength	;����RAM���ַ����ĳ���
					MOV		R6,A				;����д����ֽ���
					MOV		R7,#00H
					MOV		R0,#MY_BUFFER		;ָ���ڲ�RAM������
					LCALL	CH376ByteWrite		;���ֽ�Ϊ��λ��ǰλ��д�����ݿ�
					LCALL	mStopIfError
					MOV		A,#01H				;�����Զ������ļ�����
					LCALL   CH376FileClose		;�رյ�ǰ�Ѿ��򿪵��ļ�
					LCALL	mStopIfError

; ��ʾ�������,�ȴ�U�̰γ�
					SETB 	LED_OUT				; LED��
WAIT_DISK_OUT:		LCALL	CH376DiskConnect	;���U���Ƿ�����,�ȴ�U�̰γ�,����SD�������ɵ�Ƭ��ֱ�Ӳ�ѯSD�����Ĳ��״̬����
					JC		DISK_OUT_NOW		;U���Ѿ��Ͽ�
					MOV		A,#100
					LCALL	mDelaymS			;��Ƭ��������������,����Ƶ����ѯ
					SJMP	WAIT_DISK_OUT

DISK_OUT_NOW:		MOV		A,#200
					LCALL	mDelaymS
					LJMP	WAIT_DISK_IN		;��ѭ��,������һ��U��
;
END