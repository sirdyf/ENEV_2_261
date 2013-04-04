#pragma once

#include "tTick.h"

class tCount{
	float mas[100];
	std::string _title;
	tTick _tick;
	bool _bWrite;
	int _mcount;
	int _auto;
public:
	void WriteDump(std::string );
	int AddValue(float);
	tCount();
	void Init(std::string);
	virtual ~tCount(void);
};