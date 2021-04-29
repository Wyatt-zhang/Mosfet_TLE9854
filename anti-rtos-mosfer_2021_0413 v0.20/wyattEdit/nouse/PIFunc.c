#include "PIFunc.h"
#include "stdlib.h"

//increase PI type
void PIFunc_Calc(PIFunc_Handle p)
{

	//get error
	p->PresentE = p->Give - p->FeedBack;
	
	
	p->Output = p->LastOutput + (p->Kp)*(p->PresentE - p->LastE) + (p->Ki)*(p->PresentE);
	
	//output limit
	if((p->Output)>(p->OutMax))
	{
		p->Output = p->OutMax ;
	}
	else if((p->Output)<(p->OutMin))
	{
		p->Output = p->OutMin;
	}
	else
	{
	}
	
	// save data
	p->LastOutput = p->Output ;
	
	p->LastE = p->PresentE;
}


