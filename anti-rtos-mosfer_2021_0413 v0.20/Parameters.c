#include "Motor_Parameter.h"


//�������䣬�������䣬�㶨����Ŀ��--������������ʾ
#define  DECREASE_PAHSE   150u
#define  INCREASE_PAHSE   100u
#define  CONSTANT_PAHSE   10u

//��ͣ��������޻������޵ľ���--������������ʾ
#define  SOFTSTOPDISTANCE 30

SpeedControl UpDirConfig={INCREASE_PAHSE,DECREASE_PAHSE,CONSTANT_PAHSE,SOFTSTOPDISTANCE,8,12,7};

SpeedControl DownDirConfig={INCREASE_PAHSE,DECREASE_PAHSE,CONSTANT_PAHSE,SOFTSTOPDISTANCE,8,12,4};

Pos_Mark    UP_Pos ={0};
Pos_Mark	Down_Pos={0};



