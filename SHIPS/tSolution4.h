// tSolution4.h: interface for the tSolution4 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSOLUTION4_H__F4E7DB84_AE16_4248_B168_AAF600B42922__INCLUDED_)
#define AFX_TSOLUTION4_H__F4E7DB84_AE16_4248_B168_AAF600B42922__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define COMMAND boost::intrusive_ptr<tInterpretorCommandInterface>

#include "tSolution.h"

class tSolution4 : public tSolution  
{
protected:
//		boost::intrusive_ptr<tObj> dfnTar;
public:
	virtual void Execute(boost::intrusive_ptr<tShipCommand> shipCommand);
	virtual void Processing();
	virtual ~tSolution4();
	virtual void Init(boost::intrusive_ptr<ai_base> base);
	tSolution4();
	COMMAND cPatrul;
	COMMAND cReturn;
};

#endif // !defined(AFX_TSOLUTION4_H__F4E7DB84_AE16_4248_B168_AAF600B42922__INCLUDED_)
