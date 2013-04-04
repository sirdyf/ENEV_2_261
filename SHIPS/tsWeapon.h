// tsWeapon.h: interface for the tsWeapon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSWEAPON_H__9A9E93C1_F2E4_11DA_8340_00025511B36C__INCLUDED_)
#define AFX_TSWEAPON_H__9A9E93C1_F2E4_11DA_8340_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

class tsWeapon  
{
public:
	void NoFire();
	bool IsFire();
	float FireNow();
	float NeedEnergy();

	void operator =(const tsWeapon tse);
	bool SetValue(std::string);
	tsWeapon();
	float GetDamage();
	float GetDist();
	virtual ~tsWeapon();
	float power_weapon;//tmp
//	float timerw;//tmp
	void Reload();
protected:
	float ktf;
	float ktr;
	char name[10];
	float cost;
	float massa;
	float damage;
	int techlevel;
	float dist;
	float time_fire;
//	float time_pause;
	float time_fire_max;
//	float time_pause_max;
//	float energy;


};

#endif // !defined(AFX_TSWEAPON_H__9A9E93C1_F2E4_11DA_8340_00025511B36C__INCLUDED_)
