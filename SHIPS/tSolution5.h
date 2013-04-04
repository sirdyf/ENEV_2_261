// tSolution5.h: interface for the tSolution5 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSOLUTION5_H__5DE7D180_9200_456E_9E9D_F34C9DF8719D__INCLUDED_)
#define AFX_TSOLUTION5_H__5DE7D180_9200_456E_9E9D_F34C9DF8719D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tSolution.h"

#define COMMAND boost::intrusive_ptr<tInterpretorCommandInterface>

class tSolution5 : public tSolution  
{
public:
	COMMAND cFastMove;
	COMMAND cSlowMove;
	COMMAND cRotate;
	virtual void Execute(boost::intrusive_ptr<tShipCommand> shipCommand);
	virtual void Init(boost::intrusive_ptr<ai_base> base);
	virtual void Processing();
	tSolution5();
	virtual ~tSolution5();

};

#endif // !defined(AFX_TSOLUTION5_H__5DE7D180_9200_456E_9E9D_F34C9DF8719D__INCLUDED_)
