// tSolution3.cpp: implementation of the tSolution3 class.
//
//////////////////////////////////////////////////////////////////////

#include "tSolution3.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tSolution3::tSolution3(){
bConnectGroup=false;
bConnectPoint=false;
id=3;
}

tSolution3::~tSolution3(){}

void tSolution3::Execute(boost::intrusive_ptr<tShipCommand> shipCommand){
int a=0;// 123
	boost::intrusive_ptr<tObj> conPoint;
	boost::intrusive_ptr<tObj> stationPoint;
	if (!shipCommand->_command) return;
	int cmd=shipCommand->GetCommandId();
	switch(cmd){
		case 3:
/*
			conPoint=_base->starInterface->GetConnectPoint();
//123					(*sIter)->_ship->New_Target(tar);
			shipCommand->SetTarget(conPoint);
			shipCommand->_command=boost::intrusive_ptr<tICommand5> (new tICommand5);//cPatrul;//next command
			//shipCommand->SetCommand(
			shipCommand->m_refCounter+=tSolution3::m_refCounter-1;//???check!!!!
			break;
		case 5:
*/
			shipCommand->_ship->obj->SetMinSpeed(0.5f);
			stationPoint=_base->starInterface->GetNearStation();
			shipCommand->SetTarget(stationPoint);
			shipCommand->_command=boost::intrusive_ptr<tICommand4> (new tICommand4);//cReturn;//next command
			shipCommand->m_refCounter+=tSolution3::m_refCounter-1;//???check!!!!
			break;
		default:
			//shipCommand->_command=0;
			break;
	}

}

void tSolution3::Processing(){
// begin connect procedure
// 1)stop,wait
// 2)go to connect point
// 3)connect station
// all ships must be in defendShipsGgoup !!
	if (bConnectGroup==false){
		Step1();
	}else{
//		Step2();
	}
}
bool tSolution3::Step1(){
	bool fl=false;
	std::list<boost::intrusive_ptr<tShipCommand> >::iterator sIter;
	_base->SetAllTarget(_base->starInterface->GetNearStation());
	bConnectGroup=true;

	sIter=_base->defendShipsGroup.begin();
	boost::intrusive_ptr<tInterpretorCommandInterface> cmd;
	if (sIter==_base->defendShipsGroup.end()) return false;
	while (sIter!=_base->defendShipsGroup.end()){
		fl=_base->starInterface->RegisterShip((*sIter)->_ship->obj);
		if (fl==false) bConnectGroup=false;
		cmd=boost::intrusive_ptr<tICommand3> (new tICommand3());
		(*sIter)->_command=cmd;
//		(*sIter)->_ship->New_Target(_base->allTarget);
		sIter++;
	}
	if (bConnectGroup==false){
	// ERROR !! (for break point)
	}
	return true;
}
bool tSolution3::Step2(){
	boost::intrusive_ptr<tObj> tar;
	boost::intrusive_ptr<tObj> conPoint;
	boost::intrusive_ptr<tObj> stationPoint;
		boost::intrusive_ptr<tInterpretorCommandInterface> cmd;
	std::list<boost::intrusive_ptr<tShipCommand> >::iterator sIter;
	sIter=_base->defendShipsGroup.begin();
	if (sIter==_base->defendShipsGroup.end()) return false;
//		p=(*sIter)->_ship->obj->GetPos();
		stationPoint=_base->starInterface->GetNearStation();
		conPoint=_base->starInterface->GetConnectPoint();
	

	while (sIter!=_base->defendShipsGroup.end()){
//123		if ((*sIter)->_ship->HaveConnectContract())
		{//
//123(*sIter)->_ship->obj->SetMinSpeed(0.5);
//123			tar=(*sIter)->_ship->GetTargetObj();

//			if (stationPoint==tar) return false;

			if (conPoint==tar) {
//123				if ((*sIter)->_command->IsComplete((*sIter)->_ship)){
					tar=stationPoint;
					cmd=boost::intrusive_ptr<tICommand5> (new tICommand5);
					(*sIter)->_command=cmd;
//123					(*sIter)->_ship->New_Target(tar);
//123				}else{}
			}else{
				cmd=boost::intrusive_ptr<tICommand4> (new tICommand4);
				(*sIter)->_command=cmd;
//123				(*sIter)->_ship->New_Target(conPoint);
			}

		}
		sIter++;
	}
	return true;
}
