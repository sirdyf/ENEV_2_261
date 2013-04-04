// tsWeapon.cpp: implementation of the tsWeapon class.
//
//////////////////////////////////////////////////////////////////////

#include "tsWeapon.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void tsWeapon::operator =(const tsWeapon tse){
	name[0]=0;
	strcpy(name,tse.name);
	dist=tse.dist;
	damage=tse.damage;
	cost=tse.cost;
	massa=tse.massa;
	techlevel=tse.techlevel;

}
bool tsWeapon::SetValue(std::string buf){
	int tst=0,cmd=0;
	tst=buf.find(" ");
	if (tst<1) return false;
	// чувствителен к регистру!!!

	if (buf.find("Name")==0) cmd=1;
	if (buf.find("Distance")==0) cmd=2;
	if (buf.find("Damage")==0) cmd=3;
	if (buf.find("Cost")==0) cmd=4;
	if (buf.find("Massa")==0) cmd=5;
	if (buf.find("TechLevel")==0) cmd=6;
	if (cmd==0) return false;//Unknown Value
	buf=buf.substr(tst+1,buf.length());
	switch(cmd){
	case 1:
		strcpy(name,buf.c_str());
		break;
	case 2:
		dist=atof(buf.c_str());
		break;
	case 3:
		damage=atof(buf.c_str());
		break;
	case 4:
		cost=atof(buf.c_str());
		break;
	case 5:
		massa=atof(buf.c_str());
		break;
	case 6:
		techlevel=atof(buf.c_str());
		break;
	default:
		break;
	}
return true;
}

tsWeapon::tsWeapon(){
name[0]=0;
dist=1500.0f;
damage=1.0f;
cost=0;
massa=0;
techlevel=0;
power_weapon=0.1f;
//timerw=0;
ktf=5.0f;
ktr=5.0f;
time_fire=0;
time_fire_max=1.0f;
//time_pause=0;
//time_pause_max=150.0f;

}

tsWeapon::~tsWeapon(){}

bool tsWeapon::IsFire(){
	if (time_fire>0) return true;

	return false;
}
//extern float fDeltaTime;
void tsWeapon::NoFire(){
	time_fire=-1.0f;
}
void tsWeapon::Reload(){
	if (time_fire<0) time_fire-=ktr;//*fDeltaTime;
	if (time_fire<-time_fire_max)
		time_fire=0;//time_fire_max;
//	time_pause=time_pause_max;
	if (time_fire>0) {
		time_fire-=ktf;//*fDeltaTime;
	}
}
float tsWeapon::FireNow(){
//	if (time_pause>0) {
//		time_pause-=1.0f;
//	}else{
//		Reload();
//	}
	if (time_fire==0)	{
		time_fire=time_fire_max;
	}
	if (time_fire>0) {
		return power_weapon;//*fDeltaTime*1000.0f;
	}
return 0;
}
float tsWeapon::NeedEnergy(){
//	time_pause=time_pause_max;
	return power_weapon*(time_fire_max/(ktf));//*fDeltaTime));
}

float tsWeapon::GetDamage(){
	return damage;
}
float tsWeapon::GetDist(){
	return dist;
}
