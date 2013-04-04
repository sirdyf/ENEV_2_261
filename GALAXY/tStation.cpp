// tStation.cpp: implementation of the tStation class.
//
//////////////////////////////////////////////////////////////////////

#include "tStation.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


tStation::~tStation(){
	sISZ.clear();//shipInStationZone;
	connectShip.clear();
	attackingShips.clear();
}

void tStation::Attack(boost::intrusive_ptr<tObj> aShip){
	if (aShip) attackingShips.push_back(aShip);
}
void tStation::Processing(){
	std::list< boost::intrusive_ptr<tObj> >::iterator tIter;
	for (tIter=attackingShips.begin();tIter!=attackingShips.end();tIter++){
		if ((*tIter)->mustDestroy==true) //(*tIer)=0;//!!! ???
			tIter=attackingShips.erase(tIter);
	}
}

bool tStation::NeedDefenders(){
	if (attackingShips.size()<=numViper) return false;
	return true;
}

int tStation::getTar(){
	return attackingShips.size();
}

void tStation::InStationZone(boost::intrusive_ptr<tShip> ship){
// сделать перебор для исключения дублирования!!!
//	if (ship->level==10) {
//		ship->regOfStation=true;
//		attackingShips.push_back(ship->obj);
//	}
}
boost::intrusive_ptr<tObj> tStation::GetConnectPoint(){
	return conPoint;
}

void tStation::Init(){
	float r=tStation::obj->GetRadius();
	D3DXVECTOR3 pos=tStation::obj->GetPos()+D3DXVECTOR3(0.0f,0.0f,r+1500.0f);
	D3DXVECTOR3 pos2=pos+D3DXVECTOR3(0,0,500.0f);
	conPoint=pEng->CreateVirtObj(10.0f,pos);
	pointOfHyperJamp=pEng->CreateVirtObj(10.0f,pos2);
	tStation::obj->inertZ.SetValue(0.1714f);
//		mStation->radius=tPlanet::radius/10.0f;
//		mStation->pos=tPlanet::pos+D3DXVECTOR3(0.0f,0.0f,tPlanet::radius*2.0f);
//		mStation->pointOfHyperJamp->pos=mStation->pos+D3DXVECTOR3(0,0,500.0f);
//		strcat(mStation->name,"Station");
}

void tStation::Clear(){
	attackingShips.clear();
	connectShip.clear();
	sISZ.clear();
	curConnectShip=0;
}

void tStation::AsemblyRubish(){
	if (curConnectShip)//если есть стыкующийся корабль
		if (curConnectShip->mustDestroy==true)
				curConnectShip=0;
	
	std::list<boost::intrusive_ptr<tObj> >::iterator iShip;
	iShip=connectShip.begin();
	while(iShip!=connectShip.end()){
		if ((*iShip)->mustDestroy==true){
			iShip=connectShip.erase(iShip);
		}else{
			iShip++;
		}
	}
	iShip=attackingShips.begin();
	while(iShip!=attackingShips.end()){
		if ((*iShip)->mustDestroy==true){
			iShip=attackingShips.erase(iShip);
		}else{
			iShip++;
		}
	}
	// sISZ !!!!!
}
