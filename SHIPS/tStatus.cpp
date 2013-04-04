// tStatus.cpp: implementation of the tStatus class.
//
//////////////////////////////////////////////////////////////////////

#include "tStatus.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tStatus::tStatus(){
	_status=0;
//	aiStatus=0;
//	tacticStatus=0;
}

tStatus::~tStatus()
{

}

int tStatus::GetStrategyStatus(){
	return 0;//aiStatus;
}

//void tStatus::SetStrategyStatus(int a){aiStatus=a;}

tStatus::tStatus(int s){
	_status=s;
}

int tStatus::GetStatus(){
	return _status;
}
void tStatus::SetStatus(int st){
	_status=st;
}
