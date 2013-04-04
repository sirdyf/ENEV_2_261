#pragma once
#include "ai_motivation.h"

class ai_m_empty :
	public ai_motivation
{
public:
	ai_m_empty(void);
public:
	virtual ~ai_m_empty(void);

	virtual void Processing();

};
