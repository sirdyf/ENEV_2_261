// tStar.h: interface for the tStar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSTAR_H__F17894A5_239D_11DA_833A_00025511B36C__INCLUDED_)
#define AFX_TSTAR_H__F17894A5_239D_11DA_833A_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable:4786)

#include "..\phisics\tObj.h"
#include "..\phisics\tOwn.h"
#include "..\phisics\pEngine.h"

extern pEngine* pEng;

class tStar{
public:
	int uin;
	float goods[100];// % от дельты
	float amount[100];//в наличии
	boost::intrusive_ptr<tObj> obj;

	void Destroy();
	void Init(float);

	virtual ~tStar();

	friend void intrusive_ptr_add_ref(tStar*);
	friend void intrusive_ptr_release(tStar*);
	size_t m_refCounter;
	void AddRef() {
		if (obj) obj->AddRef();
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this;
			return;
		}
		if (obj){
			if (obj->m_refCounter<m_refCounter){
				bool error=true;}
			if (obj->m_refCounter>1) obj->Release();
		}
	}
//protected:
  tStar(): m_refCounter(0) {uin=0;}
};
inline void intrusive_ptr_add_ref(tStar* e) { e->AddRef(); }
inline void intrusive_ptr_release(tStar* e) { e->Release(); }

#endif // !defined(AFX_TSTAR_H__F17894A5_239D_11DA_833A_00025511B36C__INCLUDED_)
