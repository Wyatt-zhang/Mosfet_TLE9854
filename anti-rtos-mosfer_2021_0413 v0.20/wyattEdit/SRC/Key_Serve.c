#include "tle_device.h"	

#include "Motor_Parameter.h"

#include "Key_Serve.h"

#include "Method_Serve.h"

#include "MyAdc_Serve.h"



/* 按键逻辑处理，分为local 按键处理和 lin按键处理 ,优先级 local >lin
待添加lin的
*/

//test for now
extern uint8 SwitchLinCmd;



//调用计数滤波方法
//20*2ms
CalcMethod StKeyFilter = {0,20,KEY_IDLE,KEY_IDLE};


/*
 主要处理 本地local按键的逻辑状态的转换

*/

typedef struct{
    uint8 TempKey;      /*暂时的按键输出逻辑*/

    uint8 KeyComing ;  /*当前有效输入按键*/
    
    uint8 OldKey ; /*上一次的有效输入按键*/
    
    uint8 OutputKey ; /*最终输出的按键逻辑*/

}LocalKey;

LocalKey StKeyLogic = {KEY_IDLE};
   

/*按键逻辑，只响应一次一次有效输入脉冲--有上升沿和下降沿
定义中间态--key_idle为低电平，其它为高电平
*/
static void LocalKeyLogic(uint8 LocalKeyFliter)
{
    
    /***  需添加LIN 开关信号的逻辑： LIN的开关命令最高
    ****
    */
    
    #if 0
    if(SwitchLinCmd!=0)/*有LIN控制命令*/
    {
        StKeyFilter.OutputSignal = SwitchLinCmd;    
    }
    #endif
    
    
    //按键必须经过一次中间态--Key_idle,才更新现在的OutKey,即现在系统的运行动作  
    if( StKeyLogic.OldKey ==KEY_IDLE || LocalKeyFliter ==KEY_IDLE)
    {
        /*输出key 更新到中间态key*/
        StKeyLogic.TempKey = StKeyLogic.OutputKey; 
        
        
        StKeyLogic.KeyComing = LocalKeyFliter;///*这条不注释，则认为第一次的有效电平输入，为有效的信号*/       
    }
    else 
    {       
    }
    
    //StKeyLogic.KeyComing = LocalKeyFliter;/*这条不注释，可以从 idle->manual->auto->manual，即认为每一次的有效电平，都为有效电平*/
    
    
    StKeyLogic.OldKey = LocalKeyFliter; /*更新开关的输入状态*/
    
    
    /*冲突处理表*/
	switch(StKeyLogic.KeyComing)
	 {
		 case KEY_IDLE: 
				if((KEY_AUTODOWN== StKeyLogic.TempKey) || (KEY_AUTOUP== StKeyLogic.TempKey))
				{
					StKeyLogic.OutputKey = StKeyLogic.TempKey;
				}
				else
				{
					StKeyLogic.OutputKey = KEY_IDLE;
				}
					break;

		 case KEY_MANUALUP: 
			    if( KEY_IDLE == StKeyLogic.TempKey )	
				{
					StKeyLogic.OutputKey = KEY_MANUALUP;
				}
				else
				{
					StKeyLogic.OutputKey = KEY_IDLE;
				}
					break;
		 
		 case KEY_MANUALDOWN:
			    if(  KEY_IDLE == StKeyLogic.TempKey )	
				{
					StKeyLogic.OutputKey = KEY_MANUALDOWN;
				}
				else
				{
					StKeyLogic.OutputKey = KEY_IDLE;
				}				
				
					break;
		 
		 case KEY_AUTOUP:
			    if( (KEY_IDLE == StKeyLogic.TempKey )||(KEY_MANUALUP == StKeyLogic.TempKey)  )	
				{
					StKeyLogic.OutputKey = KEY_AUTOUP;
				}
				else
				{
					StKeyLogic.OutputKey = KEY_IDLE;
				}			 
					break;
		 
		 case KEY_AUTODOWN: 
			    if( (KEY_IDLE == StKeyLogic.TempKey) || (KEY_MANUALDOWN == StKeyLogic.TempKey ) )	
				{
					StKeyLogic.OutputKey = KEY_AUTODOWN;
				}
				else
				{
					StKeyLogic.OutputKey = KEY_IDLE;
				}
					break;
		 
	     default:   StKeyLogic.OutputKey = KEY_IDLE;				break;
		 
	 }
 
}






/*
	real key action monitor
*/

uint8 Key_AnalogMonitor(void){

    MethodCountFilter(AdcKeyMonitor(),&StKeyFilter);
   
	LocalKeyLogic(StKeyFilter.OutputSignal);
	
	return StKeyLogic.OutputKey;
	
}

/*
	set key status  by software
*/
uint8 KeyStatus_Set(uint8 KeyStatus )
{
    StKeyFilter.OutputSignal = KeyStatus;

	StKeyLogic.OutputKey = KEY_IDLE;
    
    StKeyLogic.TempKey = KEY_IDLE;
    
    StKeyLogic.OldKey = KEY_IDLE;
	
	return KeyStatus;
}

/*
	get key status  by software
*/
uint8 KeyStatus_Get(void)
{
	return StKeyLogic.OutputKey;
}







