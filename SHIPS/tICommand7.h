// tICommand7.h: interface for the tICommand7 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TICOMMAND7_H__CC4AA261_5BCA_42A6_BCF4_BAD8F70FEDA4__INCLUDED_)
#define AFX_TICOMMAND7_H__CC4AA261_5BCA_42A6_BCF4_BAD8F70FEDA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tICmdI.h"

class tICommand7 : public tInterpretorCommandInterface  
{
public:
	tICommand7();
	virtual ~tICommand7();
//	void Init(boost::intrusive_ptr<tShip> _ship_);
	virtual void Processing(boost::intrusive_ptr<tShip> _ship_);
	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset();

};

#endif // !defined(AFX_TICOMMAND7_H__CC4AA261_5BCA_42A6_BCF4_BAD8F70FEDA4__INCLUDED_)
