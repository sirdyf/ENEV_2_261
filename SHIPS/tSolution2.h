// tSolution2.h: interface for the tSolution2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSOLUTION2_H__2E2AF30F_2661_46A8_9598_BF1F506EDB2B__INCLUDED_)
#define AFX_TSOLUTION2_H__2E2AF30F_2661_46A8_9598_BF1F506EDB2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tSolution.h"

class tSolution2 : public tSolution  
{
public:
	virtual void Execute(boost::intrusive_ptr<tShipCommand> shipCommand);
	virtual void Processing();
	tSolution2();
	virtual ~tSolution2();

};

#endif // !defined(AFX_TSOLUTION2_H__2E2AF30F_2661_46A8_9598_BF1F506EDB2B__INCLUDED_)
