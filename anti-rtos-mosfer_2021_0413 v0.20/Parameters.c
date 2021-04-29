#include "Motor_Parameter.h"


//减速区间，加速区间，恒定区间的宽度--霍尔脉冲数表示
#define  DECREASE_PAHSE   150u
#define  INCREASE_PAHSE   100u
#define  CONSTANT_PAHSE   10u

//软停点距离上限或者下限的距离--霍尔脉冲数表示
#define  SOFTSTOPDISTANCE 30

SpeedControl UpDirConfig={INCREASE_PAHSE,DECREASE_PAHSE,CONSTANT_PAHSE,SOFTSTOPDISTANCE,8,12,7};

SpeedControl DownDirConfig={INCREASE_PAHSE,DECREASE_PAHSE,CONSTANT_PAHSE,SOFTSTOPDISTANCE,8,12,4};

Pos_Mark    UP_Pos ={0};
Pos_Mark	Down_Pos={0};



