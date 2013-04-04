// ai_base.cpp: implementation of the ai_base class.
//
//////////////////////////////////////////////////////////////////////

#include "ai_base.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


ai_base::~ai_base(){ }

void ai_base::Assign(boost::intrusive_ptr<tObj> _allTar){
	std::list< boost::intrusive_ptr<tShipCommand> >::const_iterator pShip=defendShipsGroup.begin();
	(*pShip)->SetTarget(_allTar);
	if (allTarget==_allTar) return;
		allTarget=_allTar;
		allTarget->m_refCounter+=ai_base::m_refCounter-1;
}
void ai_base::SetAllTarget(boost::intrusive_ptr<tObj> _allTar){
	std::list< boost::intrusive_ptr<tShipCommand> >::const_iterator pShip,end;
	if (!_allTar) return;
	Assign(_allTar);
	for(pShip=defendShipsGroup.begin(),end=defendShipsGroup.end();pShip!=end;++pShip){
		(*pShip)->SetTarget(_allTar);
	}
}
void ai_base::SetAllTarget(){
	std::list< boost::intrusive_ptr<tShipCommand> >::const_iterator pShip,end;
	if (!allTarget) return;
	for(pShip=defendShipsGroup.begin(),end=defendShipsGroup.end();pShip!=end;++pShip){
		(*pShip)->SetTarget(allTarget);
	}
}
void ai_base::SetAllFPoints(){
	std::list< boost::intrusive_ptr<tShipCommand> >::const_iterator pShip,end;
	std::list< boost::intrusive_ptr<tObj> >::const_iterator pVP,end2;
	pVP=vObjList.begin();end2=vObjList.end();
	if (pVP==end2) return;
	pShip=defendShipsGroup.begin();
	pShip++;
	end=defendShipsGroup.end();
	for(;pShip!=end;++pShip,++pVP){
		if (pVP==end2) pVP=vObjList.begin();
		(*pShip)->SetTarget((*pVP));
	}
}
void ai_base::SetAllCommand(boost::intrusive_ptr <tInterpretorCommandInterface> _command){
	std::list< boost::intrusive_ptr<tShipCommand> >::const_iterator pShip,end;
	for(pShip=defendShipsGroup.begin(),end=defendShipsGroup.end();pShip!=end;++pShip){
		(*pShip)->SetCommand(_command);
	}
}

void ai_base::Processing(){
//	solution->Processing();
}

D3DXVECTOR3 ai_base::GetComanderPos(){
	std::list< boost::intrusive_ptr<tShipCommand> >::iterator pShip;
	D3DXVECTOR3 pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	if (defendShipsGroup.size()>0){
		pShip=defendShipsGroup.begin();
		pos=(*pShip)->GetShipPos();
	}
	return pos;
}
