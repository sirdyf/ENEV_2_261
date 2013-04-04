// tICommand7.cpp: implementation of the tICommand7 class.
//
//////////////////////////////////////////////////////////////////////

#include "tICommand7.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tICommand7::tICommand7(){
	tInterpretorCommandInterface::id=7;
	tInterpretorCommandInterface::distance=600.0f;
}

tICommand7::~tICommand7(){}

void tICommand7::Processing(boost::intrusive_ptr<tShip> _ship_){
	if (!_ship_) return;
// маневр ухода от атаки
	_ship_->status._status=14;
}

bool tICommand7::IsComplete(boost::intrusive_ptr<tShip> _ship_){
	if (_ship_->dist>distance) return true;
	if (!_ship_->target) return true;
//	if (_ship_->dist>200.0f){//должно совпадать с 6-ой командой!
//		if (_ship_->tarLookMy==false){
//			return true;
//		}
//	}
	return false;
}
/*
void tICommand7::Init(boost::intrusive_ptr<tShip> _ship_){
	_ship_->obj->inertX.Value=_ship_->aY;
	//вычислить угол поворота
}
*/
void tICommand7::Reset(boost::intrusive_ptr<tShip> _ship_){
	_ship_->status._status=14;
//	_ship_->obj->SetRotateXZbalance(0.8f);
	_ship_->obj->inertX.Value=-0.0174533f*180.0f;
	_ship_->obj->inertZ.Value=0.0174533f*90.0f;
}

void tICommand7::Reset(){
}