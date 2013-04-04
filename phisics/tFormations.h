// tFormations.h: interface for the tFormations class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TFORMATIONS_H__E962C0C8_B2BA_4641_895E_9820314192AC__INCLUDED_)
#define AFX_TFORMATIONS_H__E962C0C8_B2BA_4641_895E_9820314192AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tObj.h"
#include "boost\smart_ptr.hpp"

class tFormations
{
public:
	int idGroup;
	D3DXVECTOR3 delta;
	boost::intrusive_ptr<tObj> obj;
	boost::intrusive_ptr<tObj> home;

	virtual ~tFormations();
	friend void intrusive_ptr_add_ref(tFormations*);
	friend void intrusive_ptr_release(tFormations*);
	size_t m_refCounter;
	void AddRef() {
//		if (obj) obj->AddRef();
//		if (home) home->AddRef();
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this;
			return;
		}
/*		if (obj){
			if (obj->m_refCounter<m_refCounter){
				bool error=true;}
			if (obj->m_refCounter>1) obj->Release();
		}
		if (home){
			if (home->m_refCounter<m_refCounter){
				bool error=true;}
			if (home->m_refCounter>1) home->Release();
		}*/
	}
  tFormations(): m_refCounter(0) {
	delta=D3DXVECTOR3(0,0,0);
	home=0;
	obj=0;
	idGroup=0;
  }
};
inline void intrusive_ptr_add_ref(tFormations* e) { e->AddRef(); }
inline void intrusive_ptr_release(tFormations* e) { e->Release(); }

#endif // !defined(AFX_TFORMATIONS_H__E962C0C8_B2BA_4641_895E_9820314192AC__INCLUDED_)
