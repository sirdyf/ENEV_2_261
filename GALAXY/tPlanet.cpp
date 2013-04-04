// tPlanet.cpp: implementation of the tPlanet class.
//
//////////////////////////////////////////////////////////////////////

#include "tPlanet.h"

extern pEngine* pEng;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tPlanet::~tPlanet(){}

void tPlanet::Init(bool bSpaceStation){
// ѕланета создает спутники и космическую станцию
	float rPlanet=tPlanet::obj->GetRadius();
	float rStation=20.0f;//rPlanet/5.0f;
	float d_of_p=rPlanet*1.5f;
	D3DXVECTOR3 pos=tPlanet::obj->GetPos();
	D3DXVECTOR3 pos2=pos+D3DXVECTOR3(0.0f,0.0f,d_of_p);
	if (bSpaceStation)	{
		mStation=boost::intrusive_ptr<tStation>(new tStation);
		mStation->obj=pEng->CreateObj(2,rStation,pos2);///50.0f,pos2);
		mStation->dist_of_planet=d_of_p;
		mStation->Init();
	}
}
