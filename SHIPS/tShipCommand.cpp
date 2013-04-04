// tShipCommand.cpp: implementation of the tShipCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "tShipCommand.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



tShipCommand::~tShipCommand(){}

int tShipCommand::GetShipIdGroup(){
	return _ship->GetIdGroup();
}

bool tShipCommand::CheckHit(boost::intrusive_ptr<tObj> enemy){
	bool fl=_ship->CheckFireHit(enemy);
	return fl;
}

bool tShipCommand::CheckFire(){
	bool fl=_ship->IsFire();
	return fl;
}
bool tShipCommand::SetMine(){
/*
// ƒобавить проверку на свои мины - чтобы "свои" не блокировали друг друга.
	D3DXVECTOR3 p=_ship->GetPos();
	D3DXVECTOR3 z=_ship->obj->tz;
	float r=_ship->obj->GetRadius();
	p=p-z*r-z*3.0f;//устанавливаем сзади - радиус самого корабл€ - 2
	boost::intrusive_ptr<tObj> tmpObj=pEng->CreateObj(6,1,p);//gres indEngine rad pos
	tmpObj->SetExplosive(20.0f,5.5f,_ship->GetIdGroup());
	Others->AddObj(tmpObj);
	_ship->WarningReset();
*/
	return true;

}

bool tShipCommand::CheckWarnings(){
	return _ship->Warnings();
}

void tShipCommand::Assign(boost::intrusive_ptr <tInterpretorCommandInterface> _cmd){
	if (_command==_cmd) return;
	_command=_cmd;
//	_command->m_refCounter+=tShipCommand::m_refCounter-1;
}
void tShipCommand::Assign(boost::intrusive_ptr <tShip> _sh){
	if (_ship==_sh) return;
	_ship=_sh;
//	_ship->m_refCounter+=tShipCommand::m_refCounter-1;
}
void tShipCommand::SetShip(boost::intrusive_ptr <tShip> _sh){
	if (_sh) Assign(_sh);
}
void tShipCommand::SetTarget(boost::intrusive_ptr<tObj> tO){
	if (_ship) {
		_ship->New_Target(tO);
	}
}
void tShipCommand::SetCommand(boost::intrusive_ptr <tInterpretorCommandInterface> command){
	_command=command;
}
int tShipCommand::GetCommandId(){
	return _command->GetID();
}

D3DXVECTOR3 tShipCommand::GetShipPos(){
	D3DXVECTOR3 t(0,0,0);
	if (_ship) return _ship->obj->GetPos();
	return t;
}
bool tShipCommand::IsComplete(){
	return _command->IsComplete(_ship);

}
void tShipCommand::ProcessCommand(){
	if (_command) _command->Processing(_ship);//!@!@!@!@!@!
}

bool tShipCommand::Validate(){
	if (!_command) return true;
	if (_command->IsComplete(_ship)) {
//		_command=0; // error! what command is complete?
		return true;
	}
	return false;
}
void tShipCommand::ResetCommand(){
	_command->Reset(_ship);
}
