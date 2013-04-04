// tInterpretorCommandInterface.h: interface for the tInterpretorCommandInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_tInterpretorCommandInterface_H__58046574_85C8_47FA_BB8D_EDDE953C83E2__INCLUDED_)
#define AFX_tInterpretorCommandInterface_H__58046574_85C8_47FA_BB8D_EDDE953C83E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\phisics\tPointer.h"
//#include "boost/shared_ptr.hpp"
#include "tship.h"

class tInterpretorCommandInterface : public tPointer  {
protected:
public:
//	friend class tShipCommand;

	virtual bool IsComplete(boost::intrusive_ptr<tShip> _ship_)=0;
	tInterpretorCommandInterface();
	virtual ~tInterpretorCommandInterface();
	virtual void Processing(boost::intrusive_ptr<tShip> _ship_)=0;
	virtual void Reset(boost::intrusive_ptr<tShip> _ship_)=0;
	virtual void Reset()=0;
	void Init(int status);
	void Init(float dist,int status);
	void Init(int status,float speedMin, float speedMax);
	void Init(int status,float speedMin, float speedMax, float angleZ,float angleX);
	void Init(float dist,int status,float speedMin, float speedMax);
	void Init(float dist,int status,float speedMin, float speedMax, float angleX,float angleZ);
	int GetID();
        // bool complete!
protected:
	int id;
	float distance;
	int status;
	float speedMin;
	float speedMax;
	float oZ;
	float oX;
};

#endif // !defined(AFX_tInterpretorCommandInterface_H__58046574_85C8_47FA_BB8D_EDDE953C83E2__INCLUDED_)
