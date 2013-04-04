#pragma once
#include <stdio.h>
#include <memory.h>
#include "..\main\log.h"

extern ESL::CLogFile SDELog;
class tComponents{
struct el{
	int uin;
	char name[20];
	char dest[50];
	float cost;
	int tlevel;
//	int max;
	int types;
	el(){
		uin=0;
		name[0]=0;
		dest[0]=0;
		cost=0;
		tlevel=0;
//		max=0;
		types=0;
	}
};
		el units[30];
		int counts;
public:
//	friend class tWorld;
//	friend class tRender;

	int GetCount();
	void Load(void);
	tComponents(void);
	virtual ~tComponents(void);
};
