// ai_m_null.h: interface for the ai_m_null class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AI_M_NULL_H__34F30385_AC89_11DB_8341_00025511B36C__INCLUDED_)
#define AFX_AI_M_NULL_H__34F30385_AC89_11DB_8341_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable: 4786)

#include "ai_motivation.h"

class ai_m_null : public ai_motivation  
{
public:
//	boost::intrusive_ptr<tSolution> solution;//!!!
	virtual void Processing();
	ai_m_null();
	virtual ~ai_m_null();

};

#endif // !defined(AFX_AI_M_NULL_H__34F30385_AC89_11DB_8341_00025511B36C__INCLUDED_)
