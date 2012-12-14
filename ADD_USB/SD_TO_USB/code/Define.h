/*============================================ ͷ�ļ�˵�� ============================================================
ȫ�ֱ�������
================================================ END ===============================================================*/

////////////////////////////////////////////// END ////////////////////////////////////////////////////////



#define         uchar     unsigned char
#define 	uint 	  unsigned int

#define		LED1ON	  P1OUT |= BIT4
#define		LED1OFF	  P1OUT &=~ BIT4
#define         LED1_Flicker  P1OUT ^= BIT4
/*
#define		A0_H	  P1OUT |= BIT0
#define		A0_L	  P1OUT &=~ BIT0
#define		A1_H	  P1OUT |= BIT1
#define		A1_L	  P1OUT &=~ BIT1
#define		A2_H	  P1OUT |= BIT2
#define		A2_L	  P1OUT &=~ BIT2
#define		A3_H	  P1OUT |= BIT3
#define		A3_L	  P1OUT &=~ BIT3
*/

//*����ѡ���������á�
/*
#define		FeatureSelection1_H	  P1OUT |= BIT2
#define		FeatureSelection1_L	  P1OUT &=~ BIT2
#define		FeatureSelection0_H	  P1OUT |= BIT3
#define		FeatureSelection0_L	  P1OUT &=~ BIT3
*/
#define		FeatureSelection1_H	  P1OUT |= BIT3
#define		FeatureSelection1_L	  P1OUT &=~ BIT3
#define		FeatureSelection0_H	  P1OUT |= BIT2
#define		FeatureSelection0_L	  P1OUT &=~ BIT2
//*/
#define		P15_H	  P1OUT |= BIT5
#define		P15_L	  P1OUT &=~ BIT5
#define		P16_H	  P1OUT |= BIT6
#define		P16_L	  P1OUT &=~ BIT6
#define         P15_Flicker   P1OUT ^= BIT5
#define         P32_Flicker   P3OUT ^= BIT2
#define         P33_Flicker   P3OUT ^= BIT3
//#define         P16_Flicker   P1OUT ^= BIT6
#define         WorkOnControl_H   P1OUT &=~ BIT6
#define         WorkOnControl_L   P1OUT |= BIT6

#define		FrequencyPointSelection1_H	  P5OUT |= BIT5
#define		FrequencyPointSelection1_L	  P5OUT &=~ BIT5
#define		FrequencyPointSelection0_H	  P5OUT |= BIT6
#define		FrequencyPointSelection0_L	  P5OUT &=~ BIT6

#define         AVR_1_H     P5OUT |= BIT5
#define         AVR_1_L     P5OUT &=~ BIT5
#define         AVR_2_H     P5OUT |= BIT6
#define         AVR_2_L     P5OUT &=~ BIT6

#define         QIANYABAOHU         P6OUT &=~ BIT7
#define         QIANYABAOHU_Normal  P6OUT |= BIT7   //  Ƿѹ��������

/*
#define         GUOLIU              P6OUT &=~ BIT6
#define         GUOLIU_Normal       P6OUT |= BIT6   //  ������������
*/
#define         GUOLIU              P6OUT |= BIT6
#define         GUOLIU_Normal       P6OUT &=~ BIT6   //  ������������
uchar           GUOLIU_Flag = 0;  //  ���������ı�ʶ��0�������� 1��������
//////////////////////////////////////////////////////////////////////////////////////////////

uchar           MCU_Start_flag      =     0;//��Ƭ��������־

///////////////////////////////////////////////   ��ʱ��A   /////////////////////////////////////////////////////////
uint            AcquisitionTime     =       0;      //  ���ɼ���������ʾ�ļ�ʱ
uint            WorkOnTime          =       0;      //  "������"�Ļ�����ʾ��ʱ
uint 		time	            =       0;  //�жϴ�������
uchar 		second	            =	    0;  // �� �ļ���
uint		transmit_count      =       0;  //  Ƶ�ʷ�������ʱ
uchar           WorkOn_Transmit     =       0;  //  ��ѹ"������"��,��Ƶʱ�����
uchar           keylong_flag        =       0;  //  ��������־
#define		keylongtime    600

////////////////////////////////////////////////   END   ////////////////////////////////////////////////////////////

/////////////////////////////////////////////// ����ʽ���� ////////////////////////////////////////////////////////
uchar	keyboard_value	        =	0; 	//�洢����ֵ����ʾ�ڼ�������
uchar	key_save		=	0;	//
uchar	keyon			=	0;	//����һ�����ڣ���ֵ��Ϊ1
uint   	keytime			=	0;	//���̰�����ʱ
uint   	keytime_save	        =	0;	//���̰�����ʱ�洢
uchar   keytime_start	        =	0;	//������ʱ��ʼ��־��0��ֹͣ��1����ʼ   
uchar	Rst_flag		=	0;	//����λ��������0-δ���£�1-����
uchar	ZengYi_flag		=	0;	//�����桰������0-δ���£�1-���£����ң����³�����ص����������⣬�ñ�����Ϊ0
char	ZengYi_disp		=	0;	//���棬������ֵ
uchar	Setting_flag	        =	0;	//���� ���á�0:δ���£�1������1/2AB��2������1/2MN��3������"����ѡ��"����4������"Ƶ��ѡ��"����5������"ʱ������"����6������"���"����
uchar	Position_flag	        =	0;	//���� --���
uint	AB_data			=	60;	//����1/2AB��Ĭ��ֵ0006.000 m  
uchar	AB_shanshuo		=	4;
uchar   AB_shanshuo_cmp         =       4;      //Ϊ��ֹ��Ļ��˸λͬʱ������������ֵ�ĳ�ֵ�� AB_shanshuo һ��
uchar   MN_shanshuo_cmp         =       4;
uint	MN_data			=	40;	//����1/2MN��Ĭ��ֵ0003.000 m
uchar	FeatureSelection_data   =       0;      //����"����ѡ��"��Ĭ��ֵ0000.000
uchar   FrequencyPointSelection_data=0;         //����"Ƶ��ѡ��"��Ĭ��ֵ0000.000��������ֵ��Χ0--3
uchar	TimeWindow_data         =       0;      //  0 1 2 3 
signed char    Position_data[7]={0,0,0,1,0,0,1};//�������������š�����ʾ�ã����Ǵ洢�ĵ��ֵ----ǰ��3����"���"������3����"׮��"
                                                //��������������һ��������ţ�
                                                //����ѡ��==0ʱ��7�����ִ������������ǣ�����š�����0��O���ʮλ��O��Ÿ�λ������0������0��A��ţ� O��ŷ�Χ1-99��A��ŷ�Χ1-3 ��
struct PositionRecord
{
  uchar PositionOu_InFeatureSelection_0;      //���O���������ĸ���������֣��ڹ���ѡ��0ʱ����ʱ�洢ֵ����Χ 1-99
  uchar PositionA_InFeatureSelection_0;       //���A�ڹ���ѡ��0ʱ����ʱ�洢ֵ����Χ 1��2��3.
  uint  PositionOu_InFeatureSelection_1;      //���O���������ĸ���������֣��ڹ���ѡ��1ʱ����ʱ�洢ֵ����Χ 1-999
  uint  PositionA_InFeatureSelection_1;       //���A�ڹ���ѡ��1ʱ����ʱ�洢ֵ����Χ 1-999
  uint  PositionOu_InFeatureSelection_2;
  uint  PositionA_InFeatureSelection_2; 
  uint  PositionOu_InFeatureSelection_3;
  uint  PositionA_InFeatureSelection_3; 
  uchar NumberOfXiangDao;                     //����ţ���Χ 0-9
};
struct PositionRecord PositionRecordRun;      //�˱���Ӧ��ϵͳ�ϵ����г�ʼ����ֵ��
#define Displacement              2           //��������š���������ʾ��˸������λ
#define ResumeRecordForPosition   3           //�ָ��ϴιػ�ʱ�ĵ�ż�¼----��������š�����

uchar	Position_shanshuo       =       3;
uchar	Position_shanshuo_cmp   =       3;
uchar   Setting_up		=	0;
uchar   Setting_down	        =	0;  //�̰�Ϊ1������Ϊ2
uchar   Acquisition_flag        =       0;      //  �ɼ� ��־λ��0��ֹͣ��1����ʼ
uchar   Vol_Calculate_One_Time  =       0;  //  ���ɼ������ߡ���������ʱ����ʾ��ѹֻҪ��һ�βɵ�ֵ
uchar   Cur_Calculate_One_Time  =       0;  //  ����������ʱ����ʾ����ֻҪ��һ�βɵ�ֵ
uchar   WorkOn_flag             =       0;      //  ����������������0��ֹͣ��1����ʼ
uchar   WorkOn_Transmit_STA     =       0;      //  Ƶ�ʷ��俪ʼ��־
uchar   Save_WorkStop_flag      =       0;  //��ѹ���洢����Ҫ��ʹ������ͣ���Ĺ��ܡ�

////////////////////////////////////////////////   END ////////////////////////////////////////////////////////////

///////////////////////////////////////// 12λAD�������� ///////////////////////////////////////////////////
//��Ƭ���ڲ�AD
uint    A2result                =       0;      //  �洢 A2ͨ��AD��ƽ��ֵ
uint    A4result                =       0;
uint    A0result                =       0; //�ź������� �� 1 ·
uint    A1result                =       0; //�ź������� �� 2 ·



////////////////////////////////////////////////  END //////////////////////////////////////////////////////

///////////////////////////////////////// ��Ļ�������� ////////////////////////////////////////////////////
const uchar disp_data[10][2]={//������ʾ,��������Ļ�м�1��7����ġ�8��
{5,15},	 //--0	 {E+F+G ��A+B+C+D}
{0,6},	 //--1
{3,13},	 //--2
{2,15},	 //--3
{6,6},	 //--4
{6,11},	 //--5
{7,11},	 //--6
{0,14},	 //--7
{7,15},	 //--8
{6,15} 	 //--9
};
const uchar disp_data_addr[7][2]={//	��Ļ��ÿ����8���ĵ�ַ��һ��7��
{1,2},	 //--��1��	{�͵�ַ,�ߵ�ַ}
{3,4},	 //--2
{5,6},	 //--3
{7,8},	 //--4
{19,18}, //--5 {�ߵ�ַ,�͵�ַ}
{17,16}, //--6
{15,14}	 //--7 
};
////////////////////////////////////////////// END ////////////////////////////////////////////////////////

///////////////////////////////////////// �洢���������� //////////////////////////////////////////////////
uchar     Save_Flag       =   0;  //  0��δ��ѹ�����桱������1����ѹ�����桱���� ��
uint      SaveTimeCount   =   0;  //  �洢���洢��ʱ

#define   Parameter       0x30
#define   SaveLength      26

uchar     SaveBuffer[SaveLength]; //  ÿ�ΰ�ѹ���洢�������洢�����ݣ�
#define   Demand_end_flag  0x08 //����洢�Ľ�����־
#define   DemandLength    SaveLength
//uchar     Demand[DemandLength]={Demand_end_flag,};  //  ��ѯ������
struct BufferFlagForDemand  //  ��ѯ
{
  unsigned int  RecordNumber;//"��ѯ"��Ļ�����Զ�Ӧ�ĵڼ�����¼��"��ѯ"������ʶ ����Ϊ 0 ������"��ѯ"����
  unsigned long RecordNumber_Bytes;//�ڼ�����¼����Ӧ���ֽ�����. 1����¼��Ӧ���ֽ�����Ϊ 1*DemandLength��2��Ϊ 2*DemandLength ��
  unsigned int  LastRecordNumber;//�� RecordNumber ����һ�μ�¼�����Դ��ڵ��ڻ���С�� RecordNumber
  unsigned int  OffsetInSectorOfTheFile;//�ļ���ĳ�������е��ֽ���
  unsigned int  OffsetInBuffer_Start_RecordNumber;//ÿ����¼����Ӧ�� ����FAT32_Buffer ���±ꣻ---�ʼ���Ǹ��±�
  unsigned int  OffsetInBuffer_RecordNumber;//ÿ����¼����Ӧ�� ����FAT32_Buffer ���±ꣻ
  unsigned int  TheSecondPartForDemand_Sector;//��Ļ����ʾ�ġ���ѯ��������ռ�õĵڶ���������
  unsigned long TheSecondPartForDemand_Cluster;//
  unsigned int  TheFirstPartForDemand_Sector;//��Ļ����ʾ�ġ���ѯ��������ռ�õĵ�1������
  unsigned long TheFirstPartForDemand_Cluster;//
  //unsigned char TheLastSectorInFile;//�ļ������һ�� ����//�߼�������������������������Χ��0-7
  //unsigned long TheLastClusterInFile;//�ļ������һ�� ��
  //unsigned long BytesAfterTheSector;//���������������������ռ���ֽ�����
  unsigned char NoRecord_flag_InFile;//���ļ���������Ч��¼���հ�ѹ��ѯ����ʱ����ֵΪ0��. 0--��ѯ�ļ���Ч��¼û��ȫ��ɾ����1--ȫ��ɾ��
  unsigned char Demand[ DemandLength ];
};
struct BufferFlagForDemand FatBuffer;
uchar   Delete_flag = 0;  //ɾ��������ʶ----�ڰ��������︳ֵΪ1����ɾ������غ�������0
                          //�κΰ��������Զ�������


uchar     FirstCreatTheFile_flag  = 0;  //  ��һ�δ������ļ�
#define   HeadingLength   34  //  �����е��ַ����������� Heading[] �ĳ���
uchar     Heading[HeadingLength];
////////////////////////////////////////////// END ////////////////////////////////////////////////////////

//////////////////////////////////// �����������롰�ɼ����������� /////////////////////////////////////////
uchar  mmma[8];// �洢����
uchar  mmmm[8];// �����ѹ
////////////////////////////////////////////// END ////////////////////////////////////////////////////////
/*
#define   BIAOXIAO        ( (P1IN&BIT7)&(0x80) )  //
uchar     BIAOXIAO_flag   =   0;  //��У������־λ��0���ް���������1����һ�ΰ��£�2���ڶ��ΰ��£�0�������ΰ���
#define   BIAOXIAO_save        0XBA00  //��У��������ַ��Ҳ�Ǳ������У�ʹ��flash�洢����ʼ��ַ��

#define   CalibrationCurrent_1st  1 //  ���������У����һ����
#define   CalibrationCurrent_2nd  2
#define   CalibrationCurrent_3rd  3
#define   CalibrationCurrent_4th  4
#define   CalibrationVoltage      5 //  �����ѹ��У
#define   Calibration_TheLastFlag 5 //  ��У״̬�����һ����ʶ����� BIAOXIAO_flag ���ڴ�ֵ�����˳���У��

long biaojiao_current  = 0;  //  ��У����ֵ
unsigned long biaojiao_current_staic  = 0;  //  ��У����ֵ,��
uchar     biaojiao_cur_sign = 0;//��У��������
uint      biaojiao_cur_chazhi = 0;//��У�����Ĳ�ֵ---��λ��΢��

signed long deta          =   0;  //  ��ѹ��У�ؾ���ֵ
uchar     memory[64];                  // memory[0]----��ѹ��У��������
                                       // memory[1]----��ѹ��У��ֵ����ֵ������λ��0-99
                                       // memory[2]----��ѹ��У��ֵ����ֵ������λ��0-99
*/
signed long XiuZheng_Result = 0;  //  ���������任��Ľ������AD�ж���õ��������ֵ�־������� void CurrentShow( signed long  current_xiuzheng ) ��ʹ�á�
#define XiuZhengCount   17   //  �����������ֵ��������
uchar   iXiuZhengCount  = 0;//  ÿ����һ�ε�������ֵ����ֵ�� 1
signed long long sum_XiuZheng  = 0;
#define   current    (long)( (((float)(MCU_Ref)*(float)(A4result)*1000.0)/((float)(4095)))/((float)(Current_R)) )  //  ֱ�ӻ���ɵ���


#define ZengYi_MAX  10  //�������༶��,0---9������ֵ��
struct AutoZengYi
{
  unsigned char which_grade_yichu ;//��һ�����
  unsigned char NO1_GAIN;//��һ�����棬�����������Ϊ0������==1
  unsigned char NO2_GAIN;
  unsigned char NO3_GAIN;
  unsigned char loop;//ѭ��
  unsigned char iloop;
  unsigned char ZengYi_Ever_Used ; // 1�������水���ڿ������Ƿ񱻰��£����ޣ���==0 �����£�==1��
                                   // 2�����ڿ���״̬�£�һ����ѹ����λ������ʹ ZengYi_Ever_Used �ػ�0
};
struct AutoZengYi AutoZengYiRun;

/////////////////////////////////////////////////
//