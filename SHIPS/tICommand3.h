// tICommand3.h: interface for the tICommand3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TICOMMAND3_H__886B09A3_3BD9_4346_96F1_592E40A6B8F2__INCLUDED_)
#define AFX_TICOMMAND3_H__886B09A3_3BD9_4346_96F1_592E40A6B8F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tICmdI.h"

class tICommand3 : public tInterpretorCommandInterface  
{
public:
	virtual void Processing(boost::intrusive_ptr<tShip> _ship_);
	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset();
	tICommand3();
	virtual ~tICommand3();
protected:
	bool complete;
//	boost::intrusive_ptr<tShip> ship;
};

#endif // !defined(AFX_TICOMMAND3_H__886B09A3_3BD9_4346_96F1_592E40A6B8F2__INCLUDED_)
