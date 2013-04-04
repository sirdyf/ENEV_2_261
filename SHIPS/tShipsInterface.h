// tShipsInterface.h: interface for the tShipsInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSHIPSINTERFACE_H__100F4E62_AF73_11DB_8341_00025511B36C__INCLUDED_)
#define AFX_TSHIPSINTERFACE_H__100F4E62_AF73_11DB_8341_00025511B36C__INCLUDED_

#include "..\phisics\tObj.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "boost\smart_ptr.hpp"
#include "..\phisics\tPointer.h"
#include "tShip.h"

class tShipsInterface : public tPointer
{
public:
	friend class tRenderMain;
	virtual boost::intrusive_ptr<tObj> GetNextShip(boost::intrusive_ptr<tObj> curShip) =0;
	virtual boost::intrusive_ptr<tObj> GetNextShip(int num)=0;
//	virtual boost::intrusive_ptr<tObj> GetShipObj(int num) =0;
	virtual int GetNumShips() =0;
	virtual bool AllowRegister(boost::intrusive_ptr<tObj> ship)=0;

	tShipsInterface();
	virtual ~tShipsInterface();
	virtual boost::intrusive_ptr<tShip> GetNextShip(boost::intrusive_ptr<tShip> curShip) =0;
protected:
//	virtual boost::intrusive_ptr<tShip> GetNextShip(boost::intrusive_ptr<tShip> curShip) =0;

};

#endif // !defined(AFX_TSHIPSINTERFACE_H__100F4E62_AF73_11DB_8341_00025511B36C__INCLUDED_)
