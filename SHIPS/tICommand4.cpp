// tICommand4.cpp: implementation of the tICommand4 class.
//
//////////////////////////////////////////////////////////////////////

#include "tICommand4.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tICommand4::tICommand4(){
	tInterpretorCommandInterface::id=4;
	tInterpretorCommandInterface::distance=300.0f;
}

tICommand4::~tICommand4()
{

}
void tICommand4::Processing(boost::intrusive_ptr<tShip> _ship_){
	if (!_ship_) return;
	_ship_->status._status=4;
}

bool tICommand4::IsComplete(boost::intrusive_ptr<tShip> _ship_){
	if (_ship_->dist<distance) {
		return true;
	}
	return false;
}
void tICommand4::Reset(boost::intrusive_ptr<tShip> _ship_){}

void tICommand4::Reset(){}