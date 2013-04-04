#pragma once
#include "boost\smart_ptr.hpp"
#include "..\phisics\tobj.h"

class tIStoragePhysics{
public:
	virtual void AddObj(boost::intrusive_ptr<tObj> obj)=0;
};