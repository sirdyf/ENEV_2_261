// ai_motivation.h: interface for the ai_motivation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AI_MOTIVATION_H__F85F01E9_AC87_11DB_8341_00025511B36C__INCLUDED_)
#define AFX_AI_MOTIVATION_H__F85F01E9_AC87_11DB_8341_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ai_base.h"
#include "tSolution.h"

class ai_motivation
{
public:
	virtual void Processing()=0;
	void Init(boost::intrusive_ptr<ai_base> base);
	void SetObj(boost::intrusive_ptr<tObj> tarObj);
//	void SetPos(D3DXVECTOR3 tarPos);
//	void SetZone(boost::intrusive_ptr<tObj> zone);//virtual obj
	
	virtual ~ai_motivation();

	boost::intrusive_ptr<tSolution> solution;

	friend void intrusive_ptr_add_ref(ai_motivation*);
	friend void intrusive_ptr_release(ai_motivation*);
	size_t m_refCounter;
	void AddRef() {
//		if (solution) solution->AddRef();
//		if (_base) _base->AddRef();
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this;
			return;
		}
/*		if (solution){
			if (solution->m_refCounter<m_refCounter){
				bool error=true;}
			if (solution->m_refCounter>1) solution->Release();
		}
		if (_base){
			if (_base->m_refCounter<m_refCounter){
				bool error=true;}
			if (_base->m_refCounter>1) _base->Release();
		}*/
	}
  ai_motivation(): m_refCounter(0) {}

protected:
	boost::intrusive_ptr<ai_base> _base;
	boost::intrusive_ptr<tObj> tarObj;
};
inline void intrusive_ptr_add_ref(ai_motivation* e) { e->AddRef(); }
inline void intrusive_ptr_release(ai_motivation* e) { e->Release(); }

#endif // !defined(AFX_AI_MOTIVATION_H__F85F01E9_AC87_11DB_8341_00025511B36C__INCLUDED_)
