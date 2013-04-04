// tICommand5.cpp: implementation of the tICommand5 class.
//
//////////////////////////////////////////////////////////////////////

#include "tICommand5.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tICommand5::tICommand5(){
	tInterpretorCommandInterface::id=5;
	step1=false;
}

tICommand5::~tICommand5()
{

}

void tICommand5::Processing(boost::intrusive_ptr<tShip> _ship_){
	if (!_ship_) return;
	if (!step1) {
		_ship_->status._status=5;
		if (_ship_->obj->inertX.Value<_ship_->obj->inertX.GetSteepness()*5.0f){
			step1=true;
		}
	}else{
		_ship_->status._status=6;
	}
}

bool tICommand5::IsComplete(boost::intrusive_ptr<tShip> _ship_){
	return false;
}
void tICommand5::Reset(boost::intrusive_ptr<tShip> _ship_){}

void tICommand5::Reset(){}