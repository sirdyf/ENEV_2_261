// tObj.cpp: implementation of the tObj class.
//
//////////////////////////////////////////////////////////////////////

#include "tObj.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
tObj::tObj(const tObj &a){
	gRes=a.gRes;
}
tObj& tObj::operator= (tObj const &b){
	gRes=b.gRes;
	return *this;
}
*/
tObj::~tObj(){}

void tObj::SetIdGroup(int id){
	idGroup=id;
}
int tObj::GetIdGroup(){
	return idGroup;
}

 D3DXVECTOR3 tObj::GetPos(){
	return pos;}

 void tObj::SetExplosive(float r, float p,int idGr){
	 bExplosive=true;
	 fExplRad=r;
	 fExplPower=p;
	 idGroup=idGr;
 }
float tObj::GetExplRad(){
	 return fExplRad;
 }
float tObj::GetExplPower(){
	 return fExplPower;
 }
int tObj::GetUin(){
	return uin;
}
void tObj::SetUin(int u){
	uin=u;
}
 float tObj::GetRadius(){
	return radius;}

 D3DXMATRIX tObj::GetCurMatrix(){
	return m;
}

float tObj::GetShield(){
	return baseShield;
}
bool tObj::Hit(float damage){
	baseShield-=damage;
	if (baseShield>0){
		return false;
	}else{
		mustDestroy=true;
		return true;
	}
}

float tObj::GetDiametr(){
return radius*2.0f;
}
bool tObj::SetMaxSpeed(float percent){
	inertSpeed.SetMaxValueInPercent(percent);
	return true;
}

bool tObj::SetMinSpeed(float percent){
	if (percent<0.01f) percent=0.01f;
	inertSpeed.SetMinValueInPercent(percent);
	return true;
}
void tObj::ResetXZbalance(){
	inertX.SetMinValueInPercent(0);
	inertZ.SetMinValueInPercent(0);

	inertX.SetMaxValueInPercent(1.0f);
	inertZ.SetMaxValueInPercent(1.0f);
}
bool tObj::SetRotateXZbalance(float percent){

	if (percent==0) {ResetXZbalance();return true;}

	if (percent<0.1f) percent =0.1f;
	if (percent>0.9f) percent=0.9f;

	inertX.SetMinValueInPercent(0);
	inertZ.SetMinValueInPercent(0);

	inertX.SetMaxValueInPercent(percent);
	inertZ.SetMaxValueInPercent(1-percent);

	return true;
}
//void tObj::SetOrient(Vector _dir,Vector _up){
//	D3DXVECTOR3 dir=D3DXVECTOR3(_dir.x,_dir.y,_dir.z);
//	D3DXVECTOR3 up=D3DXVECTOR3(_up.x,_up.y,_up.z);
//	this->SetOrient(dir,up);
//}
void tObj::SetOrient(D3DXVECTOR3 dir,D3DXVECTOR3 up){
//	return;
	D3DXVec3Normalize(&dir,&dir);
	D3DXVec3Normalize(&up,&up);

	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);
	D3DXVECTOR3 eye=dir;
	D3DXMatrixLookAtLH (&matView, &D3DXVECTOR3(0,0,0),&eye,&up);
//		D3DXMatrixTranspose(&matView,&matView);
	m=matView;
	tx=D3DXVECTOR3(matView._11,matView._21,matView._31);
	ty=D3DXVECTOR3(matView._12,matView._22,matView._32);
	tz=D3DXVECTOR3(matView._13,matView._23,matView._33);
}
/*
Remarks
The return value for this function is the same value returned in the pOut parameter. In this way, the D3DXMatrixLookAtLH function can be used as a parameter for another function.

This function uses the following formula to compute the returned matrix.

zaxis = normal(At - Eye)
xaxis = normal(cross(Up, zaxis))
yaxis = cross(zaxis, xaxis)
    
 xaxis.x           yaxis.x           zaxis.x          0
 xaxis.y           yaxis.y           zaxis.y          0
 xaxis.z           yaxis.z           zaxis.z          0
-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  l

Requirements
Header: Declared in D3dx9math.h.
------------------------------
D3DXMATRIX
Describes a matrix.

Syntax
typedef struct D3DXMATRIX { 
    FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
    FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
    FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
    FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44 );
} D3DXMATRIX;

*/