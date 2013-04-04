#pragma once
#include "ticmdi.h"

class tCEWSM :
	public tInterpretorCommandInterface
{
public:
	tCEWSM(void);
public:
	virtual ~tCEWSM(void);

	virtual void Processing(boost::intrusive_ptr<tShip> _ship_);
	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset();
};
