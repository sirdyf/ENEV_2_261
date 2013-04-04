#pragma once

#include "boost\smart_ptr.hpp"
#include <list>
#include <D3dx8mesh.h>
#include "..\phisics\tobj.h"
#include "..\phisics\pengine.h"

extern pEngine* pEng;

class tOthers{
public:
	friend class tRender;

	tOthers(void);
	virtual ~tOthers(void);
	void Processing(void);
	void AssemblyRubbish();
	bool AddObj(int gres,int indexEngine,float rad,D3DXVECTOR3 pos);
	bool AddObj(boost::intrusive_ptr<tObj> tO);
protected:
	std::list< boost::intrusive_ptr<tObj> > objList;
};
