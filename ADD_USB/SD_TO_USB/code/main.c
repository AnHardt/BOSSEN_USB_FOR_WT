/*********************************************************************************
��Ŀ���ƣ� �編��
���뻷���� IAR 4.20
MCU �ͺţ� MSP430F149
�ⲿ���� 10M
*********************************************************************************/

#include"main.h"
uchar count=0;
/*********************************************************************************
�������ƣ�void timera_0_isr(void)																
�������ܣ���ʱ��TA�жϺ���
˵    ����
*********************************************************************************/
//#pragma interrupt_handler timera_0_isr:TIMERA0_VECTOR
//void timera_0_isr(void)
#pragma vector = TIMERA0_VECTOR           //TA0�жϷ���,�����ο��ȶ�
__interrupt void ta0_isr(void)
{          
         if( (Save_Flag==2)||(Delete_flag==2) )//
         {
            SaveTimeCount++;
            if( SaveTimeCount > Basic_Time )
            {
              SaveTimeCount = 0;
              Save_Flag=0;  // �����ʼ�洢��־
              Delete_flag=0;//��� ɾ�� ��ʶ
              ////////////////////////////////////Ϊ��Ӧ������Ҫ�������洢�����������ˡ�����ͣ���Ĺ��ܡ����洢��ɺ�Save_Flag==2
              /*
              Acquisition_flag = 0;//��ѹ������ͣ�����رղɼ�
              WorkOn_flag      =   0;//
              FatBuffer.RecordNumber = 0;//�ر�"��ѯ"
              HT1621_all_off();
              aStatic_Show();
              */
              Save_WorkStop_flag      =       1;
              //////////////////////////////////////////////////////////////////
            }
         }         
         ////////////////////////////////////////////////////////////////////////////////
         if( Acquisition_flag==1 )
            AcquisitionTime++;
         else
            AcquisitionTime = 0;
       
         if( AcquisitionTime>=(Basic_Time*2+1)  )
         {
           AcquisitionTime=0;
         }
         /////////////////////////////////////////////////////////////////////////////////
         //////////////////////////////////////////////////////////////////////////////
         if( (WorkOn_flag==1)||(FatBuffer.RecordNumber > 0) )
           WorkOnTime++;
         else
           WorkOnTime = 0;
         if( WorkOnTime>=(Basic_Time*3+1) ) WorkOnTime = 0;
         //////////////////////////////////////////////////////////////////////////////
         time++;   //time==120, it is almost one time.  1s //if(time == 120)  	 
	 if(time == 200)	 
  	 {
      	        second++;
		time=0;                 
                
                
                LED1_Flicker; // LED1 ָʾ����˸	

                if( (WorkOn_Transmit_STA==1)&&(WorkOn_flag==1) )
                {//////��������---------ע��һ���򿪱�У�еĵ�����У���˶δ��벻������
                  WorkOn_Transmit++;
                  if( TimeWindow_data==0 )
                  {
                    if( WorkOn_Transmit>10 )//����10�룬ֹͣ����
                    {
                      WorkOn_Transmit = 0;
                      WorkOn_Transmit_STA=0;
                    }
                  }
                  if( TimeWindow_data==1 )
                  {
                    if( WorkOn_Transmit>20 )
                    {
                      WorkOn_Transmit = 0;
                      WorkOn_Transmit_STA=0;
                    }
                  }
                  if( TimeWindow_data==2 )
                  {
                    if( WorkOn_Transmit>30 )
                    {
                      WorkOn_Transmit = 0;
                      WorkOn_Transmit_STA=0;
                    }
                  }
                  if( TimeWindow_data==3 )
                  {
                    if( WorkOn_Transmit>40 )
                    {
                      WorkOn_Transmit = 0;
                      WorkOn_Transmit_STA=0;
                    }
                  }
                }
  	 }
         ///////////////////////////////////////////////////////////////////////////////////	 
         if(keytime_start	==	1) //������ʱ����
	 {
		keytime++;
		keytime_save = keytime;
                
                if( keytime_save>keylongtime )
                {
                  keyon = 0;
                  keylong_flag        =       1;
                  //key_use1();
                }
                
	 }
         //////////////////////////////////////////////////////////////////////////////// 
         
         ////////////////////////////////////////////////////////////////////////////////
	 CCR0 = 10000;	 
}

/********************************************************************************************
�������ƣ�void tb0_isr(void)
�������ܣ���ʱ�� B �ж�
˵    ����
ʱ    �䣺2010-02-27
********************************************************************************************/
#pragma vector = TIMERB0_VECTOR           //TB0�жϷ���,�����ο��ȶ�---ACLK
__interrupt void tb0_isr(void)
{
  
  if( WorkOn_flag==1 )
  {  //Transmitter( FeatureSelection_data ); //  ����Ƶ�� 
    if(count++ >10)
    {
    P15_Flicker;
    P32_Flicker;
    P33_Flicker;
    count =0;
    }
    //P16_Flicker;
  }  
  
}

/********************************************************************************************
�������ƣ�void adc_isr(void)
�������ܣ�A/Dת���жϺ���
˵    ����
ʱ    �䣺2010-02-27
********************************************************************************************/
#define   ADc12max      89                //  ADת���������ֵ�����ڴ�������Ҫ�����͡�ƽ��
unsigned long      sum_2         =     0;          //  �洢 A3 ͨ��ת����ADֵ�����
unsigned long      sum_4         =     0;          //  �洢 A4 ͨ��ת����ADֵ�����
unsigned long      sum_0         =     0; //�ź������� �� 1 ·
unsigned long      sum_1         =     0; //�ź������� �� 2 ·

uchar     ADc12count    =     0;          //  ADת��������������
#define current    (long)( (((float)(MCU_Ref)*(float)(A4result)*1000.0)/((float)(4095)))/((float)(Current_R)) )  //  ֱ�ӻ���ɵ���
#define Current_K   2.1683  //  б��
//#define Current_K   3.7783  //  б��
#define Current_B   6729.8  //  ����
//#define Current_B   26729.8  //  ����



#pragma vector = ADC12_VECTOR             //  ADC12�жϷ���
__interrupt void adc_isr(void)
{  
  ADc12count++;
  
  sum_2 += ADC12MEM0;//��ص�ѹ
  ADC12MEM0 = 0;
  sum_4 += ADC12MEM1;
  ADC12MEM1 = 0;
  sum_0 += ADC12MEM2;
  ADC12MEM2 = 0;
  sum_1 += ADC12MEM3;
  ADC12MEM3 = 0;
  
  if( ADc12count>=ADc12max )
  {
    ADc12count = 0;
    A2result = sum_2/ADc12max;
    A4result = sum_4/ADc12max;
    sum_2 = 0; 
    sum_4 = 0; 
    A0result = sum_0/ADc12max;
    A1result = sum_1/ADc12max;
    sum_0 = 0; 
    sum_1 = 0; 
    /////////////////////////////
    /*///�˲����ǹ�ȥ�ĵ����������У����
    iXiuZhengCount++;    
    sum_XiuZheng  += Current_K * current - Current_B; //i_current_xiuzheng = Current_K * current - Current_B;// ��ֵû�б�У������
    if( iXiuZhengCount >= XiuZhengCount )
    {
      iXiuZhengCount  = 0;
      XiuZheng_Result = sum_XiuZheng/XiuZhengCount;
      sum_XiuZheng = 0;
    }
    */
    CurrentFilter();
  }
}

/*********************************************************************************
�������ƣ�void main(void)																	
�������ܣ�������
˵    ����
*********************************************************************************/
void main(void)
{ 

         InitSys();
	 init_devices();

	 HT1621_all_off();
	 DelayMS(4000);
	 HT1621_all_on();
	 DelayMS(9000);	 
	 Disp_0_9();	 
	 Started();         
         
	 MCU_Start_flag = 1;  //  ��Ƭ������
         QIANYABAOHU_Normal;  //  Ƿѹ�����ţ��Ӳɼ����Դ�ɿع�EA�š���̬�������
         GUOLIU_Normal;       //  ���������ţ���������Դģ��EA�š���̬�������         
         First_Check();
	 FrequencyPointSelection1_L;
         FrequencyPointSelection0_L;
         GainControlFirst();
         FeatureSelection_Port_First( );
         WorkOnControl_H;//���������ƽţ���̬��  �ߡ����������������͡���
         
	 while(1)
	 {            
		  key_use();		  
		  SettingControl();
		  PositionControl();
                  AcquisitionControl();
                  WorkOnControl();
                  BatteryShow();
                  Current_Protect();
                  GainControl();//���ƽ�
                  
                  FeatureSelectionPortSTOP();
                  SaveControl(); 
                  DemandControl();
                  DeleteControl();
                  SaveUseWorkStop( );
	 } 
}