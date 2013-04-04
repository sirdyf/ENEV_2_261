// ai_s_null.h: interface for the ai_s_null class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AI_S_NULL_H__34F30384_AC89_11DB_8341_00025511B36C__INCLUDED_)
#define AFX_AI_S_NULL_H__34F30384_AC89_11DB_8341_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ai_motivation.h"

class ai_s_null : public ai_motivation
{
public:
	virtual void Processing();
	ai_s_null();
	virtual ~ai_s_null();

};

#endif // !defined(AFX_AI_S_NULL_H__34F30384_AC89_11DB_8341_00025511B36C__INCLUDED_)
