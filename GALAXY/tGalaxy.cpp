// tGalaxy.cpp: implementation of the tGalaxy class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "tGalaxy.h"
#include "../main/tMakeName.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tGalaxy::tGalaxy(){}

tGalaxy::~tGalaxy(){}

void tGalaxy::Init(){
	SDELog.WriteMessageLevelUp("�������� �� ��� �����,�������������...");
	aiStar=boost::intrusive_ptr<AI_Star> (new AI_Star);
//	aiStar->Init();
	SDELog.WriteMessageLevelDown("...���������.");
// ��������� �������� ������ �����
// ������ �������� ������ ������


// ��������� ������� ������
//tStar tmpStar;
//	m_Star.num_of_planets=1;
//	strcat(tmpStar.name,"Stars");
//float xS,yS,zS;
D3DXMATRIX tmp;
//char name[10];



// ������ ��������� � tResManager !!!
int num_of_stars=1000;
srand(2006);
	tMakeName mn;
for (int i=0;i<num_of_stars/3;i++){
// ������������� ����� 1/3
	masOfGalaxy[i].sUIN=(FLOAT)rand();
	mn.GenerateName(&masOfGalaxy[i].name[0]);
	masOfGalaxy[i].numOfPlanet=6.0f*(FLOAT)(rand())/RAND_MAX+3;
}
float st=2*3.1415926/(num_of_stars/3),r=0;
for (int i=num_of_stars/3-1;i<num_of_stars;i++){
// ������������� ����� 2/3
	masOfGalaxy[i].sUIN=(FLOAT)rand();
	mn.GenerateName(&masOfGalaxy[i].name[0]);
	masOfGalaxy[i].numOfPlanet=6.0f*(FLOAT)(rand())/RAND_MAX+3;
	r=r+st;
}
}

void tGalaxy::Destroy(){

//	m_Stars.p_d3dx_mesh->Release();
//	for (int i=0;i<num_of_stars;i++){
//		mStar.Destroy();
//	}
//	m_Stars.clear();
}


boost::intrusive_ptr <tStarInterface> tGalaxy::GetInterface(){
	return aiStar;//�����������!
}
D3DXVECTOR3 tGalaxy::SelectStar(int numStar){
	int numPlanet=masOfGalaxy[numStar].numOfPlanet;
	float sUin=masOfGalaxy[numStar].sUIN;
	aiStar->SetStar(numPlanet,sUin);
//	aiStar->mStar->obj->name[0]=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	char* n1=&aiStar->mStar->obj->name[0];
//	char* n2=&masOfGalaxy[numStar].name[0];
//	strcat(n1,n2);
	return aiStar->GetStarPos();
}

int tGalaxy::GetNumPlanets(int numStar){
	
	return masOfGalaxy[numStar].numOfPlanet;
}


