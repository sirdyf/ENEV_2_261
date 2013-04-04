// tICommand4.h: interface for the tICommand4 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TICOMMAND4_H__B6215280_54E8_416E_9947_9398063C9979__INCLUDED_)
#define AFX_TICOMMAND4_H__B6215280_54E8_416E_9947_9398063C9979__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tICmdI.h"

class tICommand4 : public tInterpretorCommandInterface  
{
public:
	virtual void Processing(boost::intrusive_ptr<tShip> _ship_);
	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_);
	virtual void Reset();
	tICommand4();
	virtual ~tICommand4();

};

#endif // !defined(AFX_TICOMMAND4_H__B6215280_54E8_416E_9947_9398063C9979__INCLUDED_)
