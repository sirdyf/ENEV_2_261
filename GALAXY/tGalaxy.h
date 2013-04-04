// tGalaxy.h: interface for the tGalaxy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TGALAXY_H__850E7108_AD1B_11DB_8341_00025511B36C__INCLUDED_)
#define AFX_TGALAXY_H__850E7108_AD1B_11DB_8341_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4251)
#pragma warning(disable: 4786)

#include "ai_star.h"
#include "boost\smart_ptr.hpp"

//#include "tEngine\tEngine.h"
#include "..\main\log.h"

extern ESL::CLogFile SDELog;
extern char space_name[65];
//extern tEngine* engine;

class tGalaxy 
{
public:
//	friend class tRender;
	int GetNumPlanets(int numStar);
	D3DXVECTOR3 SelectStar(int numStar);
	void Destroy();
	void Init();
	tGalaxy();
	virtual ~tGalaxy();

	boost::intrusive_ptr<AI_Star> aiStar;//Объекты звездной системы
	boost::intrusive_ptr<tStarInterface> GetInterface();
protected:
	struct MYGALAXY{
		char name[10];//избыток! Любой объект tObj содержит имя объекта!
		unsigned char numOfPlanet;
		float sUIN;
	};
	MYGALAXY masOfGalaxy[1000];
};

#endif // !defined(AFX_TGALAXY_H__850E7108_AD1B_11DB_8341_00025511B36C__INCLUDED_)
