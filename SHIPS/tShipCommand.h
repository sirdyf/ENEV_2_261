// tShipCommand.h: interface for the tShipCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TDEFENDSHIPSGROUP_H__ACF3BBA9_AE1F_4958_A41A_0FD5EB0931F6__INCLUDED_)
#define AFX_TDEFENDSHIPSGROUP_H__ACF3BBA9_AE1F_4958_A41A_0FD5EB0931F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable: 4786)

//#include "tPointer.h"
//#include"boost/shared_ptr.hpp"
#include "tICmdI.h"
#include "..\server\tOthers.h"

extern tOthers* Others;

class tShipCommand{
protected:
	boost::intrusive_ptr <tShip> _ship;
	void Assign(boost::intrusive_ptr <tShip> _sh);
public:

	friend class AI_Group;
	friend class ai_m_null;
	friend class tSolution3; // 123

	boost::intrusive_ptr <tInterpretorCommandInterface> _command;

	void ProcessCommand();
	void Assign(boost::intrusive_ptr <tInterpretorCommandInterface> _cmd);
	void SetTarget(boost::intrusive_ptr<tObj> tO);
	void SetShip(boost::intrusive_ptr <tShip> _sh);
	void SetCommand(boost::intrusive_ptr <tInterpretorCommandInterface> command);
	void ResetCommand();
	bool IsComplete();
	bool CheckWarnings();
	bool SetMine();

	bool CheckHit(boost::intrusive_ptr<tObj> enemy);
	bool Validate();
	bool CheckFire();	
	int GetCommandId();
	int GetShipIdGroup();
	D3DXVECTOR3 GetShipPos();

	virtual ~tShipCommand();

	friend void intrusive_ptr_add_ref(tShipCommand*);
	friend void intrusive_ptr_release(tShipCommand*);
	size_t m_refCounter;
	void AddRef() {
//		if (_command) _command->AddRef();
//		if (_ship) _ship->AddRef();
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this;
			return;
		}
/*		if (_command){
			if (_command->m_refCounter<m_refCounter){
				bool error=true;}
			if (_command->m_refCounter>1) _command->Release();
		}
		if (_ship){
			if (_ship->m_refCounter<m_refCounter){
				bool error=true;}
			if (_ship->m_refCounter>1) _ship->Release();
		}*/
	}

  tShipCommand(): m_refCounter(0) {}

};
inline void intrusive_ptr_add_ref(tShipCommand* e) { e->AddRef(); }
inline void intrusive_ptr_release(tShipCommand* e) { e->Release(); }

#endif // !defined(AFX_TDEFENDSHIPSGROUP_H__ACF3BBA9_AE1F_4958_A41A_0FD5EB0931F6__INCLUDED_)
