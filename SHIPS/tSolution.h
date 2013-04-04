// tSolution.h: interface for the tSolution class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSOLUTION_H__0AA81551_D3F0_4D74_9AD6_B3B2F28DFA06__INCLUDED_)
#define AFX_TSOLUTION_H__0AA81551_D3F0_4D74_9AD6_B3B2F28DFA06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ai_base.h"
#include "tIcommand1.h"
#include "tIcommand2.h"
#include "ticommand3.h"
#include "ticommand4.h"
#include "ticommand5.h"

class tSolution
{
public:
	virtual void Init(boost::intrusive_ptr<ai_base> base);
// обработка ВСЕЙ группы СРАЗУ (for ai_motivation)
	virtual void Processing()=0;

// обработка конкретного корабля
	virtual void Execute(boost::intrusive_ptr<tShipCommand> shipCommand)=0;
// Предупреждение при выполнении команды - хвост либо большие повреждения
	virtual void WarningExecute(boost::intrusive_ptr<tShipCommand> shipCommand);

	int GetID();
	
	virtual ~tSolution();
	friend void intrusive_ptr_add_ref(tSolution*);
	friend void intrusive_ptr_release(tSolution*);
	size_t m_refCounter;
	void AddRef() {
//		if (_base) _base->AddRef();
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this;
			return;
		}
/*		if (_base) {
			if (_base->m_refCounter<m_refCounter){
				bool error=true;}//				stderr << "error tSolution m_refCounter";
			if (_base->m_refCounter>1) _base->Release();
		}*/
	}
  tSolution(): m_refCounter(0) {}
protected:
	boost::intrusive_ptr<ai_base> _base;
	int id;

};
inline void intrusive_ptr_add_ref(tSolution* e) { e->AddRef(); }
inline void intrusive_ptr_release(tSolution* e) { e->Release(); }

#endif // !defined(AFX_TSOLUTION_H__0AA81551_D3F0_4D74_9AD6_B3B2F28DFA06__INCLUDED_)
