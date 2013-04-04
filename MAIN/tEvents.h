// tEvents.h: interface for the tEvents class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEVENTS_H__2B23D322_AFAE_11DB_8341_00025511B36C__INCLUDED_)
#define AFX_TEVENTS_H__2B23D322_AFAE_11DB_8341_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class tEvents  
{
public:
	virtual void Event() =0;
	tEvents(){}
	virtual ~tEvents(){}

};

#endif // !defined(AFX_TEVENTS_H__2B23D322_AFAE_11DB_8341_00025511B36C__INCLUDED_)
