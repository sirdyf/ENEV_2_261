// ai_s_null.cpp: implementation of the ai_s_null class.
//
//////////////////////////////////////////////////////////////////////

#include "ai_s_null.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ai_s_null::ai_s_null()
{

}

ai_s_null::~ai_s_null()
{

}

//extern const float g_ZDS;!!!!!
//extern const float g_CZ;!!!!!
const float g_ZDS		=1000.0f;//Çîíà Äåéñòâèÿ Ñòàíöèè
const float g_CZ		=300.0f; //Çîíà Ñòûêîâêè

void ai_s_null::Processing(){

	if (_base->enemyShips.size()>0){
		std::list<boost::intrusive_ptr<tObj> >::iterator beg,end;
		beg=_base->enemyShips.begin();end=_base->enemyShips.end();
		while(beg!=end){
			if ((*beg)->mustDestroy==true) {
				beg=_base->enemyShips.erase(beg);
			}else{
				++beg;
			}
		}
		if (_base->enemyShips.size()>0){
			_base->workStruct.enemy=true;
		}else{}
	}else{
		_base->workStruct.enemy=false;
	}
	D3DXVECTOR3 pos=_base->GetComanderPos();
	boost::intrusive_ptr<tObj> posSt=_base->starInterface->GetNearStation();//¢®§¢à.«¨¡® áâ ­æ¨î «¨¡® §¢¥§¤ã
	D3DXVECTOR3 res=pos-posSt->GetPos();
	float dist=D3DXVec3Length(&res);
	if (dist<g_ZDS) {
		_base->workStruct.stationZone=true;
		if (dist<g_CZ) {
			_base->workStruct.connectZone=true;
		}else{
			_base->workStruct.connectZone=false;
		}
	}else{
		_base->workStruct.stationZone=false;
		_base->workStruct.connectZone=false;
//		_base->bConnectGroup=false;
	}
/*
	sIter=_base->defendShipsGroup.begin();
	while (sIter!=_base->defendShipsGroup.end()){
		pos=(*sIter)->GetPos();
		posCP=_base->starInterface->GetConnectPoint();
		res=pos-posCP;
		dist=D3DXVec3Length(&res);
		if (dist<10.0f) (*sIter)->ConnectPoint();
		sIter++;
	}
	sIter=_base->defendShipsGroup.begin();
	while (sIter!=_base->defendShipsGroup.end()){
		if ((*sIter))
		sIter++;
	}
*/
return;
}
