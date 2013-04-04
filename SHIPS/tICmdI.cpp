// tInterpretorCommandInterface.cpp: implementation of the tInterpretorCommandInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "tICmdI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tInterpretorCommandInterface::tInterpretorCommandInterface(){
id=0;
distance=0;
status=0;
speedMin=speedMax=-1;
}

tInterpretorCommandInterface::~tInterpretorCommandInterface()
{

}

int tInterpretorCommandInterface::GetID(){
	return id;
}
void tInterpretorCommandInterface::Init(int _status){
	status=_status;
}
void tInterpretorCommandInterface::Init(float dist,int _status){
	distance=dist;
	status=_status;
}
void tInterpretorCommandInterface::Init(int _status,float spMin, float spMax){
	status=_status;
	speedMin=spMin;
	speedMax=spMax;
}
void tInterpretorCommandInterface::Init(int _status,float spMin, float spMax, float aX, float aZ){
	status=_status;
	speedMin=spMin;
	speedMax=spMax;
	oX=aX;
	oZ=aZ;
}
void tInterpretorCommandInterface::Init(float dist,int _status,float spMin, float spMax){
	distance=dist;
	status=_status;
	speedMin=spMin;
	speedMax=spMax;
}
void tInterpretorCommandInterface::Init(float dist,int _status,float spMin, float spMax, float aX, float aZ){
	distance=dist;
	status=_status;
	speedMin=spMin;
	speedMax=spMax;
	oX=aX;
	oZ=aZ;
}
//void tInterpretorCommandInterface::Processing(boost::intrusive_ptr<tShip> ship){}
