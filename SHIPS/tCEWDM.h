#pragma once
#include "ticmdi.h"

class tCEWDM : public tInterpretorCommandInterface{
	// C-command E-execute W-while D-distance M-more then
public:
	tCEWDM(void);
	virtual ~tCEWDM(void);

	virtual void Processing(boost::intrusive_ptr<tShip> _ship_);
	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset();
};
