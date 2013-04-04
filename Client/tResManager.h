// tResManager.h: interface for the tResManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRESMANAGER_H__20966221_2A8E_11DA_833A_00025511B36C__INCLUDED_)
#define AFX_TRESMANAGER_H__20966221_2A8E_11DA_833A_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <list>
#include <vector>
//#include "tObjResource.h"
//#include "tEngine\tEngine.h"
//typedef std::map<string,tObjResource> TObjRes;
//typedef std::vector<tObjResource> TObjRes;
#include <D3dx8mesh.h>
#include "..\main\log.h"

extern ESL::CLogFile SDELog;

class tResManager  
{
public:
	int numOfStars;
	int id_galaxy;
	struct VERTEX {
		D3DXVECTOR3 pos;
		DWORD color; // Цвет
	};
	VERTEX v_galaxy[1000];
//	float num_of_stars;

//	double GetMax(LPD3DXMESH p_mesh);
//	float CreateBoundSphere(LPD3DXMESH p_mesh,int &vertex,int &index,DWORD &num_v,DWORD &num_f);
	struct COORDS{
		float x,y,z;
	};

	struct TEXVERTEX {
		D3DXVECTOR3 pos;	// Позиция
		float tu,tv;	// Текстура
	};

	VERTEX v_cub[16];
	VERTEX v_fire[2+2*4];
	
	VERTEX horizont[3];
	VERTEX ugol[6];

	VERTEX lsk[6];
	VERTEX tar_aX[6];
	VERTEX tar_aZ[6];

	TEXVERTEX v_tar[4];
	COORDS *my_coord;
	int ind[16];
	int tar_i,tar_tex;
	int target_enemy_buf1;
	int target_enemy_buf2;
//	int CreateBoundBox(LPD3DXMESH p_mesh);
	void RMDestroy();
	void RMInit();
	tResManager();
	virtual ~tResManager();
//	TObjRes m_Res;
	
	VERTEX fire[3];

	VERTEX line[2];

	VERTEX enemy[9];

	VERTEX radar_grid[30];

	VERTEX radar_sph[400];

	VERTEX st_con[5];

//	BYTE *tmpVerticies,*tmpVerticiesInd;
//	DWORD tmpNumVertices;
//	DWORD tmpNumFaces;
//	DWORD tmpFVF;
};

#endif // !defined(AFX_TRESMANAGER_H__20966221_2A8E_11DA_833A_00025511B36C__INCLUDED_)
