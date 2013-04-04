// tSolution3.h: interface for the tSolution3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSOLUTION3_H__B53CC040_CCF4_457D_81D2_0500752DF7B3__INCLUDED_)
#define AFX_TSOLUTION3_H__B53CC040_CCF4_457D_81D2_0500752DF7B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tSolution.h"

class tSolution3 : public tSolution  
{
public:
	virtual void Processing();
	virtual void Execute(boost::intrusive_ptr<tShipCommand> shipCommand);
	bool Step1();
	bool Step2();

	tSolution3();
	virtual ~tSolution3();
protected:
	bool bConnectGroup;
	bool bConnectPoint;
};

#endif // !defined(AFX_TSOLUTION3_H__B53CC040_CCF4_457D_81D2_0500752DF7B3__INCLUDED_)
