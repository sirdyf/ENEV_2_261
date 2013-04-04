#pragma once
#include "ticmdi.h"

class tCRotateZ :
	public tInterpretorCommandInterface
{
public:
	tCRotateZ(void);
public:
	virtual ~tCRotateZ(void);

	virtual void Processing(boost::intrusive_ptr<tShip> _ship_);
	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset();
protected:
	bool init;
};
