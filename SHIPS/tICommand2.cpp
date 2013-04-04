// tICommand2.cpp: implementation of the tICommand2 class.
//
//////////////////////////////////////////////////////////////////////

#include "tICommand2.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tICommand2::tICommand2(){
	tInterpretorCommandInterface::id=2;
	tInterpretorCommandInterface::distance=0;
	complete=false;
}

tICommand2::~tICommand2(){}

void tICommand2::Processing(boost::intrusive_ptr<tShip> _ship_){
	if (!_ship_) return;
//	ship=_ship_;
//	ship->status._status=1;
	_ship_->status._status=1;//!!!!!!!
}

extern float globalTT;
const float g_CZ		=300.0f; //Зона Стыковки

bool tICommand2::IsComplete(boost::intrusive_ptr<tShip> _ship_){
//	if (_ship_->HaveTarget()==false){}

	if (_ship_->dist==0) return false;// ???? !!!!
	if (_ship_->dist<g_CZ) complete=true;
	if (complete) {
		return true;
	}
	return complete;
}
void tICommand2::Reset(boost::intrusive_ptr<tShip> _ship_){}

void tICommand2::Reset(){}