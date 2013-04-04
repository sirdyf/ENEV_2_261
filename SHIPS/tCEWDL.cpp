#include "tCEWDL.h"

tCEWDL::tCEWDL(void){
	tInterpretorCommandInterface::id=101;
}

tCEWDL::~tCEWDL(void){}

void tCEWDL::Processing(boost::intrusive_ptr<tShip> _ship_){
	if (!_ship_) return;
	_ship_->status.SetStatus(status);
	if (speedMin>0){
		_ship_->obj->SetMinSpeed(speedMin);
		_ship_->obj->SetMaxSpeed(speedMax);
	}
}

bool tCEWDL::IsComplete(boost::intrusive_ptr<tShip> _ship_){
	if (_ship_->dist>distance) return true;
	return false;
}
void tCEWDL::Reset(boost::intrusive_ptr<tShip> _ship_){}


void tCEWDL::Reset(){}