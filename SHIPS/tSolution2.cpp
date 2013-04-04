// tSolution2.cpp: implementation of the tSolution2 class.
//
//////////////////////////////////////////////////////////////////////

#include "tSolution2.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tSolution2::tSolution2(){
id=2;
}

tSolution2::~tSolution2(){}

void tSolution2::Execute(boost::intrusive_ptr<tShipCommand> shipCommand){
int a=0;
}

void tSolution2::Processing(){
// возвращаем атакующих:
//	base->defendShipsGroup<==base->atackShipsGroup;
std::list< boost::intrusive_ptr<tShipCommand> >::iterator sIter=_base->defendShipsGroup.begin();
//std::list< boost::intrusive_ptr<tObj> >::iterator pIter=_base->enemyShips.begin();
// по умолчанию - стыковка с базой

if (_base->workStruct.connectZone==false){
// т.к.может сработать событие о входе в сол.сис.необходимо
// в любом случае заново запросить станцию.
//	if ((*sIter)->_ship->HaveTarget()==false){
	_base->Assign(_base->starInterface->GetNearStation());
		// дать кораблям цель !!!!
//		(*sIter)->_ship->New_Target(_base->allTarget);
//-------------------------------------------------
// надо сопоставить этому кораблю тип комманды
// задать др.команду-с контролем расстояния до базы!
//т.е.как только dist_of_station<300 - команда завершена!
	sIter=_base->defendShipsGroup.begin();
		boost::intrusive_ptr<tICommand2> cmd2;
		cmd2=boost::intrusive_ptr<tICommand2> (new tICommand2);
		(*sIter)->_command=cmd2;
//-------------------------------------------------
// rem: compiler error:no apropriate default constructor available
// solution: need include"tICommandX.h"
// bag: find and use "friend class tICommand1;" as prototype class !?
//	}
//		boost::intrusive_ptr<tObj> tO;
		sIter++;
		if (sIter==_base->defendShipsGroup.end()) return;
//		std::list< boost::intrusive_ptr<tObj> >::iterator iVirtObj=_base->vObjList.begin();
		_base->SetAllFPoints();
		while (sIter!=_base->defendShipsGroup.end()){
//			if ((*sIter)->_ship->HaveTarget()==false){
// возможна ошибка!!! если просто смена ведущего, то надо либо удалять точки,
// либо оставлять привязку "как есть"

//				tO=(*iVirtObj);// ERROR !!!! ???

//				(*sIter)->_ship->New_Target(tO);
// надо сопоставить этому кораблю тип комманды
				boost::intrusive_ptr<tICommand1> cmd1;
				cmd1=boost::intrusive_ptr<tICommand1> (new tICommand1);
				(*sIter)->_command=cmd1;
//			}
			sIter++;
//			iVirtObj++;
		}
	}

}