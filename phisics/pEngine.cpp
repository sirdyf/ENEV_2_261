// pEngine.cpp: implementation of the pEngine class.
//
//////////////////////////////////////////////////////////////////////
#include "pEngine.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

pEngine::pEngine(){
//	engList.reserve(10);
	objChange=false;
//	timers=GetTickCount();
	steps=true;
	fpDeltaTime=0;
	bGameOver=false;
//	last_time=GetTickCount();
//	cur_time=0;
	nEngine=-1;
	nShip=-1;
	uinCount=0;
//	dObjList1=0,dObjList2=0,dFrameObjList=0;
	hObjList=CreateMutex(NULL,false,0);
	//i_stream.str(&szTemp2[0]);
	dCurTime=0;
	dBackTime=400.0f;
//	szSI=sizeof(tServiceInfo);
}

pEngine::~pEngine(){
	CloseHandle(hObjList);
	formationsObjList.clear();
	objList.clear();
	virtObjList.clear();
}

void pEngine::GetSmallObj(tIStoragePhysics* strgPhys){
	WaitForSingleObject(hObjList,INFINITE);
	std::list< boost::intrusive_ptr<tObj> >::iterator i=objList.begin();
// добавить пропуск клиентов,которые находятся на станции ?
	while(i!=objList.end()){
		if ((*i)->radius<10){ //!!!!
			strgPhys->AddObj((*i));
		}
		++i;
	}
	ReleaseMutex(hObjList);
}



bool pEngine::LoadEquipment(){
	char mstr[255]={0};
	char* tstr=0;
	int cmd=0,eqType=0;
	nEngine=-1;
	nShip=-1;
	int tst=0;
	std::string buf;
	FILE* mf=0;
//	mf=fopen("..\\ships\\data\\equipment.str","rt");
	mf=fopen("../main/equipment.str","rt");
	if (mf==NULL) return false;
	while(fgets(mstr,255,mf)){//
		cmd=0;
		if (mstr[strlen(mstr)-1]<33) mstr[strlen(mstr)-1]=0;
		if (mstr[0]==0) continue;
		buf=mstr;
		buf=buf.substr(buf.find_first_not_of("	 "),buf.find_last_not_of("	 ")+1);
		if (buf.find("STRUCT")==0) cmd=2;
		if (buf.find("END")==0) cmd=4;
		if (buf.compare("STRUCT ShipEquipment")==0) cmd=1;
		if (buf.compare("END STRUCT")==0) cmd=3;

		switch(cmd){
		case 1:
			eqType=1;
		break;
		case 2:
			tstr=&mstr[8];
			if (strcmp(tstr,"engine")==0) {eqType=21;break;}
//			if (strcmp(tstr,"weapon")==0) {eqType=22;break;}
			if (strcmp(tstr,"ship")==0) {eqType=23;break;}
// определяем тип параметра
			if (eqType==21) {
				nEngine++;
			}
			if (eqType==22){
//				nWeapon++;
			}
			if (eqType==23){
				nShip++;
//				mShip[nShip].gres=nShip;//убрал в файл настроек
			}
		break;
		case 3:
			eqType=3;
		break;
		case 4:
		break;
		default:
			//проверяем к какому типу принадлежит пар-р
			//если двигатель
			if (eqType==21){
				if (!mEngine[nEngine].SetValue(buf)){//Unknown Value ?
					char b[50]={0};
					strcat(b,buf.c_str());
					if (!SetEngineInertValue(nEngine,&b[0])){// inertion ?
						//Unknown Value !
					}
				}
			}
			if (eqType==22){
				//if (!mWeapon[nWeapon].SetValue(buf)){
				//	//Unknown Value
				//}
			}
			if (eqType==23){
				if (!mShip[nShip].SetValue(buf)){
					//Unknown Value
				}
			}
		}		
	}
	fclose(mf);

	return true;
}

boost::intrusive_ptr<tObj> pEngine::CreateObj(int gres,float rad,D3DXVECTOR3 pos,int indexEngine,float fShield,int idGr,bool camera){

	boost::intrusive_ptr<tObj> tmpObj(new tObj);

	objChange=true;
	
	if (indexEngine>10) indexEngine=0;

	tmpObj->inertX=engList[indexEngine].inertX;
	tmpObj->inertZ=engList[indexEngine].inertZ;
	tmpObj->inertY=engList[indexEngine].inertY;
	tmpObj->inertSpeed=engList[indexEngine].inertSpeed;
	
	tmpObj->tx=D3DXVECTOR3(1,0,0);
	tmpObj->ty=D3DXVECTOR3(0,1,0);
	tmpObj->tz=D3DXVECTOR3(0,0,1);// -1 ?

	++uinCount;
	tmpObj->uin=uinCount;
	tmpObj->gRes=gres;
	tmpObj->radius=rad;
	tmpObj->pos=pos;
	tmpObj->baseShield=fShield;
	tmpObj->idGroup=idGr;

		D3DXMATRIX matView;
		D3DXMatrixIdentity(&matView);
		D3DXVECTOR3 eye=tmpObj->tz;
		D3DXMatrixLookAtLH (&matView, &D3DXVECTOR3(0,0,0),&eye,&tmpObj->ty);
//		D3DXMatrixTranspose(&matView,&matView);
		tmpObj->m=matView;
		if (tmpObj->radius==3){
			int my=0;
		}
WaitForSingleObject(hObjList,INFINITE);

	if (camera)
		objList.push_front(tmpObj);
	else
		objList.push_back(tmpObj);

ReleaseMutex(hObjList);
	return tmpObj;
}
boost::intrusive_ptr<tObj> pEngine::CreatePointObj(float rad,boost::intrusive_ptr<tObj> home,D3DXVECTOR3 delta, int idGroup){

	boost::intrusive_ptr<tFormations> tmpObj(new tFormations);
	tmpObj->home=home;
// пустой объект
	boost::intrusive_ptr<tObj> nullObj(new tObj);
	nullObj->pos=home->pos+delta;
	nullObj->tx=D3DXVECTOR3(1,0,0);
	nullObj->ty=D3DXVECTOR3(0,1,0);
	nullObj->tz=D3DXVECTOR3(0,0,1);
	nullObj->radius=rad;
	nullObj->gRes=0;
//*********************
	tmpObj->obj=nullObj;
	tmpObj->delta=delta;
	tmpObj->idGroup=idGroup;
	
	formationsObjList.push_back(tmpObj);

	return nullObj;
}
boost::intrusive_ptr<tObj> pEngine::CreateVirtObj(float rad,D3DXVECTOR3 pos,
										D3DXVECTOR3 tx,
										D3DXVECTOR3 ty,
										D3DXVECTOR3 tz){
	boost::intrusive_ptr<tObj> tmpObj(new tObj);
	tmpObj->pos=pos;
	tmpObj->tx=tx;
	tmpObj->ty=ty;
	tmpObj->tz=tz;
	tmpObj->radius=rad;
	tmpObj->gRes=0;
	virtObjList.push_back(tmpObj);
	return tmpObj;
}

bool pEngine::SetEngineInertValue(int ind,char* buf){
	int tst=0,cmd=0;
	int i=0;
	char* buf2=0;
	if (buf[0]==0) return false;
	for(i=0;i<20;++i){
		if (buf[i]==0) break;
		if (buf[i]==32) break;
	}
	if (i==20) return false;
	buf[i]=0;
	buf2=buf+i+1;
	if (strcmp("InertionSTEP",buf)==0) cmd=1;
	if (strcmp("InertSpeedSTEP",buf)==0) cmd=2;
	if (strcmp("InertSpeedMAX",buf)==0) cmd=3;
	if (cmd==0) return false;//Unknown Value
//	buf2=buf.substr(tst+1,buf.length());
	for(i=0;i<10;++i){
		if (buf2[i]==0) break;
	}
	if (i==10) return false;
//buf2=buf+i+1;
//return false;
	switch(cmd){

	case 1:
		if (strcmp("default",buf2)==0)
			engList[ind].Inertion=0;
		else
			engList[ind].Inertion=atof(buf2);
		break;
	case 2:
		if (strcmp("default",buf2)==0)
			engList[ind].InertSpeedSTEP=0;
		else
			engList[ind].InertSpeedSTEP=atof(buf2);
		break;
	case 3:
		if (strcmp("default",buf2)==0)
			engList[ind].InertSpeedMAX=0;
		else
			engList[ind].InertSpeedMAX=atof(buf2);
		break;
	default:
		return false;
		break;
	}
return true;
}

void pEngine::InitEngineList(){

	//float k1=300.0f,k2=500.0f,k3=1.0f;
//	if (fast)	{
//		k1=2.0f;
//		k2=3.5f;
//		k3=0.5f;
//	}

	for (int i=1;i<10;i++){// "нулевой" индекс для не движущихся объектов!
//		engList[i].inertSpeed.d_time=&d_time;
//		if (engList[i].Inertion){
//			engList[i].inertX.SetSteepness(engList[i].Inertion);
//			engList[i].inertZ.SetSteepness(engList[i].Inertion*2.0f);
//		}else{
			engList[i].inertX.SetAcceleration(0.01745f/2.0f/5.0f,10);
			engList[i].inertZ.SetAcceleration(0.01745f/5.0f,10);//11.67
			engList[i].inertY.SetAcceleration(0.01745f/5.0f,10);
//		}
		float step=50.0f;//1750.0f;
		float mxm=100.0f+i/10.0f;//!!!!
//		if (engList[i].InertSpeedSTEP){
//			step=engList[i].InertSpeedSTEP;
//		}
//		if (engList[i].InertSpeedMAX){
//			mxm=engList[i].InertSpeedMAX;
//		}
		engList[i].inertSpeed.SetAcceleration(1,10);
	}
}
float pEngine::GetDeltaTime(){
	return fpDeltaTime;
}
void pEngine::Processing(){//float dt){

	dLastTime=dCurTime;
	dCurTime=::GetTickCount();
	fpDeltaTime=(dCurTime-dLastTime)/1000.0f;// 0.020
//	10 < fpDeltaTime < 30
	if (bGameOver) return;

	if (this->fpDeltaTime>0.03f) return; // 33.3 FPS
	if (this->fpDeltaTime<0.015f) return;// 66.6 FPS

	AssemblyRubbish();
	Collisions();

	//ProcessClients();//Вызывать не чаще 20 раз в сек. Как?!?

//	DWORD cur_time=GetTickCount();
//	Calculate();
//if ((cur_time-timers<1000)||(steps))
//if (steps)
//{
	Rotatings();
	Movings();
//}
}
/*
void pEngine::SetAllObj(D3DXVECTOR3 pos){
	std::list< boost::intrusive_ptr<tObj> >::iterator i=objList.begin();
	(*i)->pos=pos;// camera!!
	while(++i!=objList.end()){
		(*i)->pos-=pos;
	}
	i=virtObjList.begin();
	while(i!=virtObjList.end()){
		(*i)->pos-=pos;
		i++;
	}
}
*/
void pEngine::CalcNextPos(){}

bool pEngine::Calculate(boost::intrusive_ptr<tObj> center){

	if (objList.size()<2) return false;
	WaitForSingleObject(hObjList,INFINITE);
	std::list< boost::intrusive_ptr<tObj> >::iterator i=objList.begin();
	while(i!=objList.end()){
		if (center==(*i)) break;
		++i;
	}
	if (i!=objList.end()){
//		objList.swap(i,objList.begin());
		objList.erase(i);
		objList.push_front(center);
		ReleaseMutex(hObjList);
		this->Calculate();
		return true;
	}
	ReleaseMutex(hObjList);
	return false;
}

void pEngine::Calculate(){
//---расчет координат всех объектов относительно камеры
	D3DXVECTOR3 tmp_v;
	float tmp_f=0;

	std::list< boost::intrusive_ptr<tObj> >::const_iterator i=objList.begin();
	D3DXVECTOR3 pos=(*i)->pos;
	if (D3DXVec3Length(&pos)>1000.0f){
		WaitForSingleObject(hObjList,INFINITE);
		(*i)->pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
		while(++i!=objList.end()){
			(*i)->pos-=pos;
			if ((*i)->radius<10.0f){//корабль
				tmp_v=(*i)->pos;
				tmp_f=D3DXVec3Length(&tmp_v);
				float r=(*i)->radius;
				if (tmp_f>10000.0f){//вышел за пределы видимости !!
					(*i)->mustDestroy=true; // !!!!!!!abcdef
				}
			}
		}
		ReleaseMutex(hObjList);

		i=virtObjList.begin();
		while(i!=virtObjList.end()){
			(*i)->pos-=pos;
			i++;
		}
	}
	std::list< boost::intrusive_ptr<tFormations> >::iterator tF=
		formationsObjList.begin();
	while (tF!=formationsObjList.end()){
		(*tF)->obj->pos=(*tF)->home->pos+(*tF)->delta;
		(*tF)->obj->inertSpeed.curValue=(*tF)->home->inertSpeed.curValue;
		(*tF)->obj->tx=(*tF)->home->tx;
		(*tF)->obj->ty=(*tF)->home->ty;
		(*tF)->obj->tz=(*tF)->home->tz;
		tF++;
	}
}
void pEngine::Collisions(){
	float delta=0;
	float r1=0;
	float r2=0;
	float pow=0;
	bool dead=false;
	int n1=0,n2=0;
	D3DXVECTOR3 tmp_v;
	std::list< boost::intrusive_ptr<tObj> >::const_iterator i,ii,beg,end;
WaitForSingleObject(hObjList,INFINITE);
	beg=objList.begin();
	end=objList.end();
//проверка на столкновения
	bool md=false;
	for(i=beg;i!=end;++i){
		if ((*i)->mustDestroy) {continue;}
		n1=(*i)->GetIdGroup();
		r1=(*i)->radius;
		md=(*i)->bExplosive;
		if (md){
			int debug=0;
		}
		for(ii=i;ii!=end;++ii){//пропускаем самого себя
			if (i==ii) continue;
			if ((*ii)->mustDestroy) continue;
//			if ((*ii)->bExplosive) continue;//пропускаем мины (мина - на мину)//НЕ ПРОПУСКАТЬ! если мина-посл.объект,то она тогда не обработается!
			n2=(*ii)->GetIdGroup();
			tmp_v=(*i)->pos-(*ii)->pos;
			delta=D3DXVec3Length(&tmp_v);
			r2=(*ii)->radius;
			if (delta<r1+r2){//проверка на столкновение
//				проверяем и уничтожаем из за столкновения
//					if ((r1<100.0f)&&(r1*5.0f<r2)){// пропускаем крупные объекты: станцию,планету,звезду и т.п. а также объекты 5 кратно крупнее
				if (r1<=r2*3.0f){// пропускаем объекты 3 кратно крупнее
//						if (i!=objList.begin()) // DEBUG (skip camera)
						(*i)->mustDestroy=true;
						if (i==beg){
							int b=0;
						} // DEBUG (skip camera)
					objChange=true;//********************************
				}
//					if ((r2<100.0f)&&(r2*5.0f<r1))// пропускаем крупные объекты: станцию,планету,звезду и т.п.а также объекты 5 кратно крупнее
				if (r2<=r1*3.0f){// пропускаем объекты 3 кратно крупнее
//						if (ii!=objList.begin()) // DEBUG (skip camera)
					(*ii)->mustDestroy=true;
					if (i==beg){
						int a=0;
					} // DEBUG (skip camera)
					objChange=true;//********************************
				}
			}
// Проверка на взрывающиеся объекты:
			if (n1==0) continue; //пропускаем НЕ корабли
			if (n2==0) continue; //пропускаем НЕ корабли
			if (((*ii)->bExplosive)&&((*i)->bExplosive)) continue;//пропускаем мины (мина - на мину)
			r1=(*i)->radius; r2=(*ii)->radius;
			if ((*i)->bExplosive){//проверка на мины (взрывающиеся объекты)
				r1=(*i)->GetExplRad();
				if (delta<r1+r2){
					if (n1==n2) {
	   					(*i)->bExplFriend=true;
					}else{
						(*i)->bExplEnemy=true;
					}
				}
			}
			r1=(*i)->radius; r2=(*ii)->radius;
			if ((*ii)->bExplosive){//проверка на мины (взрывающиеся объекты)
				r2=(*ii)->GetExplRad();
				if (delta<r1+r2){
					if (n1==n2) {
	   					(*ii)->bExplFriend=true;
					}else{
						(*ii)->bExplEnemy=true;
					}
				}
			}

		}//for(ii=i;ii!=end;++ii){//пропускаем самого себя
	}// for(i=beg;i!=end;++i){

	for(i=beg;i!=end;++i){
		if ((*i)->mustDestroy) continue;
		if ((*i)->bExplosive==false) continue;// ищем мины
		if ((*i)->bExplEnemy==true){//мина инициирована?
			if ((*i)->bExplFriend==true) {
//				(*i)->bExplEnemy=false;//не надо! Мина должна взорваться в любом случае,если прошла ее инициализация
				(*i)->bExplFriend=false;
				continue;
			}else{//взрываем мину
				n1=(*i)->GetIdGroup();
				r1=(*i)->GetExplRad();
				for(ii=beg;ii!=end;++ii){
					if (i==ii) continue;//пропускаем самого себя
					if ((*ii)->bExplosive) continue;//пропускаем мины (мина - на мину)
					if ((*ii)->mustDestroy) continue;
	// наносим повреждения окружающим объектам:
					n2=(*ii)->GetIdGroup();
					if (n2==0) continue; //пропускаем НЕ корабли
					r2=(*ii)->radius;

					tmp_v=(*i)->pos-(*ii)->pos;
					delta=D3DXVec3Length(&tmp_v);

					if (delta<r1+r2){
						if (n1==n2){
							int err=0;//не должно быть такого!
						}
						pow=(*i)->GetExplPower();
						dead=(*ii)->Hit(pow);
						if (dead) {
							(*ii)->mustDestroy=true;
							objChange=true;//********************************
						}
					}
				}
				(*i)->mustDestroy=true;//уничтожаем только после проверки ВСЕХ объектов,т.к.может задеть несколько кораблей
			}//}else{//взрываем мину
		}
	}
	ReleaseMutex(hObjList);
}
bool pEngine::CheckCollision(boost::intrusive_ptr<tObj> myObj){
D3DXVECTOR3 pos,tz,delta;
float dist=0,ro=0,res=0,r=0;

if (!myObj) return false;
if (myObj->mustDestroy) return false;

	std::list< boost::intrusive_ptr<tObj> >::const_iterator i,beg,end;

	pos=myObj->pos;// ->GetPos();
	tz=myObj->tz;
	r=myObj->radius;// >GetRadius();

	WaitForSingleObject(hObjList,INFINITE);
	beg=objList.begin();
	end=objList.end();

//проверка на столкновения
	for(i=beg;i!=end;++i){
		if ((*i)->mustDestroy) {
			continue;
		}
		if ((*i)==myObj){//пропускаем самого себя
			continue;
		}
		delta=pos+tz*30.0f-(*i)->pos;
		dist=D3DXVec3Length(&delta);
		ro=(*i)->radius;// >GetRadius();
		res=r+ro;
		if (fabsf(res)>fabsf(dist)){
			ReleaseMutex(hObjList);
			return true;//(*allShips)->status.SetStatus(9);
		}
	}
	ReleaseMutex(hObjList);
	return false;
}
boost::intrusive_ptr<tObj> pEngine::CheckCollisionBigObj(boost::intrusive_ptr<tObj> myObj){
	boost::intrusive_ptr<tObj> retO=0;
D3DXVECTOR3 pos,tz,delta;
float dist=0,ro=0,res=0,r=0;

if (!myObj) return false;
if (myObj->mustDestroy) return false;

	std::list< boost::intrusive_ptr<tObj> >::const_iterator i,beg,end;

	pos=myObj->pos;// ->GetPos();
	tz=myObj->tz;
	r=myObj->radius;// >GetRadius();

	WaitForSingleObject(hObjList,INFINITE);
	beg=objList.begin();
	end=objList.end();

//проверка на столкновения
	for(i=beg;i!=end;++i){
		if ((*i)->mustDestroy) {
			continue;
		}
		if ((*i)==myObj){//пропускаем самого себя
			continue;
		}
		
		ro=(*i)->radius;// >GetRadius();
		if (ro>r*5.0f) break; // пропускаеи объекты 5 кратно больше
		delta=pos+tz*30.0f-(*i)->pos;
		dist=D3DXVec3Length(&delta);
		res=r+ro;
		if (fabsf(res)>fabsf(dist)){
			ReleaseMutex(hObjList);
			return (*i);//(*allShips)->status.SetStatus(9);
		}
	}
	ReleaseMutex(hObjList);
	return retO;
}

void pEngine::Movings(){
	float tmpSpeed=0;
	std::list< boost::intrusive_ptr<tObj> >::const_iterator i,end;
	WaitForSingleObject(hObjList,INFINITE);
	for(i=objList.begin(),end=objList.end();i!=end;++i){
		tmpSpeed=(*i)->inertSpeed.GetCurValue(fpDeltaTime);//deltaTime);
		if (tmpSpeed!=0){
			int debug=0;
		}
		(*i)->pos+=(*i)->tz*tmpSpeed;
	}
	ReleaseMutex(hObjList);
}
void pEngine::Rotatings(){
// напоминание: для правильной инерции obj->inertPrediction() должна вызываться всегда!
	std::list< boost::intrusive_ptr<tObj> >::const_iterator i,end;
	D3DXMATRIX m1;
int debug=0;
	WaitForSingleObject(hObjList,INFINITE);
	for(i=objList.begin(),end=objList.end();i!=end;++i){
//		if ((*i)->radius>50.0f) continue;
		int u=(*i)->GetUin();
		if (u==41000){
			debug=1;
		}
		(*i)->inertZ.InertPrediction();//предсказание-prediction.Необходимо задать obj->inert.Value
//		float zz=(*i)->inertZ.Value;
		D3DXMatrixIdentity(&m1);
		D3DXMatrixRotationAxis(&m1,&(*i)->tz,(*i)->inertZ.GetCurValue(fpDeltaTime));
		D3DXMatrixMultiply(&(*i)->m,&(*i)->m,&m1);
		D3DMath_VectorMatrixMultiply( (*i)->tx,(*i)->tx,m1);
		D3DMath_VectorMatrixMultiply( (*i)->ty,(*i)->ty,m1);

		(*i)->inertX.InertPrediction();
		D3DXMatrixIdentity(&m1);
		float ix=(*i)->inertX.GetCurValue(fpDeltaTime);
		if (ix!=0){
			int debug=1;
		}
		D3DXMatrixRotationAxis(&m1,&(*i)->tx,ix);
		D3DXMatrixMultiply(&(*i)->m,&(*i)->m,&m1);
		D3DMath_VectorMatrixMultiply( (*i)->tz,(*i)->tz,m1);
		D3DMath_VectorMatrixMultiply( (*i)->ty,(*i)->ty,m1);

		(*i)->inertY.InertPrediction();
		D3DXMatrixIdentity(&m1);
		D3DXMatrixRotationAxis(&m1,&(*i)->ty,(*i)->inertY.GetCurValue(fpDeltaTime));
		D3DXMatrixMultiply(&(*i)->m,&(*i)->m,&m1);
		D3DMath_VectorMatrixMultiply( (*i)->tx,(*i)->tx,m1);
		D3DMath_VectorMatrixMultiply( (*i)->tz,(*i)->tz,m1);
	}
	if (debug==0){
		bool error=1;
	}
	ReleaseMutex(hObjList);
}
/*
void tWorld::CalcAllObj(D3DXVECTOR3 pos){
// добавить обработку расстояния до звезды: для ручного перелета от звезды к звезде

	m_Galaxy.m_Star->pos-=pos;//Солнце

	D3DXVECTOR3 delta=D3DXVECTOR3(0,0,0);
	float dist=0,max=500000;
	std::list< boost::intrusive_ptr<tPlanet> >::iterator tmpP;
	tmpP=m_Galaxy.m_Star.m_Planets.begin();
	tWorld::curPlanet=(*tmpP);
	for(;tmpP!=m_Galaxy.m_Star.m_Planets.end();tmpP++){
		(*tmpP)->pos-=pos;//cam->pos;
		delta=cam->pos-(*tmpP)->pos;
		dist=D3DXVec3Length(&delta);
		if (dist<max){
			max=dist;
			tWorld::curPlanet=(*tmpP);
		}
		if ((*tmpP)->m_Station){
			(*tmpP)->m_Station->pos-=pos;//cam->pos;
			(*tmpP)->m_Station->pointOfHyperJamp->pos-=pos;//cam->pos;
		}
	}

}
*/


void pEngine::Clear(){
//	boost::intrusive_ptr<tObj> cam=objList.pop_front();
	WaitForSingleObject(hObjList,INFINITE);
	objList.clear();
	ReleaseMutex(hObjList);
	virtObjList.clear();
}

bool pEngine::ObjEvents(){
	if (objChange) {
		objChange=false;
		return true;
	}
	return false;
}
int pEngine::ServerSendData(){//Server Formating Data for Send to Clients

//	ASSERT(archive_stream.str().empty()); !!!
//	os << BOOST_SERIALIZATION_NVP(tmp);//TEST если нет объектов, то сериализация не срабатыват!
	tServiceInfo tmpSI;
	tmpSI.mode=1;
	WaitForSingleObject(hObjList,INFINITE);
	std::list< boost::intrusive_ptr<tObj> >::iterator i=objList.begin();
	std::list<tSendData> sendList;
	tSendData tmp;
//	sendList.push_back(tmp);// фиктивный объект, чтобы список не был пустым
	int count=0;
// добавить пропуск клиентов,которые находятся на станции ?
	while(i!=objList.end()){
			tmp.pos=(*i)->GetPos();
			tmp.dir=(*i)->tz;
			tmp.up=(*i)->ty;
			tmp.uin=(*i)->uin;
			tmp.radius=(*i)->radius;
			if ((*i)->radius<10){ //!!!!
				sendList.push_back(tmp);
				count++;
			}
		++i;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//archive_stream.str("");
	//boost::archive::text_oarchive os(archive_stream);
	//os << BOOST_SERIALIZATION_NVP(tmpSI);
	//os << BOOST_SERIALIZATION_NVP(sendList);
	ReleaseMutex(hObjList);
	return count;
}

// получаем буфер с нажатыми клавишами от клиента
// (переделал,теперь у клиента персональный буфер)
//void pEngine::ProcessClients(){
////return;//!!!!!!!!!!!!!!!!!!!!!!!!
////	WaitForSingleObject(hClients,500);//сделать массив и ждать MultipleObj
//	WaitForSingleObject(hObjList,500);
////	memcpy(&srvMsg,buf,szSI);
////	srvMsg.dwServerTime=::GetTickCount();//сделать блокировку DDoS от клиентов
//	tServiceInfo *srvMsg=0;
//
//	return;
//
//	for (int i=0;i<5;i++){
//		srvMsg=(tServiceInfo *)&mClients[i].buf[0];
//	}
//	// 1.найти клиента по УИНу
//int tmpUIN=0,clientUIN=0;
//	std::list< boost::intrusive_ptr<tObj> >::iterator i=objList.begin();
//	while(i!=objList.end()){
//		if ((*i)->radius<10){ //!!!!
//			tmpUIN=(*i)->uin;
//			if (tmpUIN==clientUIN){
//				break;
//			}
//		}
//		++i;
//	}	
//	ReleaseMutex(hObjList);
//	ReleaseMutex(hClients);

// 2.эмулировать нажатие клавиш
//	this->ProcessKeyEmulation((*i),buf);
//}
//void pEngine::ProcessKeyEmulation(boost::intrusive_ptr<tObj> tmpObj,const char* buf){
//	if(buf[79]){
//		//printf ("key press");
//		tmpObj->inertZ.Value=0.10f;}//VK_DOWN]){//o
//	if(buf[80]){tmpObj->inertZ.Value=-0.10f;}//VK_DOWN]){//p
//}


void pEngine::AssemblyRubbish(){

// mustDestroy тоже отработать ????

	WaitForSingleObject(hObjList,INFINITE);
	std::list< boost::intrusive_ptr<tObj> >::iterator i=objList.begin();
	while(i!=objList.end()){
		int u=(*i)->GetUin();
		if ((*i)->m_refCounter<2){
			i=objList.erase(i);
//			objChange=true;//********************************????????????
		}else{
			i++;
		}
	}
	ReleaseMutex(hObjList);
	i=virtObjList.begin();
	while(i!=virtObjList.end()){
		if ((*i)->m_refCounter<2){
			i=virtObjList.erase(i);
		}else{
			i++;
		}
	}
/*
	std::list< boost::intrusive_ptr<tFormations> >::iterator ii=
		formationsObjList.begin();
	while(ii!=formationsObjList.end()){
		if ((*ii)->home->mustDestroy){// удаление - ошибка!!!
//			ErasePointers((*ii)->home);
			ii=formationsObjList.erase(ii);
		}else{
			ii++;
		}
	}
*/
}

void pEngine::ChangePointsMaster(boost::intrusive_ptr<tObj> alt,
								 boost::intrusive_ptr<tObj> newObj){

	std::list< boost::intrusive_ptr<tFormations> >::iterator iAlt=
		formationsObjList.begin();
	while(iAlt!=formationsObjList.end()){
		if ((*iAlt)->home==alt) {
			(*iAlt)->home=newObj;
		}
		iAlt++;
	}
}
/*
void pEngine::ErasePointers(boost::intrusive_ptr<tObj> alt){

	std::list< boost::intrusive_ptr<tFormations> >::iterator iAlt=
		formationsObjList.begin();
	while(iAlt!=formationsObjList.end()){
		if ((*iAlt)->home==alt) {
			iAlt=formationsObjList.erase(iAlt);
//			break;// ??? к одному home не должно быть несколько привязок
		}else{
			iAlt++;
		}
	}
}
*/
/*
bool pEngine::SetMaxSpeed(float percent, boost::intrusive_ptr<tObj> tar){
	std::list< boost::intrusive_ptr<tObj> >::iterator i=objList.begin();
	while(i!=objList.end()){
		if ((*i)==tar){
			break;
		}
	}
	if (i==objList.end()){
		return false;
	}
//	tmpSpeed=(*i)->inertSpeed.GetCurValue();
//	(*i)->pos+=(*i)->tz*tmpSpeed;
//	if (curValue<maximum*0.3f) curValue=maximum*0.3f;

}
*/

bool pEngine::ErasePointsForGroup(int idGroup){
	std::list< boost::intrusive_ptr<tFormations> >::iterator iAlt=formationsObjList.begin();
	while(iAlt!=formationsObjList.end()){
		if ((*iAlt)->idGroup==idGroup) {
			iAlt=formationsObjList.erase(iAlt);
		}else{
			iAlt++;
		}
	}

return true;
}
