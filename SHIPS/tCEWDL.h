#pragma once
#include "ticmdi.h"

class tCEWDL :public tInterpretorCommandInterface{
	// C-command E-execute W-while D-distance L-less then
public:
	tCEWDL(void);
	virtual ~tCEWDL(void);
	virtual void Processing(boost::intrusive_ptr<tShip> _ship_);
	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset();
};
