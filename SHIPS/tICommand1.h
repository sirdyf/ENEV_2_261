// tICommand1.h: interface for the tICommand1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TICOMMAND1_H__CF73D588_09D4_4FFB_8B45_6AA28433BD9B__INCLUDED_)
#define AFX_TICOMMAND1_H__CF73D588_09D4_4FFB_8B45_6AA28433BD9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tICmdI.h"

class tICommand1 : public tInterpretorCommandInterface{
protected:
public:
	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_);
	virtual void Processing(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset();
	tICommand1();
	virtual ~tICommand1();

};

#endif // !defined(AFX_TICOMMAND1_H__CF73D588_09D4_4FFB_8B45_6AA28433BD9B__INCLUDED_)
