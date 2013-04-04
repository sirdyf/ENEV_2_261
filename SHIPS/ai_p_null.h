// ai_p_null.h: interface for the ai_p_null class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AI_P_NULL_H__34F30386_AC89_11DB_8341_00025511B36C__INCLUDED_)
#define AFX_AI_P_NULL_H__34F30386_AC89_11DB_8341_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ai_motivation.h"

class ai_p_null : public ai_motivation
{
public:
	virtual void Processing();
	ai_p_null();
	virtual ~ai_p_null();

};

#endif // !defined(AFX_AI_P_NULL_H__34F30386_AC89_11DB_8341_00025511B36C__INCLUDED_)
