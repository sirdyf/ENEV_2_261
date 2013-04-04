// tStatus.h: interface for the tStatus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSTATUS_H__1A9019C7_504A_426C_ACE5_6CA4A003F05C__INCLUDED_)
#define AFX_TSTATUS_H__1A9019C7_504A_426C_ACE5_6CA4A003F05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class tStatus  
{
public:
	friend class tICommand1;
	friend class tICommand2;
	friend class tICommand3;
	friend class tICommand4;
	friend class tICommand5;
	friend class tICommand6;
	friend class tICommand7;

	friend class tRender;

	int GetStatus();
	void SetStatus(int st);
	tStatus(int s);
//	void SetStrategyStatus(int a);
	int GetStrategyStatus();
	tStatus();
	virtual ~tStatus();
protected:
//	int tacticStatus;
//	int aiStatus;
	int _status;
};

#endif // !defined(AFX_TSTATUS_H__1A9019C7_504A_426C_ACE5_6CA4A003F05C__INCLUDED_)
