// tICommand5.h: interface for the tICommand5 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TICOMMAND5_H__AC117906_09B5_4520_8EDB_2CA4EF03D61D__INCLUDED_)
#define AFX_TICOMMAND5_H__AC117906_09B5_4520_8EDB_2CA4EF03D61D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tICmdI.h"

class tICommand5 : public tInterpretorCommandInterface  
{
public:
	virtual void Processing(boost::intrusive_ptr<tShip> _ship_);
	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset();
	tICommand5();
	virtual ~tICommand5();
protected:
	bool step1;
};

#endif // !defined(AFX_TICOMMAND5_H__AC117906_09B5_4520_8EDB_2CA4EF03D61D__INCLUDED_)
