// tICommand6.h: interface for the tICommand6 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TICOMMAND6_H__5D7C9B44_4F6D_4E38_A32B_FC651F0F868A__INCLUDED_)
#define AFX_TICOMMAND6_H__5D7C9B44_4F6D_4E38_A32B_FC651F0F868A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tICmdI.h"

class tICommand6 : public tInterpretorCommandInterface  
{
public:
	tICommand6();
	virtual ~tICommand6();
	virtual void Processing(boost::intrusive_ptr<tShip> _ship_);
	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset();

};

#endif // !defined(AFX_TICOMMAND6_H__5D7C9B44_4F6D_4E38_A32B_FC651F0F868A__INCLUDED_)
