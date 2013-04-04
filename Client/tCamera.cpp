// tCamera.cpp: implementation of the tCamera class.
//
//////////////////////////////////////////////////////////////////////

#include "tCamera.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tCamera::tCamera()//:tEquipment(s)
{	//d_time=0;
	cash=500;
	speed=0.1f;
	accel=0;
	m_Jamp=false;
	aZ=aX=0.0f;
	float max=200.0f*1.0f;
	stpnsX=0.01745f;//0.002f/max*1.0f;
	stpnsZ=stpnsX*2.0f;
	stpnsZmax=stpnsZ*max;
	stpnsXmax=stpnsX*max;
	curStar=0.0f;
	tarPlanet=0;
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
//	target_star=0;
	bStop=false;
//	ofStation=true;
//	for (int i=0;i<10;i++)	masWeapon[i]=false;
//	missileEnable=false;
//	missileLock=false;
//	missileLockTimer=0;
	ZeroMemory( &goods, sizeof(goods) );
//	right=D3DXVECTOR3(1,0,0);
	obj.dir=D3DXVECTOR3(0,0,1);
	obj.up=D3DXVECTOR3(0,1,0);
}

tCamera::~tCamera()
{//!!!!!!!!!!!!!!!!!! обработать !!!!!!!!!!!!!!!!!!!!!
// 		brnd=true;//для появления пиратов 
}

// void tCamera::SetCurMatrix(D3DXMATRIX matrix){
	//obj->m=matrix;
//}
 //D3DXVECTOR3 tCamera::GetTx(){obj->tx;}

// D3DXVECTOR3 tCamera::GetTy(){
//	return obj.up;//obj->ty;
//}
// D3DXVECTOR3 tCamera::GetTz(){
//	return obj.dir;//obj->tz;
//}

void tCamera::RotateZ(float angl){
// пояснения см.в RotateX
	//if (fabsf(aZ)<=stpnsZ) aZ=0.0f;
	//
	//if (angl==0.0f) {
	//	if (aZ>0) aZ-=stpnsZ;//angl=-0.50f;
	//	if (aZ<0) aZ+=stpnsZ;//angl=+0.50f;
	//}else{
	//	if (angl<0) aZ-=stpnsZ*2.0f;//angl=-0.50f;
	//	if (angl>0) aZ+=stpnsZ*2.0f;//angl=+0.50f;
	//}
	//
	//if (aZ>stpnsZmax) aZ=stpnsZmax;// Verify Max
	//if (aZ<-stpnsZmax) aZ=-stpnsZmax;//Verify Min
	D3DXVECTOR3 right=D3DXVECTOR3(0,0,0);
	D3DXVec3Cross(&right,&objTest.up,&objTest.dir);

		D3DXMATRIX m1;
		D3DXMatrixIdentity(&m1);
		D3DXMatrixRotationAxis(&m1,&objTest.dir,angl);
		D3DMath_VectorMatrixMultiply( right,right,m1);
		D3DMath_VectorMatrixMultiply( objTest.up,objTest.up,m1);
}

void tCamera::RotateX(float angl){
// Стабилизирующая ф-ция инерции:
//если угол вращения меньше шага вращения(погрешность) сбрасываем угол
//	if (fabsf(aX)<=stpnsX) aX=0.0f;
// если камера не вращается,необходимо стабилизировать вращение
	//if (angl==0.0f) {
	//	if (aX>0) aX-=stpnsX;//angl=-0.50f;
	//	if (aX<0) aX+=stpnsX;//angl=+0.50f;
	//}else{
	//	if (angl<0) aX-=stpnsX*2.0f;//angl=-0.50f;
	//	if (angl>0) aX+=stpnsX*2.0f;//angl=+0.50f;
	//}
	//if (aX>stpnsXmax) aX=stpnsXmax;// Verify Max
	//if (aX<-stpnsXmax) aX=-stpnsXmax;//Verify Min
	D3DXVECTOR3 right=D3DXVECTOR3(0,0,0);
	D3DXVec3Cross(&right,&objTest.up,&objTest.dir);

	D3DXMATRIX m1;
	D3DXMatrixIdentity(&m1);
	D3DXMatrixRotationAxis(&m1,&right,angl);//aX*fDeltaTime*1000.0f);
	D3DMath_VectorMatrixMultiply( objTest.dir,objTest.dir,m1);
	D3DMath_VectorMatrixMultiply( objTest.up,objTest.up,m1);
}
float tCamera::GetSpeedPercent(){
	if (speed==0) return 0;
	return speed/0.1f*100.0f;
}
void tCamera::Move(){
	speed=(speed+accel);//*d_time;
	
	if (speed>0.5f) {speed=0.5f;accel=0;}
//	if (speed<0.01f) {speed=0.01f;accel=0;}

	if (bStop){speed=0.0f;accel=0;}
	
	obj.pos+=obj.dir*speed;
	if (m_Jamp){
//		obj->pos+=obj->tz*10.0f;
	}
	accel=0;
//	if (accel!=0.0f){
//		if (accel>0) accel-=0.01f;
//		else accel+=0.01f;
//	}
//	if (fabsf(accel)<0.02f) accel=0.0f;
}

//void tCamera::CInit(tShotsMngr* m){
//	tEquipment::ShMngr=m;
//}
/*
void tCamera::Fire(){
	if (timerw<=0){
		tShots tmp;
		tmp.pos=pos;
		tmp.tz=tz;
		ShMngr->AddShot(&tmp);
		timerw=1000.0f;
	}
}
*/
/*
void tCamera::Processing(){

	if (energy<100.0f) energy+=0.01f;
	if (IsFire()) energy-=Weapon.FireNow();
//	if (energy>0) energy-=Weapon.FireNow();


//	Claculate();
//	obj->m=matView;

	//Move();

	//if (tEquipment::target)
	//	if (tEquipment::target->mustDestroy){
	//		tEquipment::target=0;
	//}



//	if (Weapon.timerw>0) Weapon.timerw-=1.0f;
//	if (Weapon.power_weapon>0) Weapon.power_weapon-=1.0f;



//	if (missileEnable){//ракета активирована
		//теперь требуется удержать цель в течении 5 сек.
		// дистанция действия ракеты ???
//		if (!missileLock){
//			if (GetTickCount()-missileLockTimer>5000) {
//				missileLock=true;
//			}
//		}
//	}
	
}
*/

void tCamera::Create(D3DXVECTOR3 pos){
	SDELog.WriteMessage("tCamera: Create()");
	obj.pos=pos;
}

//void tCamera::Create(D3DXVECTOR3 pos,tsShip ship,tsEngine engine, tsWeapon weapon){
//	obj=pEng->CreateObj(0,1,pos,0,10,1,true);
//	if (obj){
//		SDELog.WriteMessage("tCamera: Create Obj successfull");
//	}else{
//		SDELog.WriteError("Cant create tCamera Obj!!!");
//	}
//	SDELog.WriteMessage("Set camera idGroup=1");
//	Ship=ship;
//	Engine=engine;
//	Weapon=weapon;
//	for(int i=0;i<30;++i) eqComp[i]=0;
//	SDELog.WriteMessage("Ends camera create.");
//}

//void tCamera::Claculate(){
//	if (target){
//		D3DXVECTOR3 pos=obj->GetPos();
//		D3DXMATRIX inv,matWorld;
//		D3DXMatrixIdentity(&inv);
//		D3DXMatrixIdentity(&matWorld);
//
//	//востанавливаем мировую матрицу
//matWorld=matView;
//		D3DXMatrixTranslation(&inv,pos.x,pos.y,pos.z);
//		D3DXMatrixMultiply(&matWorld,&matWorld,&inv);
//		D3DXVECTOR3 t=target->GetPos();
//		D3DMath_VectorMatrixMultiply( t, t,matWorld);
//
//	//	tarDir=t.z;
//		LocalAngl(t);
//	}
//}
//extern float globalTT;

//void tCamera::LocalAngl(D3DXVECTOR3 t){
//	float a=0;
//	if (target){
//		a=t.x*t.x+t.y*t.y;
//		anglAx=asin(t.y/(sqrt(a+t.z*t.z)));//угол вращения по OX
//		anglAz=asin(t.x/sqrt(a));//угол вращения по OZ
//		anglAy=-asin(t.x/sqrt(a+t.z*t.z));//угол вращения по OZ
//	}
////	anglAx=0;
//}
