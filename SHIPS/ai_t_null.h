// ai_t_null.h: interface for the ai_t_null class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AI_T_NULL_H__34F30387_AC89_11DB_8341_00025511B36C__INCLUDED_)
#define AFX_AI_T_NULL_H__34F30387_AC89_11DB_8341_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ai_motivation.h"

class ai_t_null : public ai_motivation
{
public:
	virtual void Processing();
	ai_t_null();
	virtual ~ai_t_null();

};

#endif // !defined(AFX_AI_T_NULL_H__34F30387_AC89_11DB_8341_00025511B36C__INCLUDED_)
