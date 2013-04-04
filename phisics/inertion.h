// inertion.h: interface for the inertion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INERTION_H__EDFFCEE1_FF7D_11D9_8339_00025511B36C__INCLUDED_)
#define AFX_INERTION_H__EDFFCEE1_FF7D_11D9_8339_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <math.h>
class inertion  {
public:
	friend class pEngine;
	friend class tRender;
	friend class tObj;

	void InertPrediction();
	void SetSpeedValue(bool dir);
	void SetValue(float v);
	void operator =(const inertion tse);
	void InertPredictionSpeed(float tarDist,float fDeltaTime);
	void SetAcceleration(float stpns,int maxStep);

	bool Check();
	void SetValuePrediction(int step);
	float GetMaximum();
	float GetCurValue(float fDeltaTime);
	float GetSteepness();
//	float GetValue(bool direction);
	inertion();
	virtual ~inertion();

	float Value;
//	float* d_time;
	float minPercent;
protected:
	float CalcCurrentPath();
	float CalcFullPath(int stp);
//	float accelStepPerSecond;
	float curValueSign;
	float maxStep;
	float maxPercent;
	float steepness;
	float curValue;
	float maximum;
//	bool direction;
	bool SetMinValueInPercent(float percent);
	bool SetMaxValueInPercent(float percent);
//	void CheckAndSetValue(float w,float fDeltaTime);
};

#endif // !defined(AFX_INERTION_H__EDFFCEE1_FF7D_11D9_8339_00025511B36C__INCLUDED_)
