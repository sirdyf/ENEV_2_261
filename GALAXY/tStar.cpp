// tStar.cpp: implementation of the tStar class.
//
//////////////////////////////////////////////////////////////////////

#include "tStar.h"
extern char space_name[65];
extern HRESULT D3DMath_VectorMatrixMultiply( D3DVECTOR& vDest, D3DVECTOR& vSrc,D3DMATRIX& mat);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tStar::~tStar(){}

void tStar::Init(float tuin){
	this->uin=tuin;
	tStar::obj=0;
	tStar::obj=pEng->CreateObj(2,1391980.0f/40.0f/20.0f);
	float cs=10.0f;
//	tStar::radius=1391980.0f/cs/cs;// солнце 1 391 980 км.
	ZeroMemory( &goods, sizeof(goods) );
	ZeroMemory( &amount, sizeof(amount) );
	srand(uin);// !!!
	float pr=0;
	for (int i=0;i<100;i++){
		pr=(FLOAT)(rand())/RAND_MAX;
		if (pr<0.5f) pr=0.5f;
		goods[i]=pr;
		amount[i]=80.0f*(FLOAT)(rand())/RAND_MAX+10.0f;
	}
}

void tStar::Destroy()
{
//for (TList::iterator i=mList.begin();i!=mList.end();i++)
//tPlanet planet;

//for (TPlanet::iterator i=m_Planets.begin();i!=m_Planets.end();i++){
//	(*i).p_d3dx_mesh->Release();
//}
}

