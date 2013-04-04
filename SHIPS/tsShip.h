// tsShip.h: interface for the tsShip class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSSHIP_H__1EF687C1_4233_11DB_8340_00025511B36C__INCLUDED_)
#define AFX_TSSHIP_H__1EF687C1_4233_11DB_8340_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

class tsShip  
{
public:
	void operator =(const tsShip tse);
	bool tsShip::SetValue(std::string buf);
	int missileSlots;
	int massa;
	char name[10];

	float tonnage;
	int engineClassMax;
	int cost;
	int techLevel;
	int gres;
	float rad;
	float fBaseShield;

	int eqTypesMax[15];

	tsShip();
	virtual ~tsShip();

};
#endif // !defined(AFX_TSSHIP_H__1EF687C1_4233_11DB_8340_00025511B36C__INCLUDED_)
