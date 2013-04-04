// tWorld.cpp: implementation of the tWorld class.
//
//////////////////////////////////////////////////////////////////////

#include "tWorld.h"
//#include "pEngine.h"
#include "tRender.h"

extern tRender my_render;
extern char g_diks[255];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tWorld::tWorld(){
	i_stream.str(&szTemp2[0]);// в конструкторе pEngine было
	mode=0;
	uin=0;
	szSI=sizeof(tServiceInfo);
	tickForStep.Stop();
	tick.Stop();
	//mCount.Init("tWorld StepCamera() stp");
}
tWorld::~tWorld(){}

void tWorld::Init(){
	tickForStep.Stop();
	tick.Stop();
		//mCount.WriteDump("tWorld::StepCamera stp:");

	//srvMsg.iUinClient=2010; // для тестирования только!

	bool fl=false;
	SDELog.WriteMessageLevelUp("Resource manager init start...");
	resManager.RMInit();
	SDELog.WriteMessageLevelDown("...End init Resource manager");
//SDELog.WriteMessageLevelUp("AI Global init start...");
//	aiGlobal.Init();
//SDELog.WriteMessageLevelDown("...End AI Global initialization");
SDELog.WriteMessageLevelUp("Goods LOAD start...");
	mGoods.Load();
SDELog.WriteMessageLevelDown("...End Goods loading");
SDELog.WriteMessageLevelUp("tComponents manager init start...");

//	mComp.Load();

SDELog.WriteMessageLevelDown("...End tComponents");
	
	SDELog.WriteMessage("");
//--------------------------------------------------
//	SDELog.WriteMessageLevelUp("Инициализация галактики ...");
//	mGalaxy.Init();// НЕ создает звезду и планеты!
//	SDELog.WriteMessageLevelDown("... завершена.");
//	SDELog.WriteMessage("");

//	int cStar=500;
//	SDELog.WriteMessage("Выбрана звездная система под номером: %d",cStar);
//	D3DXVECTOR3 starPos=mGalaxy.SelectStar(cStar);//Инициализация ВАЖНО!(Создает звезду и планеты) LOG????????????
//	SDELog.WriteMessage("Текущая позиция звезды: x=%.1f y=%.1f z=%.1f",starPos.x,starPos.y,starPos.z);

//	boost::intrusive_ptr<tObj> tmpObj=mGalaxy.aiStar->mStarContainer->GetPlanetWithStation();
//	if (tmpObj){
//		SDELog.WriteMessage("Координаты ближайшей планеты со станцией получены.");
//	}else{//ERROR
//		SDELog.WriteWarning("ВНИМАНИЕ! Не удалось получить координаты ближайшей планеты со станцией!");
//		int error=1;
//	}
	// Центруем объекты отностительно планеты
//	if (tmpObj) fl=pEng->Calculate(tmpObj);
//	if (fl){
//		SDELog.WriteWarning("Центровка объектов завершена.");
//	}else{
//		SDELog.WriteWarning("Ошибка центровки объектов!");
//	}

//	pEng->LoadEquipment();
//	pEng->InitEngineList();
//-----------------------------------------------
	// инициализация корабля-камеры !!
//	D3DXVECTOR3 newPos=D3DXVECTOR3(55000.0f,500.0f,-10000.0f);//in Sol system
	SDELog.WriteMessage("");
//	cam=boost::intrusive_ptr<tCamera> (new tCamera);
//	if (cam){
		SDELog.WriteMessage("Camera created.");
//	}else{
//		SDELog.WriteError("Camera NOT CREATED!!!");
//	}
	//cam->status=999;
	//tsWeapon weapon;
//	cam->Create(tmpObj->GetPos()+D3DXVECTOR3(50,50,500+100),pEng->mShip[0],pEng->mEngine[0],weapon);//Ships->mWeapon[0]);//In Station
	cam=boost::intrusive_ptr<tCamera> (new tCamera);
	cam->Create(D3DXVECTOR3(50,50,500+100));//Ships->mWeapon[0]);//In Station
	cam->curStar=0;//cStar;
//-----------------------------------------------
//	aiGlobal.Mission1();
	
	mMenu=tMenu(4);
	//inStation=tMenu(6);
	//trade=tMenu(mGoods.GetCount());
	//newShip=tMenu(4);
	//component=tMenu(5);//mComp.GetCount());

	mode=100;
}

void tWorld::Destroy(){
	resManager.RMDestroy();
//	m_Galaxy.Destroy();
}
void tWorld::SelComponents(int key){
	int sel=component.GetCurNum();
	if (key==VK_RIGHT){//покупка
/*		if (World.aiGlobal.cam->eqComp[sel]<World.aiGlobal.cam->Ship.eqTypesMax[World.mComp.units[sel].types]){
			if (cam->cash>World.mComp.units[sel].cost){
				cam->cash-=World.mComp.units[sel].cost;
				cam->eqComp[sel]++;
			}
		}*/
	}
	if (key==VK_LEFT){//продажа
		//if (cam->eqComp[sel]>0){
		//	cam->cash+=World.mComp.units[sel].cost;
		//	cam->eqComp[sel]--;
		//}
	}
}
void tWorld::MMenu(int key){
//	if (key==VK_ENTER){//выбор
}
void tWorld::Trade(int key){
	int sel=0;
	float delta=0,cost=0,amount=0;
//	char t=0;
//	if (key==VK_RIGHT){//покупка
//		sel=trade.GetCurNum()+trade.GetStartNum();
////	!!!		delta=aiGlobal.mGalaxy.aiStar->mStarContainer->mStar->goods[sel];//перенести в tGalaxy !!!
////	!!!		amount=aiGlobal.mGalaxy.aiStar->mStarContainer->mStar->amount[sel];
//		cost=mGoods.units[sel].cost*delta;
//		if ((cam->cash>cost)&&(amount>1)){
//			if (cam->Ship.tonnage>1){// проверить наличие свободного места !!!
//				cam->goods[sel]++;
////	!!!				aiGlobal.mGalaxy.aiStar->mStarContainer->mStar->amount[sel]--;
//				cam->cash-=cost;
//				if (mGoods.units[sel].meas[0]==116)
//					cam->Ship.tonnage--;
//			}
//		}
//	}
//	if (key==VK_LEFT){//продажа
//		sel=trade.GetCurNum()+trade.GetStartNum();
//		amount=cam->goods[sel];
//		if (amount>0){
////	!!!			aiGlobal.mGalaxy.aiStar->mStarContainer->mStar->amount[sel]++;
////	!!!			delta=aiGlobal.mGalaxy.aiStar->mStarContainer->mStar->goods[sel];//перенести в tGalaxy !!!
//			cost=mGoods.units[sel].cost*delta;
//			cam->goods[sel]--;
//			cam->cash+=cost;
//		}
//	}
}



//extern float fDeltaTime;

//DWORD lastTime=::GetTickCount();
void tWorld::RotateCameraX(bool fl){
	if (fl) cam->RotateX(0.01745f/2.0f);
	else cam->RotateX(-0.01745f/2.0f);
}
void tWorld::RotateCameraZ(bool fl){
	if (fl) cam->RotateZ(0.01745f*2.0f);
	else cam->RotateZ(-0.01745f*2.0f);
}

void tWorld::CDM(){
//			aiGlobal.cam->d_time=delta_time;
	int sel=0;
	std::list<tSendData> :: const_iterator _b;
	std::list<tSendData> :: const_iterator _e;
//	SDELog.WriteError("tWorld::CDM() mode=%d",aiGlobal.mode);
	switch (mode){
		case 1: // in Space
			_b=this->fObjList2.begin();
			_e=this->fObjList2.end();
			my_render.InSpaceMain(cam,_b,_e);//блокировать на это время работу со списком!!
//			SDELog.WriteError("");

//			if (my_render.Render()) {
//				cam->Processing(); //aiGlobal.Processing();
				//mGalaxy.aiStar->Processing();//вычисляет curPlanet!
				//Others->Processing();
				//pEng->Processing();
				this->Step();//pEng->Step();
				//this->StepCamera();//ручное управление камерой
				
//				input.ProcessInSpace();

//				DWORD curTime=::GetTickCount();
//				if (curTime-lastTime>400){
//					lastTime=curTime;
//					pEng->SwapNetworkBuffer();
//				}
//			}
			break;

		case 2: // Trade
			my_render.Trade(&trade);
//			sel=input.PrecessTrade(&trade);
//			if (sel==VK_BACK) mode=10;
//			Trade(sel);
			break;
		case 3: // Equipment Ship
//			my_render.SelComponents(&component);
//			sel=input.PrecessTrade(&component);
//			if (sel==VK_BACK) mode=10;
//			SelComponents(sel);
			break;
		case 4: // new Ship
			my_render.NewShip(&newShip);
//			sel=input.PrecessTrade(&newShip);
//			if (sel==VK_BACK){
//				mode=10;
//			}
			break;
		case 5: // Planet MAP
			my_render.PlanetMap();
//			if (input.ProcessPlanetMap()){
//				mode=10;
//			}
			break;
		case 10: // Main Menu in Station
//			SDELog.WriteMessage("Mode 10");
			my_render.InStationMain(&inStation);
//			if (input.ProcessInStation(&inStation)){
//				if (inStation.GetCurNum()==0){
//					mode=0;
//				aiGlobal.mode=0;
//				aiGlobal.DisconnectWithStation();					
//				aiGlobal.cam->obj->pos=D3DXVECTOR3(0.0f,0.0f,250.0f);
//				}
//				if (inStation.GetCurNum()==2) {mode=2;}
//				if (inStation.GetCurNum()==3) {mode=3;}
//				if (inStation.GetCurNum()==4) {mode=4;}
//				if (inStation.GetCurNum()==5) {mode=5;}
//			}
			break;
		case 100:
			if (this->_netStat){
				my_render.MainMenu(&mMenu,this->_netStat);
			}else{
				my_render.MainMenu();//нарисовать окно с ошибкой - "нет соединения с сервером!"
			}
			//if (input.ProcessMenu(&mMenu)){//теперь управление только через сервер!
			//	if (mMenu.GetCurNum()==0){mode=9;}//Почему? По меню, по идее,можно и с локальным управлением лазить.
			//	if (mMenu.GetCurNum()==4) {bGameOver=true;}//теоретически - да,но встаёт вопрос о безопасности
			//}// но можно попробовать вариант "наполовину" - вверх/вниз рулить локально, а активные действия-через сервер
			break;

		default:
			break;
	}
}
int tWorld::FormatDataForSend(char* buf){
	int sz=sizeof(int);
	memcpy(&buf[0],&g_diks[0],255);//слепок состояния клавы
	memcpy(&buf[0]+255,&this->mode,sz);
	memcpy(&buf[0]+255+sz,&this->uin,sz);
	return 255+sz+sz;
}


tCount mTcount;//????????



void tWorld::ClientReciveData(const char* buf,int len){

	return;

	if (len<sizeof(tServiceInfo))return;
	memset(&szTemp2[0],0,1024);
	memcpy(&szTemp2[0],buf,len);
//	std::string test(szTemp2);
//	i_stream.str(test);
//	std::stringstream tt(std::string(szTemp2,len));

//	std::ifstream tt(&szTemp2[0]);
	std::stringstream tt(&szTemp2[0]);
//	std::stringstream tt(buf);
//	if (len!=tt.str().length()) return;
//	tt.str().assign(szTemp2);

	boost::archive::text_iarchive os(tt);//i_stream);

	tServiceInfo tmpSI;
	
//	::WaitForSingleObject(hPeng,INFINITE);
	os >> tmpSI;
//	srvMsg.dwClientRecv=::GetTickCount();
//	srvMsg.dwClientSend=tmpSI.dwClientSend;
//	this->srvMsg=tmpSI;
//	this->netStat.AddTimeRecv(tmpSI.numPacket,tmpSI.dwServerWork);

// Анализ полученного пакета на основе служебной структуры "tServiceInfo"
	if (tmpSI.mode==100){//главное меню
		this->mode=100;
		int a=this->mode;
		this->uin=tmpSI.iUinClient;
		os >> mMenu; //получаем меню
		return;
	}
	if (tmpSI.mode==10){//главное меню
		this->mode=10;
		os >> this->inStation; //получаем меню
		os >> this->clientSMI;//информация для меню на станции
		return;
	}
	if (tmpSI.mode==1){//если в космосе летим
		this->mode=1;
		tSendData tmp;
		std::list<tSendData> recvList;
		std::list<tSendData>::const_iterator iRL;
		os >> recvList;
		iRL=recvList.begin();
		while(iRL!=recvList.end()){
			tmp=(*iRL);
			AddObjToFrame(&tmp);//добавить объект в frameObjList
			iRL++;
		}
		dFrameObjList=tick.GetTime();
		recvList.clear();
		AddNetworkObj();//добавить НОВЫЕ объекты из frameObjList в fObjList2
		return;
	}
	if (tmpSI.mode==200){//получаем координаты планет
		this->mode=200;
		os >> this->lBigObj;
	}
//	ReleaseMutex(hPeng);
}
float tStep=0,tStep2=0;
tTick StepTick;
//StepTick.Stop();
//добавить объект во frameObjList
void tWorld::AddObjToFrame(const tSendData* tmpObj){
	std::list< tSendData > ::iterator beg,end;

	beg=frameObjList.begin();
	end=frameObjList.end();
	int u=tmpObj->uin;
	
	while(beg!=end){
		if ((*beg).uin==u){
			if (u==2110){
				if (tmpObj->pos.x!=50){
					int debug=0;
				}
			}
			(*beg).dir=tmpObj->dir;
			D3DXVECTOR3 vv1=(*beg).up;
			D3DXVECTOR3 vv2=tmpObj->up;
			float vv3=vv1.x*vv2.x + vv1.y * vv2.y + vv1.z*vv2.z;
			//if (vv3>0.001f) tStep++;
			tStep2=tStep;
			tStep=1-vv3;
			mTcount.AddValue(tStep*1000.0f);
			StepTick.Wait();
			//if (mTcount.mcount>20){
			//	int debug=1;
			//}
			(*beg).up=tmpObj->up;
			(*beg).pos=tmpObj->pos;
			return;
		}
		++beg;
	}

	tSendData obj;
	obj.uin=u;
	obj.dir=tmpObj->dir;
	obj.up=tmpObj->up;
	obj.pos=tmpObj->pos;

	if (frameObjList.size()>50)	frameObjList.clear();// !!!!!!!!

	frameObjList.push_back(obj);
	return;
}
// проверка и добавление новых объектов из frameObjList во fObjList2
void tWorld::AddNetworkObj(){
//	::WaitForSingleObject(hPeng,INFINITE);
	std::list< tSendData > ::const_iterator beg,end,beg2,end2;
	if (frameObjList.size()>0){
		beg=frameObjList.begin();
		end=frameObjList.end();
		int u=0;
		while(beg!=end){
			beg2=fObjList2.begin();
			end2=fObjList2.end();
			u=(*beg).uin;
			while(beg2!=end2){
				if ((*beg2).uin==u){
					break;
				}
				++beg2;
			}
			if (beg2==end2){
					tSendData obj;
					obj.uin=u;// obj->SetUin(u);
					obj.dir=(*beg).dir;//obj->SetOrient((*beg)->tz,(*beg)->ty);
					obj.up=(*beg).up;
					obj.pos=(*beg).pos;
					fObjList2.push_back(obj);
			}
			++beg;
		}
	}
//	::ReleaseMutex(hPeng);
}
DWORD tWorld::GetTimeSleepNetwork(){
	if (this->mode==1) return 30;
	return 150;
}

void tWorld::StepCamera(){
	// за 100мСек вызовется 5(!) раз
	float dRenderTime=tickForStep.GetTime()-100.0f;
	float stp=(dObjList2-dRenderTime)/20.0f;
	
	int num=mCount.AddValue(stp);
	if (num<0)	bGameOver=true;

	if (stp<=0) {
		return; //потеря пакета
	}
	D3DXVECTOR3 tmp=D3DXVECTOR3(0,0,0);
	tmp=cam->objTest.dir-cam->obj.dir;
	cam->obj.dir=cam->obj.dir+tmp/stp;
	tmp=cam->objTest.up-cam->obj.up;
	cam->obj.up=cam->obj.up+tmp/stp;
}
// расчет промежуточного положения объектов между двумя буферами: frameObjList и fObjList2(рисуется)
//вызывается из CDM каждый тик (15<fDeltaTime<30 mSec)=(66<FPS<33)
void tWorld::Step(){
//	::WaitForSingleObject(hPeng,INFINITE);
//	DWORD res=::WaitForSingleObject(hPeng,1000);
//	if (res!=WAIT_OBJECT_0){/*ERROR*/}

	std::list< tSendData > ::iterator beg2,end2;
	std::list< tSendData > ::const_iterator beg,end;
	beg2=fObjList2.begin();
	end2=fObjList2.end();
	end=frameObjList.end();
	D3DXVECTOR3 v1,v2,v3,pos;
	float stp=0,deltaV=0,u1=0,u2=0;
	//DWORD dCurTime=GetTickCount();//Точность 10-15 мсек!!!
	float dRenderTime=tickForStep.GetTime()-75.0f;// dBackTime=50 mSec = 20 FPS
	stp=(dFrameObjList-dRenderTime)/20.0f;//fDeltaTime;// FPS<stp<0
	mCount.AddValue(stp);
	//if (mCount.mcount==198){
	//	int debug=0;
	//}
	if (stp<=0){
		return; //потеря пакета
	}

	while(beg2!=end2){// проходим по буферу
		beg=frameObjList.begin();
		v1=(*beg2).pos;
		u1=(*beg2).uin;
		while(beg!=end){// ищем в принятом буфере
			u2=(*beg).uin;
			if (u1==u2){//если находим

				v2=(*beg).pos;
				v3=v2-v1;
				deltaV=D3DXVec3Length(&v3);
				pos=v1+v3/stp;
				(*beg2).pos=pos;//(*beg).pos;//D3DXVECTOR3(pos.x,pos.y,pos.z);
				(*beg2).dir+=((*beg).dir-(*beg2).dir)/stp;
				(*beg2).up+=((*beg).up-(*beg2).up)/stp;
				if ((*beg2).uin==this->uin){// -= C A M E R A =-
					this->cam->obj.pos=(*beg2).pos;
					this->cam->obj.up=(*beg2).up;
					this->cam->obj.dir=(*beg2).dir;
				}
				break;
			}
			++beg;
		}
		++beg2;
	}

//	ReleaseMutex(hPeng);
}
