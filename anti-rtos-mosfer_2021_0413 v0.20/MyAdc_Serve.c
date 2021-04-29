
#include "tle_device.h"	
#include "Motor_Parameter.h"
#include "MyAdc_Serve.h"

/*
�ײ�ADC�����Ĵ���
*/

ADCGet StADCValue={KEY_IDLE,0,0};

//��δʹ��
void AdcTempMonitor(void){
	
	//BDRV���¶�
	StADCValue.TemperatureBDRV =  ADC2_GetChResult_C(ADC2_TEMP1);
	//оƬ�����¶�
	StADCValue.TemperatureChip = ADC2_GetChResult_C(ADC2_TEMP2);	
}

/*
 
****ʵʱ��ȡ����ADC����ֵ,�ж��ĸ���������
*/
 uint8 AdcKeyMonitor(void){
	uint8 KeyStatus=KEY_IDLE; // 0000 0x00
	
	uint16 varmon =0;	
	
	//MON1 up key detect
	if( ADC1_GetChResult_mV(&varmon,ADC1_MON1) == true )  //
	{
		#if 1
		//up press down if more than 10V
		if(varmon >= 1000u)
			KeyStatus |= KEY_MANUALUP;//0x01; 0001
		else
			KeyStatus &= 0xFE; ////clear 0001
		#endif
	}
		
	//MON2  down key detect
	if((ADC1_GetChResult_mV(&varmon,ADC1_MON2) == true) )
	{
		#if 1
		if(varmon >=1000u)
			KeyStatus |= KEY_MANUALDOWN; //0010
		else
			KeyStatus &= 0xFD; //clear 0010
		#endif
	}
	
	//auto key is activated
    //�Զ������ļ���--�»�����ĳ�������ȼ��������һ��
	if(KeyStatus==0x03)
	{
		if(StADCValue.KeyStatus==KEY_MANUALUP)
		{
			KeyStatus = KEY_AUTOUP;
		}
		else if(StADCValue.KeyStatus==KEY_MANUALDOWN)
		{
			KeyStatus = KEY_AUTODOWN;
		}
		else
		{
			KeyStatus = StADCValue.KeyStatus;
		}
	}
	else
	{

	}
	
	//�����ڵ�key���߼�ֵ����
	StADCValue.KeyStatus = KeyStatus;
	
	return KeyStatus;
}
