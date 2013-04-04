#include "tCEWSM.h"

tCEWSM::tCEWSM(void){
	tInterpretorCommandInterface::id=103;
}

tCEWSM::~tCEWSM(void)
{
}
void tCEWSM::Processing(boost::intrusive_ptr<tShip> _ship_){
	if (!_ship_) return;
	_ship_->status.SetStatus(status);
	if (speedMin>0){
		_ship_->obj->SetMinSpeed(speedMin);
		_ship_->obj->SetMaxSpeed(speedMax);
	}
}

bool tCEWSM::IsComplete(boost::intrusive_ptr<tShip> _ship_){
	float cValue=0;//_ship_->obj->inertSpeed.GetCurValue();
	float cMax=0;//_ship_->obj->inertSpeed.GetMaximum()*(speedMax-0.005f);
	if (cValue>=cMax) {
		return true;
	}
	return false;
}
void tCEWSM::Reset(boost::intrusive_ptr<tShip> _ship_){}

void tCEWSM::Reset(){}