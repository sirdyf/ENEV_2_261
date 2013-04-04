#include "tCRotateZ.h"
// Подойдет и для вращения по Х
tCRotateZ::tCRotateZ(void){
	tInterpretorCommandInterface::id=105;
	init=true;
}

tCRotateZ::~tCRotateZ(void)
{
}
void tCRotateZ::Processing(boost::intrusive_ptr<tShip> _ship_){
	if (!_ship_) return;
	_ship_->status.SetStatus(status);
	if (speedMin>0){
		_ship_->obj->SetMinSpeed(speedMin);
		_ship_->obj->SetMaxSpeed(speedMax);
	}
/*
	if (init){
		init=false;
		_ship_->obj->inertX.Value=oX;
		_ship_->obj->inertZ.Value=oZ;
	}
*/
// Ускоряться(10) или тормозить(11) выбирается с помощью "status"
}

bool tCRotateZ::IsComplete(boost::intrusive_ptr<tShip> _ship_){
	float cValue=0;
	float cMax=0;
	if (oZ!=0){
		cValue=_ship_->obj->inertZ.Value;
		cMax=_ship_->obj->inertZ.GetSteepness()*10.0f;
		if (cValue<cMax){
			init=true;
			return true;
		}
	}
	if (oX!=0){
		cValue=_ship_->obj->inertX.Value;
		cMax=_ship_->obj->inertX.GetSteepness()*10.0f;
		if (fabsf(cValue)<fabsf(cMax)){
			init=true;
			return true;
		}
	}
	return false;
}
void tCRotateZ::Reset(boost::intrusive_ptr<tShip> _ship_){
	_ship_->obj->inertX.Value=oX;
	_ship_->obj->inertZ.Value=oZ;
}
void tCRotateZ::Reset(){
}