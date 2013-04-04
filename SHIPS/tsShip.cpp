// tsShip.cpp: implementation of the tsShip class.
//
//////////////////////////////////////////////////////////////////////

#include "tsShip.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tsShip::tsShip(){
name[0]=0;
massa=0;
missileSlots=0;

tonnage=0;
engineClassMax=0;
cost=0;
techLevel=0;
gres=0;
rad=1.0f;
//ZeroMemory( &eqTypes, sizeof(eqTypes) );
int et[15]={5,4,1,1,1,1,1,4,1};
memcpy(eqTypesMax,et,sizeof(eqTypesMax));
//eqTypes[1]=4;
}

tsShip::~tsShip(){}

bool tsShip::SetValue(std::string buf){
	int tst=0,cmd=0;
				tst=buf.find(" ");
				if (tst<1) return false;
// чувствителен к регистру!!!
				
	if (buf.find("Name")==0) cmd=1;
	if (buf.find("Massa")==0) cmd=2;
	if (buf.find("MissileSlots")==0) cmd=3;
	if (buf.find("Tonnage")==0) cmd=4;
	if (buf.find("EngineClassMax")==0) cmd=5;
	if (buf.find("Cost")==0) cmd=6;
	if (buf.find("TechLevel")==0) cmd=7;
	if (buf.find("Size")==0) cmd=8;
	if (buf.find("Gres")==0) cmd=9;
	if (buf.find("BaseShield")==0) cmd=10;

				if (cmd==0) return false;//Unknown Value
				buf=buf.substr(tst+1,buf.length());
				if (buf.length()>8) buf[9]=0;
				switch(cmd){
				case 1:
					strcpy(name,buf.c_str());
					break;
				case 2:
					massa=atoi(buf.c_str());
					break;
				case 3:
					missileSlots=atoi(buf.c_str());
					break;
				case 4:
					tonnage=atof(buf.c_str());
					break;
				case 5:
					engineClassMax=atoi(buf.c_str());
					break;
				case 6:
					cost=atoi(buf.c_str());
					break;
				case 7:
					techLevel=atoi(buf.c_str());
					break;
				case 8:
					rad=atof(buf.c_str());
					break;
				case 9:
					gres=atoi(buf.c_str());
					break;
				case 10:
					fBaseShield=atof(buf.c_str());
					break;
				default:
					break;
				}
return true;
}
void tsShip::operator =(const tsShip tse){
	massa=tse.massa;
	strcpy(name,tse.name);
	missileSlots=tse.missileSlots;
	tonnage=tse.tonnage;
	engineClassMax=tse.engineClassMax;
	cost=tse.cost;
	techLevel=tse.techLevel;
	gres=tse.gres;
	rad=tse.rad;
	memcpy(eqTypesMax,tse.eqTypesMax,sizeof(eqTypesMax));
//	int tt=sizeof(eqTypes);//two bytes
}