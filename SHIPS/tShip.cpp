// tShip.cpp: implementation of the tShip class.
//
//////////////////////////////////////////////////////////////////////

#include "tShip.h"

#define g_PI         3.14159265358979323846f // Pi
#define g_2_PI       6.28318530717958623200f // 2 * Pi
#define g_PI_DIV_2   1.57079632679489655800f // Pi / 2
#define g_PI_DIV_4   0.78539816339744827900f // Pi / 4
#define g_PI_DIV_6   0.523598775598298873077f
// Pi / 6 =0.523598775598298873077107230546584
#define g_DEGTORAD   0.01745329251994329547f // Degrees to Radians
#define g_RADTODEG  57.29577951308232286465f // Radians to Degrees

extern HRESULT D3DMath_VectorMatrixMultiply( D3DVECTOR& vDest, D3DVECTOR& vSrc,D3DMATRIX& mat);

extern float globalTT;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tShip::tShip(){
	
	aX=0;aY=0;aZ=0;
	dist=10000.0f;distFP=0;
	connectContract=false;
	level=0;role=0;
	tarDir=0;
	tarLookMy=false;
	tarLookAngle=0;

}

tShip::~tShip(){}

int tShip::GetIdGroup(){
	return obj->GetIdGroup();
}
void tShip::WarningReset(){
	tEnemyLookMy=0;
	tLastDamage=0;
	fDamageLevel=0;
}

bool tShip::Warnings(){
	DWORD cTime=GetTickCount();
	if (tEquipment::WarningDamage()) return true;
	if (tEnemyLookMy){
		if (cTime-tEnemyLookMy>5000) return true;
	}
	return false;
}

void tShip::CalculateTarget(void){
	float tarDot=0,ddist=0;
	D3DXVECTOR3 tmp(0,0,0);
	D3DXVECTOR3 tmp2(0,0,0);
//	D3DXVECTOR3 tmp3(0,0,0);
	if (target){
	// определяем направление "взгляда" цели
		D3DXVECTOR3 pos=obj->GetPos();
		D3DXVECTOR3 tar=target->GetPos();
		D3DXVECTOR3 tar_tz=target->tz;
		tmp=pos-tar;
		ddist=D3DXVec3Length(&tmp);
		tmp2=pos-(tar+tar_tz);
	//	tmp3=tar+tar_tz;
		float a=D3DXVec3LengthSq(&tmp);
		float b=D3DXVec3LengthSq(&tmp2);
	//	float distTar=D3DXVec3Length(&t);
	//	if (a>b) tarLookMy=false;
		tarLookMy=false;
		D3DXVec3Normalize(&tmp,&tmp);
	//	D3DXVec3Normalize(&tmp2,&tmp2);
		if (a>b) {
			tarDot=D3DXVec3Dot(&tmp,&tar_tz);
			tarLookAngle=acosf(tarDot);//*g_RADTODEG;		
			if (tarLookAngle<30.0f*0.0174533f) {
				tarLookMy=true;//- угол
				if ((0==tEnemyLookMy)&&(ddist<250.0f)){
					tEnemyLookMy=GetTickCount();
				}else{}
			}else{tEnemyLookMy=0;}
		}else{tEnemyLookMy=0;}
	}else{tEnemyLookMy=0;}
}
/* Обычно для проекции вектора на вектор один из них нормируют и умножают на скалярное произведение.
vector3 projection( const vector3& a,  const vector3& b )
{  vector3 unit_a = a;
   unit_a.norm();
   return  unit_a * dot(unit_a, b);
}
Неприятно то, что при нормализации мы вызываем достаточно медленный квадратный корень, этого можно и нужно избежать.
vector3 projection( const vector3& a,  const vector3& b )
{  vector3 p = a*( dot(a, b)/a.length_squared() ) ;
   return  p;
}*/
void tShip::Calculate(void){

	D3DXVECTOR3 pos=obj->GetPos();
//востанавливаем мировую матрицу
	D3DXMATRIX inv,matWorld;
	D3DXMatrixIdentity(&inv);
	matWorld=obj->GetCurMatrix();//лск
	D3DXMatrixTranslation(&inv,pos.x,pos.y,pos.z);
	D3DXMatrixMultiply(&matWorld,&matWorld,&inv);
	D3DXMatrixIdentity(&inv);
	D3DXMatrixInverse(&inv,NULL,&matWorld);
	D3DXVECTOR3 t=target->GetPos();
	D3DMath_VectorMatrixMultiply( t, t,inv);
	tarDir=t.z;
	LocalAngl(t);
}

void tShip::LocalAngl(D3DXVECTOR3 tv){
	D3DXVECTOR3 t=tv;

	D3DXVec3Normalize(&t,&t);
	float a=t.x*t.x+t.y*t.y;
	if (t.z<0.0f){
		aX=1.57f;
	}else{
		aX=asin(t.y/(sqrt(a+t.z*t.z)));//угол вращения по OX
	}
	aZ=asin(t.x/sqrt(a));//угол вращения по OZ
	aY=-asin(t.x/sqrt(a+t.z*t.z));//угол вращения по OZ
	
	float r1=D3DXVec3Length(&D3DXVECTOR3(tv.x,tv.y,0));
	float r2=D3DXVec3Length(&tv);
	rXY=asin(r1/r2);
}
// automatic
void tShip::Move(){
		if ((rXY<0.01745f*10.0f)&&(tarDir>0)){
			obj->inertSpeed.SetSpeedValue(true);
		}else{
			obj->inertSpeed.SetSpeedValue(false);
		}
		Moving();
}
// manual
void tShip::Move(bool fspeed){
	if (fspeed){
		obj->inertSpeed.SetSpeedValue(true);
	}else{
		obj->inertSpeed.SetSpeedValue(false);
	}
	Moving();
}
void tShip::Moving(void){
	D3DXVECTOR3 len=obj->GetPos()-target->GetPos();
	dist=D3DXVec3Length(&len);
}
//extern float fDeltaTime;
void tShip::Processing(){
//	Decision_Making();//принять решение
D3DXVECTOR3 tmp_v=D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXMATRIX inv,m;

// Внимание!!! ракета без цели получает статус "7"

bool tmp=false;
//if (timerw>0) timerw-=1.0f;
//if (power_weapon>0) power_weapon-=1.0f;

if (status.GetStatus()==11){//если объект д.б.уничтоден
	tShip::obj->mustDestroy=true;//уничтожаем
}

	Weapon.Reload();//обеспечивает работу лазера по времени.Работает всегда.
	if (energy<100.0f) energy+=0.01f;
//	if (IsFire()) energy-=Weapon.FireNow();
CalculateTarget();
if (target){
	if (target->mustDestroy==true){ 
		target=0;// Цель исчезла
		Weapon.NoFire();
	}else{
		switch (status.GetStatus()) {
			case 1:		//полет к статической цели
				Calculate();
				Moving();
				if (tarDir>0){
					if ((rXY>0.01745f*10.0f)&&(dist>200.0f)){
						obj->inertZ.Value=aZ;
						if (obj->inertZ.Value<obj->inertZ.GetSteepness()*10.0f)
							obj->inertX.Value=aX;
						else {}
						Move(false);
					}else{
						obj->inertY.Value=aY;
						obj->inertX.Value=aX;
//	!!!					obj->inertSpeed.Value=target->inertSpeed.GetCurValue();
//	!!!					obj->inertSpeed.InertPredictionSpeed(dist);
					}
				}else{
					obj->inertX.Value=0.01745f*45.0f;
					Move(false);
				}
				break;
			case 2:		//атака цели(этап1:сближение на дистанцию атаки)
				Calculate();
				Moving();
				if (tarDir>0){
					if (rXY>0.01745f*10.0f){
						obj->inertZ.Value=aZ;
						if (obj->inertZ.Value<obj->inertZ.GetSteepness()*10.0f)
							obj->inertX.Value=aX;
					Move(false);
					}else{
						obj->inertY.Value=aY;
						obj->inertX.Value=aX;
						Move(true);
						FireLaser();
					}
				}else{
					obj->inertX.Value=0.01745f*45.0f;
					Move(false);
				}
				break;
			case 3:		//stop
//				obj->inertX.Value=0;
				Move(false);
//				Weapon.NoFire();
				break;
			case 4:// =case 1(slow)
				Calculate();
				Moving();
				if (tarDir>0){
					if ((rXY>0.01745f*10.0f)&&(dist>200.0f)){
						obj->inertZ.Value=aZ;
						if (obj->inertZ.Value<obj->inertZ.GetSteepness()*10.0f)
							obj->inertX.Value=aX;
						else {}
						Move(false);
					}else{
						obj->inertY.Value=aY;
						obj->inertX.Value=aX;
						Move(false);
					}
				}else{
					obj->inertX.Value=0.01745f*20.0f;
					Move(false);
				}
				break;
			case 5://выр-е по осям step1
				Calculate();
				Moving();
				Move(false);
				obj->inertZ.Value=aZ;
				break;
			case 6://выр-е по осям step2
				Calculate();
				Moving();
				Move(false);
				obj->inertX.Value=aX;
				break;
			case 7:		//initialization
				Move(true);
				break;
			case 8: //маневр ухода от атаки
				Calculate();
				Moving();
				if (tarDir>0){
					obj->inertX.Value=0.01745f*30.0f;
					Move(false);
				}else{
					Move(true);
				}
				break;
			case 9: //маневр ухода от столкновения со статическим(!) объектом
				obj->inertX.Value=0.01745f*30.0f;
				Move(false);
				break;
			case 10://вращение по осям с ускорением
				Calculate();
//				Moving();
				Move(true);
				break;
			case 12://вращение по осям с торможением
					Calculate();
//				Moving();
				Move(true);
//				Move(false);
				break;
			case 14://пока(!) это для "бочки"
				Move(false);
				break;
			default:
				break;
			}
		}
	}else{
//		Weapon.NoFire();
	}

}


void tShip::CalcFlyPoint(){
// Atention!!! вычисляется ТОЛЬКО во время задания цели
// Вычисляем точку облета планеты
/*
	if (planet){
// определяем закрывает ли планета цель:
		D3DXVECTOR3 vecPlanet=obj->GetPos()-planet->GetPos();
		float distPlanet=D3DXVec3Length(&vecPlanet);
		D3DXVECTOR3 vecTar=obj->GetPos()-target->GetPos();//вектор от корабля до цели
		float distTar=D3DXVec3Length(&vecTar);
		if (distPlanet<distTar){//если расстояние до планеты < чем до цели
			D3DXVECTOR3 vecPlanTar=planet->GetPos()-target->GetPos();//вектор от планеты до цели
			float distPlanTar=D3DXVec3Length(&vecPlanTar);

			float m_alpha=asin(planet->GetRadius()/distPlanTar);

			D3DXVECTOR3 tmp_vecPlanTar=vecPlanTar;
			D3DXVec3Normalize(&tmp_vecPlanTar,&tmp_vecPlanTar);
float tt2=D3DXVec3Dot(&vecTar,&tmp_vecPlanTar);
			float m_betta=acosf(D3DXVec3Dot(&vecTar,&tmp_vecPlanTar)/(distTar));//*distPlanTar));

			if (m_betta<m_alpha){//если угол касательной > угла относительно цели

				D3DXVec3Normalize(&vecTar,&vecTar);
				float tt=D3DXVec3Dot(&vecPlanTar,&vecTar);
				D3DXVECTOR3 v1=vecTar*tt;
				tt=D3DXVec3Length(&vecPlanTar);
				D3DXVECTOR3 tarVec=(vecPlanTar-v1);
				D3DXVec3Normalize(&tarVec,&tarVec);
				tarVec*=tt;
// !!!				tShip::flyAroundPoint=new tObj;
// !!!				tShip::flyAroundPoint->pos=planet->pos+tarVec;
				status.GetStatus()=20;
			}
		}
	}
*/	
}


void tShip::Create(tsShip ship,tsEngine engine, tsWeapon weapon,int role,D3DXVECTOR3 pos){
	tEquipment::Ship=ship;
	tEquipment::Engine=engine;
	tEquipment::Weapon=weapon;
	tShip::role=role;

	if (role==55)	obj=pEng->CreateObj(ship.gres,ship.rad,pos,9,ship.fBaseShield);
	else	obj=pEng->CreateObj(ship.gres,ship.rad,pos,1,ship.fBaseShield);
}

void tShip::Move(float kSpeed){
/* !!!
	if (obj->inertSpeed.GetCurValue()<obj->inertSpeed.GetMaximum()*kSpeed)
		obj->inertSpeed.SetSpeedValue(true);
	else{
		obj->inertSpeed.SetSpeedValue(false);
	}
*/
	Moving();
}
bool tShip::HaveConnectContract(){
	return connectContract;
}
void tShip::CalculateFP(void){
/*
	D3DXVECTOR3 pos=obj->GetPos();
//востанавливаем мировую матрицу		
	D3DXMATRIX inv,matWorld;
	D3DXMatrixIdentity(&inv);
	matWorld=obj->GetCurMatrix();//лск
	D3DXMatrixTranslation(&inv,pos.x,pos.y,pos.z);
	D3DXMatrixMultiply(&matWorld,&matWorld,&inv);
	D3DXMatrixIdentity(&inv);
	D3DXMatrixInverse(&inv,NULL,&matWorld);
	D3DXVECTOR3 t=flyAroundPoint->GetPos();
	D3DMath_VectorMatrixMultiply( t, t,inv);
	LocalAngl(t);
*/
}
//	rXY=g_PI_DIV_2-acos(r1/r2);
//	rXY=acos(r1/r2);
/*
	if (rXY>0.01745f*5.0f){//если угол до цели >5 град.
		firePos.z=0.0f;// создаем новую точку выстрела
		D3DXVec3Normalize(&firePos,&firePos);
		firePos=firePos*10.0f*cos(0.01745f*5.0f);//43.75f;//длина вектора 43,75(на дистанции 500)
		firePos.z=10.0f;//500.0f;//дистанция 500
	}
*/
/*
    intrusive_ptr(intrusive_ptr const & rhs): p_(rhs.p_)
    {
        if(p_ != 0) intrusive_ptr_add_ref(p_);
    }
*/
/*
tShip::tShip(tShip const &b):rXY(b.rXY){
int ss=0;
}
*/
/*
tShip::tShip(const tShip &a){
//cArray(const cArray &a){
// public:
	tarDir=a.tarDir;
	rXY=a.rXY;
	idGroup=a.idGroup;
// private:
//	firePos=a.firePos;
	regOfStation=a.regOfStation;
	role=a.role;
	level=a.level;
	distFP=a.distFP;
	dist=a.dist;
	aZ=a.aZ;
	aX=a.aX;
	aY=a.aY;
}

tShip& tShip::operator=(tShip const &a){
	tarDir=0;
	return *this;
}
*/
/*
	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);
	D3DXVECTOR3 eye;

	eye.x=tz.x;
	eye.y=tz.y;
	eye.z=tz.z;
	D3DXMatrixLookAtLH (&matView, &D3DXVECTOR3(0,0,0),&eye,&ty);
	D3DXMatrixTranspose(&matView,&matView);
*/
