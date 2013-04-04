// tEquipment1.cpp: implementation of the tEquipment class.
//
//////////////////////////////////////////////////////////////////////

#include "tEquipment.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



/*
tEquipment::tEquipment(const tEquipment &a){
	status=a.status;
	obj=a.obj;
	energy=a.energy;
	Engine=a.Engine;
	Weapon=a.Weapon;
	Ship=a.Ship;
	target=a.target;

}
tEquipment& tEquipment::operator= (tEquipment const &a){
	status=a.status;
	obj=a.obj;
	energy=a.energy;
	Engine=a.Engine;
	Weapon=a.Weapon;
	Ship=a.Ship;
	target=a.target;
return *this;
}
*/
tEquipment::~tEquipment(){
//	target=0; //!!!!!!!!
//	obj=0;
}

//void tEquipment::Processing() {}
/*
void tEquipment::AplyEquipment(){
	if (Engine.Inertion){
		inertX.SetSteepness(Engine.Inertion);
		inertZ.SetSteepness(Engine.Inertion*2.0f);
	}else{
		inertX.SetSteepness(14000.0f);
		inertZ.SetSteepness(14000.0f/2.0f);
	}
	float step=1000.0f;
	float mxm=0.5f;
	if (Engine.InertSpeedSTEP){
		step=Engine.InertSpeedSTEP;
	}
	if (Engine.InertSpeedMAX){
		mxm=Engine.InertSpeedMAX;
	}
	inertSpeed.SetSteepness(step,mxm);
	status=7;
	mustDestroy=false;
}
*/

D3DXVECTOR3 tEquipment::GetPos(){

	return obj->GetPos();
}
bool tEquipment::WarningDamage(){
	float shield=10.0f;//obj->baseShieldMax;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (fDamageLevel>shield/5.0f) return true;// 20%
	else return false;
}
bool tEquipment::Hits(float damagePower){
	// разные виды щитов для разных орудий !
	// сначала вычесть из энергетического щита
	// потом от брони корабля
	DWORD cTime=GetTickCount();
	if (cTime-tLastDamage<3000){
		fDamageLevel+=damagePower;
	}else{
		tLastDamage=cTime;
		fDamageLevel=damagePower;
	}
	bool dead=false;
	dead=obj->Hit(damagePower);
	return dead;
}
bool tEquipment::CheckFireHit(boost::intrusive_ptr<tObj> enemy){
	D3DXVECTOR3 t=D3DXVECTOR3(0,0,0);
	if (tEquipment::IsFire()){
		t=obj->GetPos();
//востанавливаем мировую матрицу
		D3DXMATRIX inv,matWorld;
		D3DXMatrixIdentity(&inv);
		matWorld=obj->GetCurMatrix();//лск
		D3DXMatrixTranslation(&inv,t.x,t.y,t.z);
		D3DXMatrixMultiply(&matWorld,&matWorld,&inv);
		D3DXMatrixIdentity(&inv);
		D3DXMatrixInverse(&inv,NULL,&matWorld);
		t=enemy->GetPos();
		D3DMath_VectorMatrixMultiply( t, t,inv);

		if ((t.z>0)&&(t.z<tEquipment::GetWeaponDist())){
			t.z=0;
			float len=D3DXVec3Length(&t);//растояние до оси Z
			float rad=enemy->GetRadius();
			if (len<rad){
				return true;
			}
		}
	}
	return false;
}
bool tEquipment::IsFire(){
	//if (energy>0) 
		return Weapon.IsFire();
	return false;
}
void tEquipment::NoFire(){
	//energy=-100.0f;
//	Weapon.time_fire=-1.0f;
}
void tEquipment::FireLaser(){
//	if (1){//energy>Weapon.NeedEnergy()){
	if (energy>Weapon.NeedEnergy()){
//		Weapon.Reload();
		energy-=Weapon.FireNow();
//		bFireLaser=true;
	}
}

float tEquipment::GetWeaponDist(){
	return Weapon.GetDist();
}
float tEquipment::GetWeaponDamage(){
	return Weapon.GetDamage();
}
void tEquipment::AssignObj(boost::intrusive_ptr<tObj> o){
	obj=o;
//	if (o==0) return;
//	obj->m_refCounter+=tEquipment::m_refCounter-1;
}
void tEquipment::New_Target(boost::intrusive_ptr<tObj> tar){
	if (target==tar) return;
	target=tar;
	if (target==0) return;
	target->m_refCounter+=tEquipment::m_refCounter-1;
//	CalcFlyPoint();
	tEnemyLookMy=0;
	tLastDamage=0;
}

bool tEquipment::HaveTarget(){
	if (target) return true;

	return false;
}

boost::intrusive_ptr<tObj> tEquipment::GetTargetObj(){
	return target;
}
D3DXVECTOR3 tEquipment::GetTargetPos(){
	if (!target) return D3DXVECTOR3(0,0,0);

	return target->GetPos();
}


void tEquipment::CleanTarget(){
	target=0;
}

