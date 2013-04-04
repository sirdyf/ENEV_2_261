// tsEngine.h: interface for the tsEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSENGINE_H__9A9E93C2_F2E4_11DA_8340_00025511B36C__INCLUDED_)
#define AFX_TSENGINE_H__9A9E93C2_F2E4_11DA_8340_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
//#include"tObj.h"

class tsEngine // : public tObj
{
public:
//	int indEng;
	void operator =(const tsEngine tse);
	bool SetValue(std::string);
	tsEngine();
	virtual ~tsEngine();
//protected:
	bool HaveHyperJamp;
	float DistOfHyperJamp;
	float Massa;
	
	char name[10];
};

#endif // !defined(AFX_TSENGINE_H__9A9E93C2_F2E4_11DA_8340_00025511B36C__INCLUDED_)
