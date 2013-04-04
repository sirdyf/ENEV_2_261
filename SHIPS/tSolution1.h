// tSolution1.h: interface for the tSolution1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSOLUTION1_H__D8256387_78AC_45A8_935C_F3FA6D5A3D20__INCLUDED_)
#define AFX_TSOLUTION1_H__D8256387_78AC_45A8_935C_F3FA6D5A3D20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tSolution.h"
#include "tICommand6.h"
#include "tICommand7.h"
#include "..\main\log.h"

extern ESL::CLogFile SDELog;
class tSolution1 : public tSolution  
{
public:
	virtual void Processing();
	virtual void Execute(boost::intrusive_ptr<tShipCommand> shipCommand);
	virtual void WarningExecute(boost::intrusive_ptr<tShipCommand> shipCommand);
	tSolution1();
	virtual ~tSolution1();
};

#endif // !defined(AFX_TSOLUTION1_H__D8256387_78AC_45A8_935C_F3FA6D5A3D20__INCLUDED_)
