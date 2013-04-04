//tControl.cpp: implementation of the tControl class.
//
//////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN

#include "tControl.h"

#include <WinUser.rh>

//#include "tWorld.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//extern tWorld World;


tControl::tControl(){}

tControl::~tControl(){}

bool tControl::ProcessMenu(tMenu* menu,char* g_diks){
	if(g_diks[VK_DOWN]){
		menu->Next();
		g_diks[VK_DOWN]=0;
		return false;
	}
	if(g_diks[VK_UP]){
		menu->Prev();
		g_diks[VK_UP]=0;
		return false;
	}
	if(g_diks[VK_RETURN]){
		g_diks[VK_RETURN]=0;
		return true;
	}
	return false;
}

int tControl::PrecessTrade(tMenu* menu,char* g_diks){
	if(g_diks[VK_DOWN]){
		menu->Next();
		g_diks[VK_DOWN]=0;
		return false;
	}
	if(g_diks[VK_UP]){
		menu->Prev();
		g_diks[VK_UP]=0;
		return false;
	}
	if(g_diks[VK_LEFT]){
		g_diks[VK_LEFT]=0;
		return VK_LEFT;
	}
	if(g_diks[VK_RIGHT]){
		g_diks[VK_RIGHT]=0;
		return VK_RIGHT;
	}
	if (g_diks[VK_BACK]){
		g_diks[VK_BACK]=0;
		return VK_BACK;
	}
	return 0;
}
bool tControl::ProcessInStation(tMenu* menu,char* g_diks){
	if(g_diks[VK_DOWN]){
		menu->Next();
		g_diks[VK_DOWN]=0;
		return false;
	}
	if(g_diks[VK_UP]){
		menu->Prev();
		g_diks[VK_UP]=0;
		return false;
	}
	if(g_diks[VK_RETURN]){
		g_diks[VK_RETURN]=0;
		return true;
	}
	return 0;
}
bool tControl::ProcessPlanetMap(char* g_diks){
	if (g_diks[VK_BACK]){
		g_diks[VK_BACK]=0;
		return true;
	}
	return false;
}

void tControl::ProcessInSpace(char* g_diks){
/*
	if(g_diks[VK_INSERT]){
		pEng->timers=GetTickCount();
	}
	if(g_diks[VK_DELETE]){
		if (pEng->steps==true){
			pEng->steps=false;
		}else{
			pEng->steps=true;
		}
	}

	if(g_diks[87]){//VK_HOME]){//w
		World.cam->accel=0.005f;
//		engine->g_diks[VK_HOME]=0;
	}
	if(g_diks[83]){//VK_END]){//s
		World.cam->accel=-0.005f;
//		engine->g_diks[VK_END]=0;
	}

	if(g_diks[80]){//VK_RIGHT]){//p
			//World.cam->RotateZ(2.0f);
	}else{
		if(g_diks[79]){//VK_LEFT]){//o
			//World.cam->RotateZ(-2.0f);
		}else{
			//World.cam->RotateZ(0.0f);
		}
	}
*/
	if(g_diks[65]){//VK_DOWN]){//a
//			World.cam.RotateX(-2.0f);
	}else{
		if(g_diks[81]){//VK_UP]){//q
//			World.cam.RotateX(2.0f);
		}else{
//			World.cam.RotateX(0.0f);
		}
	}
	//if (g_diks[77]){ // "m" - stop DEBUG
	//	if (World.cam->bStop) World.cam->bStop=false;
	//	else World.cam->bStop=true;
	//	g_diks[77]=0;
	//}	
// **** Перебор Целей(кораблей) ****
	if (g_diks[VK_NUMPAD0]){/*
		boost::intrusive_ptr<tShipsInterface> _sI;
		_sI=World.aiGlobal.Ships->GetInterface();
		World.cam->New_Target(
			_sI->GetNextShip(World.cam->GetTargetObj()));
		g_diks[VK_NUMPAD0]=0;*/
	}
	//if (g_diks[VK_NUMPAD1]){
	//	World.cam->CleanTarget();
	//	g_diks[VK_NUMPAD1]=0;
	//}
// **** Стреляем ****
//------------------------
//	World.cam->Weapon.Reload();
//------------------------
	//if(g_diks[VK_SPACE]){
	//	World.cam->FireLaser();
	//	g_diks[VK_SPACE]=0;
	//}
}
/*
// **** Перебор планет ****
	if (engine->g_diks[VK_NUMPAD1]){
//		std::list<boost::intrusive_ptr<tPlanet> >::iterator tmpP;
		World.cam->tarPlanet=
			World.aiGlobal.mGalaxy.aiStar->mStarContainer->GetNextPlanet(
			World.cam->tarPlanet);
		engine->g_diks[VK_NUMPAD1]=0;
	}
	if (engine->g_diks[74]){ // "j"
		(World.cam->m_Jamp)?World.cam->m_Jamp=false:World.cam->m_Jamp=true;
		engine->g_diks[74]=0;
	}
//----------------------------------------------------------------------------------------------------------
	if(engine->g_diks[VK_LEFT]){
		int ind=World.curPos+World.mGoods.delta;
// добавить проверку на запрещенные товары
		if (World.mode==5){//продажа
			if (World.cam->goods[ind]>0){
				World.cam->cash+=World.mGoods.units[ind].cost+
					World.m_Galaxy.m_Star.goods[ind]*
					World.mGoods.units[ind].delta;
				World.cam->goods[ind]--;
				World.m_Galaxy.m_Star.amount[ind]++;
			}
		}
		if (World.mode==6){//оружие/оснащение
		}
		if (World.mode==0){
			World.cam->RotateZ(2.0f);
		}
	}
	if(engine->g_diks[VK_RIGHT]){
		int ind=World.curPos+World.mGoods.delta;
		float cost=0;
		if (World.mode==5){//покупка
			cost=World.mGoods.units[ind].cost+World.m_Galaxy.m_Star.goods[ind]*
					World.mGoods.units[ind].delta;
			if (World.cam->cash>=cost){
				if (World.m_Galaxy.m_Star.amount[ind]>1){
					World.cam->cash-=cost;
					World.cam->goods[ind]++;
				World.m_Galaxy.m_Star.amount[ind]++;
				}
			}
		}
		if (World.mode==6){//оружие/оснащение
		}
		if (World.mode==0){
			World.cam->RotateZ(-2.0f);
		}
	}
	if(engine->g_diks[VK_UP]){
		if (World.mode==5){
			if (World.curPos<1){
				World.curPos=0;
				if (World.mGoods.delta>0) World.mGoods.delta--;
			}else{
				World.curPos--;
			}
			engine->g_diks[VK_UP]=0;
		}
		if ((World.mode==6)||(World.mode==3)){//оружие/оснащение
			World.curPos--;
			if (World.curPos<1){
				World.curPos=0;
			}
			engine->g_diks[VK_UP]=0;
		}
		if (World.mode==0){
			World.cam->RotateX(2.0f);
		}
	}
	if(engine->g_diks[VK_DOWN]){
		if (World.mode==5){
			if (World.curPos>28){
				World.curPos=29;
				if (World.mGoods.delta<World.mGoods.GetCount()-30) World.mGoods.delta++;
			}else{
				World.curPos++;
			}
			engine->g_diks[VK_DOWN]=0;
		}
		if (World.mode==6){//оружие/оснащение
			World.curPos++;
			if (World.curPos>9){
				World.curPos=9;
			}
			engine->g_diks[VK_DOWN]=0;
		}
		if (World.mode==3){//на станции
			World.curPos++;
			if (World.curPos>5){
				World.curPos=5;
			}
			engine->g_diks[VK_DOWN]=0;
		}
		if (World.mode==0){
			World.cam->RotateX(-2.0f);
		}
	}
	if(engine->g_diks[VK_RETURN]){
		if (World.mode==3){
			if (World.curPos==0)	World.mode=3;//Ремонт
			if (World.curPos==1)	World.mode=5;//ТорговлЯ
			if (World.curPos==2)	World.mode=6;//Оснащение кораблЯ
			if (World.curPos==3)	World.mode=7;//Покупка нового кораблЯ
			if (World.curPos==4)	World.mode=3;//Карта Солнечной системы
			if (World.curPos==5)	World.mode=3;//Карта Галактики
		}
		World.curPos=0;
		engine->g_diks[VK_RETURN]=0;
	}
	if(engine->g_diks[VK_F3])
		if (World.cam->ofStation) {World.mode=3;World.curPos=0;}
		else World.mode=0;
// Включение/Выключение режима Планетарной Карты
	if(engine->g_diks[VK_F4])
		if (World.mode==0) World.mode=1;
// Включение/Выключение режима Галактической Карты
	if(engine->g_diks[VK_F5])
		if (World.mode==0) World.mode=2;
// гипер переход
	if (engine->g_diks[VK_F6]){
		if (World.mode==0){
			if (World.cam->target_star!=World.cam->curStar){
				World.mode=11;

				World.m_Galaxy.m_Star.Init(World.m_Galaxy.masOfGalaxy[World.cam->target_star].numOfPlanet,World.m_Galaxy.masOfGalaxy[World.cam->target_star].sUIN);

				World.cam->curStar=World.cam->target_star;
				hyper_ts=1.0f;

				World.cam->tarShip=0;
				World.cam->tarPlanet=0;
				World.freeShips.clear();
				World.cam->obj=0;
//				D3DXVECTOR3 newPos=(*tmpIterP)->m_Station->obj->GetPos()+D3DXVECTOR3(0.0f,0.0f,700.0f);
				pEng->Clear();
				World.warm=0;
				World.curPlanet=0;

				World.m_Galaxy.m_Star.Init(World.m_Galaxy.masOfGalaxy[World.cam->target_star].numOfPlanet,World.m_Galaxy.masOfGalaxy[World.cam->target_star].sUIN);

				World.cam->curStar=World.cam->target_star;

				std::list<boost::intrusive_ptr<tPlanet> >::iterator tp;
				tp=World.m_Galaxy.m_Star.m_Planets.begin();

				D3DXVECTOR3 newPos=(*tp)->obj->GetPos()-D3DXVECTOR3(0,0,3000.0f);
				World.cam->obj=pEng->CreateObj(0,0,10.0f,
					newPos,
					D3DXVECTOR3(1,0,0),
					D3DXVECTOR3(0,1,0),
					D3DXVECTOR3(0,0,1),
					true);				

//				World.CalcAllObj(pos);
//				World.cam->obj->GetPos()=D3DXVECTOR3(0.0f,0.0f,0.0f);
			}
		}
	}
// вылет со станции
	if(engine->g_diks[VK_F9]){
		World.cam->ofStation=false;
		if (World.mode==3) 
			World.mode=0;
		if (World.mode==5) 
			World.mode=0;
		if (World.mode==6) 
			World.mode=0;
	}	

	if(engine->g_diks[VK_F11]){
		if (World.warm==0){
			std::list<boost::intrusive_ptr<tObj> >::iterator iptr;
			iptr=World.points.begin();
			for (int i=0;i<5;i++){
				(*iptr)->GetPos()+=World.curPlanet->m_Station->obj->GetPos();
				iptr++;	
			}	
			World.warm=1;
//Создаем и настраиваем вражеский крейсер
			boost::intrusive_ptr<tShip> tmpShip(new tShip);
			tmpShip->Engine=World.mEngine[1];
			tmpShip->obj->GetPos()=D3DXVECTOR3(100,200,-3000.0f);
			tmpShip->status=1;
			tmpShip->obj->gRes=6;
			tmpShip->planet=World.curPlanet->obj;
			tmpShip->New_Target(World.curPlanet->m_Station->obj);
			World.freeShips.push_back(tmpShip);
		}
	}

	if (engine->g_diks[73]){//"i"
		(World.price)?World.price=false:World.price=true;
		engine->g_diks[73]=0;
	}
	if (engine->g_diks[107]){//+
		switch(World.mode) {
		case 1:
			World.m_PlanetMap.fPlanetMapY+=0.5f;
			break;
		case 2:
			World.m_GalaxyMap.fGalaxyMapY+=0.05f;
			break;
//		default:
		}
	}
	if (engine->g_diks[109]){//-
		switch(World.mode) {
		case 1:
			World.m_PlanetMap.fPlanetMapY-=0.5f;
			if (World.m_PlanetMap.fPlanetMapY<0.5f)
				World.m_PlanetMap.fPlanetMapY=0.5f;
			break;
		case 2:
			World.m_GalaxyMap.fGalaxyMapY-=0.05f;
			if (World.m_GalaxyMap.fGalaxyMapY<1.0f)
				World.m_GalaxyMap.fGalaxyMapY=1.0f;
			break;
//		default:
		}	
	}

// ******************************
	if (engine->g_diks[75]){ // "k" - активация/деактивация ракеты
		if (World.cam->tarShip){// если цель существует
			if (World.cam->tarShip->obj->mustDestroy==true){
				World.cam->tarShip=0;
				World.cam->missileEnable=false;
//				World.cam->missileLockTimer=0;
				World.cam->missileLock=false;
			}else{// если корабль не должен быть уничтожен
				if (World.cam->missileEnable){
					World.cam->missileEnable=false;
//					World.cam->missileLockTimer=0;
					World.cam->missileLock=false;
				}else{
					World.cam->missileEnable=true;
					World.cam->missileLockTimer=GetTickCount();
					World.cam->missileLock=false;
				}
		}	}
		
		engine->g_diks[75]=0;
	}
	if (engine->g_diks[76]){ // "l" - запуск ракеты
		if (World.cam->missileLock){//если цель захвачена
			World.LaunchMissile();
			World.cam->missileEnable=false;
//					World.cam->missileLockTimer=0;
			World.cam->missileLock=false;
		}
		engine->g_diks[76]=0;
	}
	if(engine->g_diks[192]){
		(engine->Console->Visible)?engine->Console->Visible=false:engine->Console->Visible=true;
		engine->g_diks[192]=0;
	}
	if (*(engine->lbmousedown)==true){
		if (World.mode==2){
			// поиск звезды
			float hyper_len=10000.0f;
			World.cam->posOfCur=D3DXVECTOR3(engine->i_cu->x,engine->i_cu->y,0.0f);
			D3DXVECTOR3 posCur=World.cam->posOfCur;
			D3DXVECTOR3 posOfStar=D3DXVECTOR3(0,0,0);
			D3DXVECTOR3 tpos1=D3DXVECTOR3(0,0,0);
			D3DXMATRIX mWorld,mProj,mView;
			D3DXMatrixIdentity(&mWorld);
			float Scrx=engine->GetRenderWidth();
			float Scry=engine->GetRenderHeight();
			D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI/2, Scrx/Scry, 0.0f, 500.0f);
			D3DXMatrixLookAtLH (&mView, 
				&D3DXVECTOR3 (0.0f, 0.0f,-World.m_GalaxyMap.fGalaxyMapY), 
				&D3DXVECTOR3 (0.0f, 0.0f, 0.0f), 
				&D3DXVECTOR3 (0.0f, 1.0f, 0.0f));

			posCur.z=1.0f;
			for (int i=0;i<World.m_Galaxy.num_of_stars;i++){
				posOfStar=World.m_Galaxy.v_galaxy[i].pos;
				D3DMath_VectorMatrixMultiply(posOfStar,posOfStar,mWorld);
				D3DMath_VectorMatrixMultiply(posOfStar,posOfStar,mView);
				D3DMath_VectorMatrixMultiply(posOfStar,posOfStar,mProj);
				// нужна инверсия по Y !!!
				posOfStar.x=(posOfStar.x+1.0f)*Scrx/2.0f;
				posOfStar.y=Scry-(posOfStar.y+1.0f)*Scry/2.0f;
				//posOfStar.y/=Scrx/Scry;
				tpos1=posOfStar-posCur;
				if (D3DXVec3Length(&tpos1)<hyper_len){
					hyper_len=D3DXVec3Length(&tpos1);
					World.cam->target_star=i;
				}
			}
		}
	}
*/

