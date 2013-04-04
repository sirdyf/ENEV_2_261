// tGoods.h: interface for the tGoods class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TGOODS_H__2FC74435_8DA8_4E3B_B9E7_CA46B5A1799C__INCLUDED_)
#define AFX_TGOODS_H__2FC74435_8DA8_4E3B_B9E7_CA46B5A1799C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include "..\main\log.h"

extern ESL::CLogFile SDELog;

class tGoods  
{
public:
	struct mUnit{
		std::string desc;//описание
		std::string meas;//товар
		float delta;//отклонение от базовой стоимости(для расчета)
		float cost;//базовая стоимость
		std::string name;
//		char name[30];
		int num;//в наличии
	};
	public:
		int GetCount();
		int delta;
//		int curPos;
	mUnit units[60];
	void Load();
	tGoods();
	virtual ~tGoods();

protected:
	int counts;
};

#endif // !defined(AFX_TGOODS_H__2FC74435_8DA8_4E3B_B9E7_CA46B5A1799C__INCLUDED_)
