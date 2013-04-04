#include "tCEWDM.h"

tCEWDM::tCEWDM(void){
	tInterpretorCommandInterface::id=100;
}

tCEWDM::~tCEWDM(void){}

void tCEWDM::Processing(boost::intrusive_ptr<tShip> _ship_){
	if (!_ship_) return;
	_ship_->status.SetStatus(status);
	if (speedMin>0){
		_ship_->obj->SetMinSpeed(speedMin);
		_ship_->obj->SetMaxSpeed(speedMax);
	}
}

bool tCEWDM::IsComplete(boost::intrusive_ptr<tShip> _ship_){
	if (_ship_->dist<distance) return true;
	return false;
}
void tCEWDM::Reset(boost::intrusive_ptr<tShip> _ship_){}

void tCEWDM::Reset(){}