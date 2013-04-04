// tICommand2.h: interface for the tICommand2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TICOMMAND2_H__7D79EB5D_BC7B_4FC6_8D1A_5DAA67288594__INCLUDED_)
#define AFX_TICOMMAND2_H__7D79EB5D_BC7B_4FC6_8D1A_5DAA67288594__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tICmdI.h"

class tICommand2 : public tInterpretorCommandInterface
{
public:
	tICommand2();
	virtual ~tICommand2();
	virtual void Processing(boost::intrusive_ptr<tShip> );
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset();
	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_);
protected:
	bool complete;
//	boost::intrusive_ptr<tShip> ship;
};

#endif // !defined(AFX_TICOMMAND2_H__7D79EB5D_BC7B_4FC6_8D1A_5DAA67288594__INCLUDED_)
