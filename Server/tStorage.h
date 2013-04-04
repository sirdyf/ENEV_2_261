#pragma once

#include <iostream>
#include <sstream>
#include <fstream>

#include "..\main\ttick.h"
#include "..\main\tTransferdata.h"
#include "tIStoragePhysics.h"
//struct sockaddr;

class tStorage: public tIStoragePhysics{
	//tTick mTick;
	std::list<tSendData> physObj;
public:
	void ClearList(void);
	void AddObj(boost::intrusive_ptr<tObj> obj);

	

	tStorage(void);
	virtual ~tStorage(void);
};
