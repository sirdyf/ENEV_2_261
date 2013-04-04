// tSatelitte.h: interface for the tSatelitte class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSATELITTE_H__F17894A2_239D_11DA_833A_00025511B36C__INCLUDED_)
#define AFX_TSATELITTE_H__F17894A2_239D_11DA_833A_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\phisics\tOwn.h"

class tSatelitte: public tOwn  
{
public:
	char name[10];
	double dist_of_planet;
	tSatelitte();
	virtual ~tSatelitte();

};

#endif // !defined(AFX_TSATELITTE_H__F17894A2_239D_11DA_833A_00025511B36C__INCLUDED_)
