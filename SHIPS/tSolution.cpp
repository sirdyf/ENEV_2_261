// tSolution.cpp: implementation of the tSolution class.
//
//////////////////////////////////////////////////////////////////////

#include "tSolution.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



tSolution::~tSolution(){}


void tSolution::Init(boost::intrusive_ptr<ai_base> base){
	_base=base;
}
int tSolution::GetID(){
	return id;
}
void tSolution::WarningExecute(boost::intrusive_ptr<tShipCommand> shipCommand){
	return;// Debug !
}
// !!! ATTENTION !!! после атаки кораблю надо задать точку в строю
/*
		sIter=_base->attackShipGroup.begin();
		while (sIter!=_base->attackShipGroup.end()){

			if (_base->enemyShips.size()==0){
				// All ships must be fly in group
				
				if ((*sIter)->GetStatus()==1){
					if ((*sIter)->HaveTarget()){
						sIter++;
						continue;
					}
				}
				(*sIter)->CleanTarget();
				(*sIter)->New_Target(_base->GetFreePoint());
				(*sIter)->SetStatus(1);//лететь к целе
			}else{
				//	Atack ENEMY !
				// Remember: status=
				// 1 -корабль в строю
				// 2 -корабль атакует, при этом проверить таргет=0 ?
				// 7 -корабль без цели
				sIter=_base->attackShipGroup.begin();
				if ((*sIter)->GetStatus()==2){
					if ((*sIter)->HaveTarget()) return;
		
				}
				(*sIter)->SetStatus(2);
				(*sIter)->New_Target((*pIter));

			}
			sIter++;
		}
*/

// *** проверить флаг mustDestroy !!

