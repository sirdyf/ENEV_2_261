#pragma once
#include "ticmdi.h"

class tCEWSL :
	public tInterpretorCommandInterface
{
public:
	tCEWSL(void);
public:
	virtual ~tCEWSL(void);

	virtual void Processing(boost::intrusive_ptr<tShip> _ship_);
	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset();
};
