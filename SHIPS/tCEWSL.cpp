#include "tCEWSL.h"

tCEWSL::tCEWSL(void){
	tInterpretorCommandInterface::id=104;
}

tCEWSL::~tCEWSL(void)
{
}
void tCEWSL::Processing(boost::intrusive_ptr<tShip> _ship_){
	if (!_ship_) return;
	_ship_->status.SetStatus(status);
	if (speedMin>0){
		_ship_->obj->SetMinSpeed(speedMin);
		_ship_->obj->SetMaxSpeed(speedMax);
	}
}

bool tCEWSL::IsComplete(boost::intrusive_ptr<tShip> _ship_){
	float cValue=0;//_ship_->obj->inertSpeed.GetCurValue();
	float cMin=0;//_ship_->obj->inertSpeed.GetMaximum()*(speedMin+0.005f);
	if (cValue<=cMin) {
		return true;
	}
	return false;
}
void tCEWSL::Reset(boost::intrusive_ptr<tShip> _ship_){}

void tCEWSL::Reset(){}