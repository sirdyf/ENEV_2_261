// AI_Star.cpp: implementation of the AI_Star class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "AI_Star.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



//void AI_Star::Init(){}
//boost::intrusive_ptr<tStarInterface> AI_Star::GetInterface(){
//	return mStarContainer;
//}

//extern const float g_DSD;

void AI_Star::Event(){

	if (!curPlanet) {return;}

	boost::intrusive_ptr<tStation> curStation;
	curStation=curPlanet->mStation;
	if (!curStation) {return;}
// проверяем и даем разрешение на стыковку.
	//std::list<boost::intrusive_ptr<tObj> >::iterator iShip;
	//if (!curStation->curConnectShip) {
	//	iShip=curStation->connectShip.begin();
	//	if (iShip!=curStation->connectShip.end()){
	//		curStation->curConnectShip=(*iShip);
	//		shInterface->AllowRegister(curStation->curConnectShip);
	//	}else{// нет стыкующихся - можно разрешить вылет со станции
	//	}
	//}

// проверяем появившиеся корабли и атакуем "плохих"
}
void AI_Star::Update(){
//--------------------------------------------------------------

//--------------------------------------------------------------
}
int AI_Star::GetData(char* buff){
	std::stringstream tmpOs;
	boost::archive::text_oarchive os(tmpOs);
	std::list< tSendData> lSendData;
	tSendData tmp;
	tmp.pos=mStar->obj->GetPos();
	tmp.radius=mStar->obj->GetRadius();
//	lSendData.push_back(tmp);
	boost::intrusive_ptr<tObj> tmpObj;
	std::list< boost::intrusive_ptr<tPlanet> >::const_iterator iPlanetB=mPlanets.begin(),iPlanetE=mPlanets.end();
	while(iPlanetB!=iPlanetE){
		tmp.pos=(*iPlanetB)->obj->GetPos();
		tmp.radius=(*iPlanetB)->obj->GetRadius();
		lSendData.push_back(tmp);
		iPlanetB++;
	}
	tServiceInfo tmpSI;
	tmpSI.mode=200;
	os << BOOST_SERIALIZATION_NVP(tmpSI);
	os << BOOST_SERIALIZATION_NVP(lSendData);
	int len=tmpOs.str().length();
	memcpy(buff,tmpOs.str().c_str(),len);
	return len;
}

void AI_Star::Processing(){
//	if (mStarContainer->CheckEvent()) Event();//wait connection
// с точностью до 1000 задано в pEngine!
	D3DXVECTOR3 solPos=mStar->obj->GetPos();
	float dist=D3DXVec3Length(&solPos);
	if (dist<100000.0f) {
		if (!curPlanet){
			curPlanet=GetNearPlanet();
			bSolSystem=true;

//			Ships->Event();
			bEvent=true;

		}else{
			if (curPlanet->mStation){
				solPos=curPlanet->mStation->obj->GetPos();
				dist=D3DXVec3Length(&solPos);
				if (dist<5000.0f){//!!!!!!!!!
					if (bStationZone==false){
						bStationZone=true;
//						Ships->Event();
						bEvent=true;
					}else{}
				}else{
					bStationZone=false;
				}
			}else{
				bStationZone=false;
			}
		}
	}else{
			bSolSystem=false;
// !!!! вне солнечной системы обнулить все указатели!
		if (curPlanet){
			if (curPlanet->mStation){
				curPlanet->mStation->Clear();//???
				curPlanet->mStation->curConnectShip=0;
				curPlanet->mStation=0;
			}
			curPlanet=0;
		}
	}
}
void AI_Star::AsemblyRubish(){
//	mStarContainer->AsemblyRubish();
	if (curPlanet)
		if (curPlanet->mStation)
			curPlanet->mStation->AsemblyRubish();
}

//void AI_Star::Calculate(D3DXVECTOR3 camPos){
// Atention! camPos/solPos=scale !!!
//	D3DXVECTOR3 solPos=mStarContainer->GetNearSol(camPos)->GetPos();// scale !!!
//	D3DXVECTOR3 vec=camPos-solPos;// scale !!!
//	float dist=D3DXVec3Length(&vec);
//	if (dist<100000.0f) mStarContainer->bInSolSystem=true;
//	else mStarContainer->bInSolSystem=false;
//}
//void AI_Star::SetInterface(boost::intrusive_ptr<tShipsInterface> i){
//	shInterface=i;
//}
int AI_Star::GetUinStarName(){
	return this->mStar->uin;
}
int AI_Star::GetUinPlanetName(int num){
	if (num<0) return 0;
	if (num>numOfPlanets) return 0;
	return this->mStar->uin+num;
}


//----------------------------------------

void AI_Star::SetStar(int nmPlanets,float uin){
	mStar=boost::intrusive_ptr<tStar> (new tStar);
	if (mStar)
		SDELog.WriteMessage("Создание звезды");
	else
		SDELog.WriteWarning("Звезда НЕ создана(!)");
	mPlanets.clear();
	SDELog.WriteMessage("Очистка списка планет");

	D3DXMATRIX tmp,tmp2;
	float dist=0,rad=0,angl;
	D3DXVECTOR3 pos=D3DXVECTOR3(0,0,0);
	this->numOfPlanets=nmPlanets;
	mStar->Init(uin);
	mPlanets.clear();
// Звезда создает планеты
	float distOfSan[9]={
		  57909000.0f,//меркурий
		 108208930.0f,//Венера
		 149600000.0f,//Земля
		 227936640.0f,//Марс
		 778412010.0f,//Юпитер
		1426725400.0f,//Сатурн
		2870972200.0f,//Уран
		4498252900.0f,//Нептун
		5906376200.0f//Плутон
	};
	float diamOfPlanets[9]={
		  4879.4f,//меркурий
		 12103.6f,//Венера
		 12756.3f,//Земля
		  6794.0f,//Марс
		142984.0f,//Юпитер
		120536.0f,//Сатурн
		 51118.0f,//Уран
		 55528.0f,//Нептун
		  2320.0f//Плутон
	};// солнце 1 391 980 км.

//tMakeName tMN;
	for (int i=0;i<numOfPlanets;i++){
		angl=6.3f*(FLOAT)(rand())/RAND_MAX;
		rad=100.0f;//510.0f;//diamOfPlanets[i]/2.0f;
		dist=distOfSan[i]/1000.0f;
		D3DXMatrixTranslation(&tmp,0.0f,0.0f,dist);
		D3DXMatrixRotationAxis(&tmp2,&(D3DXVECTOR3(0,1,0)),angl);
		D3DXMatrixMultiply(&tmp,&tmp,&tmp2);
// вычисляем координаты планеты
		D3DMath_VectorMatrixMultiply( pos,pos,tmp);
		boost::intrusive_ptr<tPlanet> tmpPlanet(new tPlanet);
		tmpPlanet->obj=pEng->CreateObj(2,rad,pos);

//		tMN.
//		MakePlanetName(&tmpPlanet->obj->name[0],uin+(float)i);

		tmpPlanet->dist_of_star=dist;//17000.0f+100.0f*(FLOAT)(rand())/RAND_MAX-50.0f;//40*(FLOAT)(rand())/RAND_MAX-20
		tmpPlanet->angl=angl;
		tmpPlanet->num_of_satelitte=0;

		if (i<3) tmpPlanet->Init(true);
		mPlanets.push_back(tmpPlanet);
		tmpPlanet=0;
//		tmpPlanet->obj->AddRef();//!!!!!!!!!!!!!!!!!!!!!
	}
	this->Update();
}

D3DXVECTOR3 AI_Star::GetStarPos(){

	return mStar->obj->GetPos();
}

float AI_Star::GetStarRadius(){

	return mStar->obj->GetRadius();
}

boost::intrusive_ptr<tObj> AI_Star::GetPlanetObj(unsigned int num){

	boost::intrusive_ptr<tObj> tmpObj;
	std::list< boost::intrusive_ptr<tPlanet> >::iterator tmpPlanet=mPlanets.begin();
	if (num<=numOfPlanets){
		for (;num>0;num--)	tmpPlanet++;
	}
	tmpObj=(*tmpPlanet)->obj;
//	else{tmpObj=mStar->obj;}
	return tmpObj;
}

int AI_Star::GetNumPlanets(){
	numOfPlanets=mPlanets.size();
	return numOfPlanets;
}
D3DXVECTOR3 AI_Star::GetGatewayVector(){
	D3DXVECTOR3 tmpVec(500,500,-500.0f);
	D3DXVECTOR3 p(0,0,0);
	D3DXVECTOR3 s(0,0,0);
	boost::intrusive_ptr<tObj> nStation;
	if (curPlanet){
		if (curPlanet->mStation){
			p=curPlanet->obj->GetPos();
			s=curPlanet->mStation->obj->GetPos();
//			tmpVec=s-p;
			tmpVec=s+tmpVec;
		}
	}
	return tmpVec;
}
boost::intrusive_ptr<tObj> AI_Star::GetNearStation(){
	
	boost::intrusive_ptr<tObj> tmpObj;//=boost::intrusive_ptr<tObj> (new tObj);
	tmpObj=mStar->obj;
	if (curPlanet){
		tmpObj=curPlanet->obj;
		if (curPlanet->mStation){
			tmpObj=curPlanet->mStation->obj;
		}else{
			tmpObj=GetPlanetWithStation();
			if (!tmpObj){}//ERROR нет планет со станцией
		}
	}

return tmpObj;
}

int AI_Star::GetNextPlanet(int numPlanet){
	if (numPlanet+1>=numOfPlanets) return 0;
	if (numPlanet<0) return 0;

	return numPlanet+1;
}
bool AI_Star::RegisterShip(boost::intrusive_ptr<tObj> sh){
	if (!sh) return false;
	if (!curPlanet) return false;
	if (!curPlanet->mStation) return false;

	curPlanet->mStation->connectShip.push_back(sh);
return true;
}


boost::intrusive_ptr<tPlanet> AI_Star::GetNearPlanet(){
	D3DXVECTOR3 p=D3DXVECTOR3(0,0,0);//?????
	std::list< boost::intrusive_ptr<tPlanet> >::iterator tmpPlanet=mPlanets.begin();
	boost::intrusive_ptr<tPlanet> resPlanet=(*tmpPlanet);
/*
	D3DXVECTOR3 plPos=(*tmpPlanet)->obj->GetPos();
    D3DXVECTOR3 delta=p-plPos;
	float dist=D3DXVec3Length(&delta);
	float dMin=dist;
	while(tmpPlanet!=mPlanets.end()){
		plPos=(*tmpPlanet)->obj->GetPos();
	        delta=p-plPos;
	        dist=D3DXVec3Length(&delta);
	        if (dist<dMin) {
	        	dist=dMin;
//!!!!	        	resPlanet=tmpPlanet;
	        }
		tmpPlanet++;
	}
*/
	return resPlanet;
}
boost::intrusive_ptr<tObj> AI_Star::GetConnectPoint(){
	boost::intrusive_ptr<tObj> tmpObj;//=boost::intrusive_ptr<tObj> (new tObj);
	tmpObj=0;
	if (curPlanet)
		if (curPlanet->mStation)
			tmpObj=curPlanet->mStation->GetConnectPoint();

return tmpObj;
}
bool AI_Star::StationZone(){
	return bStationZone;
}


bool AI_Star::CheckEvent(){
	if (bEvent) return true;
// если есть ожидающие стыковки - генерится событие
		if (curPlanet)
			if (curPlanet->mStation)
				if (curPlanet->mStation->connectShip.size()>0)
					if (!curPlanet->mStation->curConnectShip) return true;
	
return false;
}

boost::intrusive_ptr<tObj> AI_Star::GetPlanetWithStation(){

	std::list< boost::intrusive_ptr<tPlanet> >::iterator tmpPlanet=mPlanets.begin(),end=mPlanets.end();
	for (;tmpPlanet!=end;++tmpPlanet){
		if ((*tmpPlanet)->mStation) return (*tmpPlanet)->mStation->obj;
	}
	return 0;
}

bool AI_Star::SolSystem(){

	return bSolSystem;

	if (bSolSystem){
		bSolSystem=false;
		return true;
	}
return false;
}
