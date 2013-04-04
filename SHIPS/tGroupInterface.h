#pragma once

#include "boost\smart_ptr.hpp"
#include "..\phisics\tObj.h"

class tGroupInterface{
public:
//	tGroupInterface(void);
	virtual ~tGroupInterface(void);

	virtual bool SetMotivationDefendObj(boost::intrusive_ptr<tObj> dObj)=0;
	virtual void SetMotivationEmpty()=0;
	virtual void SetMotivationNull()=0;
//	void SetPos(D3DXVECTOR3 tarPos);
//	void SetZone(boost::intrusive_ptr<tObj> zone);//virtual obj
	friend void intrusive_ptr_add_ref(tGroupInterface*);
	friend void intrusive_ptr_release(tGroupInterface*);
	size_t m_refCounter;
	void AddRef() {
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this;
			return;
		}
	}
  tGroupInterface(): m_refCounter(0) {}

};
inline void intrusive_ptr_add_ref(tGroupInterface* e) { e->AddRef(); }
inline void intrusive_ptr_release(tGroupInterface* e) { e->Release(); }
