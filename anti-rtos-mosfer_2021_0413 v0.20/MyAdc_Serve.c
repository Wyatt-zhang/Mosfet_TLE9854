
#include "tle_device.h"	
#include "Motor_Parameter.h"
#include "MyAdc_Serve.h"

/*
底层ADC采样的处理
*/

ADCGet StADCValue={KEY_IDLE,0,0};

//暂未使用
void AdcTempMonitor(void){
	
	//BDRV的温度
	StADCValue.TemperatureBDRV =  ADC2_GetChResult_C(ADC2_TEMP1);
	//芯片中心温度
	StADCValue.TemperatureChip = ADC2_GetChResult_C(ADC2_TEMP2);	
}

/*
 
****实时获取按键ADC的数值,判断哪个按键按下
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
    //自动按键的激活--下或者上某个按键先激活，再另外一个
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
	
	//把现在的key的逻辑值更新
	StADCValue.KeyStatus = KeyStatus;
	
	return KeyStatus;
}
