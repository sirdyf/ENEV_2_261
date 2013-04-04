// tShipsContainer.h: interface for the tShipsContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSHIPSCONTAINER_H__850E7104_AD1B_11DB_8341_00025511B36C__INCLUDED_)
#define AFX_TSHIPSCONTAINER_H__850E7104_AD1B_11DB_8341_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
#include "boost\smart_ptr.hpp"
#include "tShip.h"
#include "tShipsInterface.h"
#include "..\phisics\tObj.h"	// Added by ClassView


class tShipsContainer :  public tShipsInterface
{
public:
//	virtual void SolSystem();
	virtual bool AllowRegister(boost::intrusive_ptr<tObj> ship);
	virtual boost::intrusive_ptr<tObj> GetNextShip(boost::intrusive_ptr<tObj> curShip);
	virtual boost::intrusive_ptr<tShip> GetNextShip(boost::intrusive_ptr<tShip> curShip);
	virtual boost::intrusive_ptr<tObj> GetNextShip(int curShip);
	
//	virtual boost::intrusive_ptr<tObj> GetShipObj(int num);
	virtual int GetNumShips();
	tShipsContainer();
	virtual ~tShipsContainer();

	std::list< boost::intrusive_ptr<tShip> > mShips;// список ИИ группы кораблей
private:
};

#endif // !defined(AFX_TSHIPSCONTAINER_H__850E7104_AD1B_11DB_8341_00025511B36C__INCLUDED_)
