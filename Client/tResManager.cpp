// tResManager.cpp: implementation of the tResManager class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable:4786)

#include "tResManager.h"

//extern tEngine* engine;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define g_PI         3.14159265358979323846f // Pi
#define g_2_PI       6.28318530717958623200f // 2 * Pi
#define g_PI_DIV_2   1.57079632679489655800f // Pi / 2
#define g_PI_DIV_4   0.78539816339744827900f // Pi / 4
#define g_PI_DIV_6   0.523598775598298873077f

tResManager::tResManager()
{
	int t_ind[16]={0,4,6,2,3,1,0,2,5,1,3,7,6,4,5,7};
	memcpy(ind,t_ind,16*4);
// center
	v_fire[0].pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	v_fire[1].pos=D3DXVECTOR3(0.0f,0.0f,500.0f);//dist_of_fire
// left
	v_fire[2].pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	v_fire[3].pos=D3DXVECTOR3(43.75f,0.0f,500.0f);
// right
	v_fire[4].pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	v_fire[5].pos=D3DXVECTOR3(-43.75f,0.0f,500.0f);
// up
	v_fire[6].pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	v_fire[7].pos=D3DXVECTOR3(0.0f,43.75f,500.0f);
// down
	v_fire[8].pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	v_fire[9].pos=D3DXVECTOR3(0.0f,-43.75f,500.0f);

float x=0.2f;
float y=0.1f;
float tu=0.6f;//59f;
float tv=0.5f;//47f;
	v_tar[0].pos=D3DXVECTOR3( x, y,0.0f);
	v_tar[1].pos=D3DXVECTOR3( x,-y,0.0f);
	v_tar[2].pos=D3DXVECTOR3(-x, y,0.0f);
	v_tar[3].pos=D3DXVECTOR3(-x,-y,0.0f);

	v_tar[0].tu=tu; v_tar[0].tv=0;
	v_tar[1].tu=tu; v_tar[1].tv=tv;
	v_tar[2].tu=0;	v_tar[2].tv=0;
	v_tar[3].tu=0;	v_tar[3].tv=tv;

	horizont[0].pos=D3DXVECTOR3(-0.05f,-0.05f,0.0f); horizont[0].color=0xffff0000;
	horizont[1].pos=D3DXVECTOR3( 0.0f,  0.05f,0.0f); horizont[1].color=0xffff0000;
	horizont[2].pos=D3DXVECTOR3( 0.05f,-0.05f,0.0f); horizont[2].color=0xffff0000;

	ugol[0].pos=D3DXVECTOR3(+0.0f, +0.0f, 0.0f); ugol[0].color=0xff00ff00;
	ugol[1].pos=D3DXVECTOR3(-0.03f,-0.08f,0.0f); ugol[1].color=0xff00ff00;
	ugol[2].pos=D3DXVECTOR3( 0.0f, -0.06f,0.0f); ugol[2].color=0xff00ff00;

	ugol[3].pos=D3DXVECTOR3(0.0f, -0.06f,0.0f); ugol[3].color=0xff00ff00;
	ugol[4].pos=D3DXVECTOR3(0.03f,-0.08f,0.0f); ugol[4].color=0xff00ff00;
	ugol[5].pos=D3DXVECTOR3(0.0f, +0.0f ,0.0f); ugol[5].color=0xff00ff00;

	lsk[0].pos=D3DXVECTOR3(0.0f, 0.0f ,0.0f); lsk[0].color=0xffffffff;
	lsk[1].pos=D3DXVECTOR3(1.0f, 0.0f ,0.0f); lsk[1].color=0xffffffff;
	lsk[2].pos=D3DXVECTOR3(0.0f, 0.0f ,0.0f); lsk[2].color=0xffffffff;
	lsk[3].pos=D3DXVECTOR3(0.0f, 1.0f ,0.0f); lsk[3].color=0xffffffff;
	lsk[4].pos=D3DXVECTOR3(0.0f, 0.0f ,0.0f); lsk[4].color=0xffffffff;
	lsk[5].pos=D3DXVECTOR3(0.0f, 0.0f ,1.0f); lsk[5].color=0xffffffff;

	tar_aX[0].pos=D3DXVECTOR3(0.0f, 0.0f ,0.0f);	tar_aX[0].color=0xffffffff;
	tar_aX[1].pos=D3DXVECTOR3(0.0f, 0.0f ,1.0f);	tar_aX[1].color=0xffffffff;
	tar_aX[2].pos=D3DXVECTOR3(0.0f, 0.0f ,1.0f);	tar_aX[2].color=0xffffffff;
	tar_aX[3].pos=D3DXVECTOR3(0.0f, 0.03f ,0.8f);	tar_aX[3].color=0xffffffff;
	tar_aX[4].pos=D3DXVECTOR3(0.0f, 0.0f ,1.0f);	tar_aX[4].color=0xffffffff;
	tar_aX[5].pos=D3DXVECTOR3(0.0f,-0.03f,0.8f);	tar_aX[5].color=0xffffffff;

	tar_aZ[0].pos=D3DXVECTOR3(0.0f, 0.0f ,0.0f);	tar_aZ[0].color=0xffffffff;
	tar_aZ[1].pos=D3DXVECTOR3(1.0f, 0.0f ,0.0f);	tar_aZ[1].color=0xffffffff;
	tar_aZ[2].pos=D3DXVECTOR3(1.0f, 0.0f ,0.0f);	tar_aZ[2].color=0xffffffff;
	tar_aZ[3].pos=D3DXVECTOR3(0.8f, 0.03f ,0.0f);	tar_aZ[3].color=0xffffffff;
	tar_aZ[4].pos=D3DXVECTOR3(1.0f, 0.0f ,0.0f);	tar_aZ[4].color=0xffffffff;
	tar_aZ[5].pos=D3DXVECTOR3(0.8f,-0.03f ,0.0f);	tar_aZ[5].color=0xffffffff;

	enemy[0].pos=D3DXVECTOR3( 0.0f, 0,-0.05f );	enemy[0].color=0xffffffff;
	enemy[1].pos=D3DXVECTOR3( 0.02f,0,-0.05f);	enemy[1].color=0xffffffff;
	enemy[2].pos=D3DXVECTOR3( 0.02f, 0,0.0f );	enemy[2].color=0xffffffff;
	enemy[3].pos=D3DXVECTOR3( 0.04f, 0,0.0f );	enemy[3].color=0xffffffff;
	enemy[4].pos=D3DXVECTOR3( 0.0f , 0,0.05f);	enemy[4].color=0xffffffff;
	enemy[5].pos=D3DXVECTOR3(-0.04f, 0,0.0f );	enemy[5].color=0xffffffff;
	enemy[6].pos=D3DXVECTOR3(-0.02f, 0,0.0f );	enemy[6].color=0xffffffff;
	enemy[7].pos=D3DXVECTOR3(-0.02f,0,-0.05f );	enemy[7].color=0xffffffff;
	enemy[8].pos=D3DXVECTOR3( 0.0f, 0,-0.05f );	enemy[8].color=0xffffffff;

	st_con[0].pos=D3DXVECTOR3(-2, 1,0);
	st_con[1].pos=D3DXVECTOR3( 2, 1,0);
	st_con[2].pos=D3DXVECTOR3( 2,-1,0);
	st_con[3].pos=D3DXVECTOR3(-2,-1,0);
	st_con[4].pos=D3DXVECTOR3(-2, 1,0);
}

tResManager::~tResManager()
{

}

extern HRESULT D3DMath_VectorMatrixMultiply( D3DVECTOR& vDest, D3DVECTOR& vSrc,D3DMATRIX& mat);

void tResManager::RMInit(){
// RADAR - GRID
float stepX=10;
float stepY=5;
float dx1=0.08f;
float dx2=0.03f;
float dy=0.3f;
	for (int i=0;i<stepX;i++){
		radar_grid[i*2].pos=D3DXVECTOR3(   dx1*i-dx1*stepX/2.0f,-dy, 0.0f ); radar_grid[i*2].color=0xffffffff;
		radar_grid[i*2+1].pos=D3DXVECTOR3( dx2*i-dx2*stepX/2.0f, dy,0.0f ); radar_grid[i*2+1].color=0xffffffff;
	}
	for (int i=0;i<stepY;i++){
		radar_grid[i*2+(int)stepX*2].pos=D3DXVECTOR3(  -dx1*stepX/2.0f+i*(dx1*stepY-dx2*stepY)/(stepY-1), dy/2.0f*i-dy, 0.0f );
		radar_grid[i*2+(int)stepX*2].color=0xffffffff;
		radar_grid[i*2+1+(int)stepX*2].pos=D3DXVECTOR3(dx1*(stepX-1)-dx1*stepX/2.0f-i*(dx1*stepY-dx2*stepY)/stepY, dy/2.0f*i-dy,0.0f );
		radar_grid[i*2+1+(int)stepX*2].color=0xffffffff;
	}
// RADAR - SPHERE
int	i=0;
	int step=20;
	for (float angl=0;angl<g_PI;angl+=g_PI/step){
		radar_sph[i].pos=D3DXVECTOR3(cosf(angl),sinf(angl),0)/3.0f;
		radar_sph[i].color=0xffffffff;
		i++;
	}
float stp2=g_PI/step*2.0f;
D3DXMATRIX m1;
D3DXMatrixRotationX(&m1,stp2);
D3DXVECTOR3 k=D3DXVECTOR3(0,0,0);
for (float anglZ=stp2;anglZ<g_PI*2.0f;anglZ+=stp2){
	for (int j=0;j<step;j++){
		k=radar_sph[i-step].pos;
		D3DMath_VectorMatrixMultiply(k,k,m1);
		radar_sph[i].pos=k;
		radar_sph[i].color=0xffffffff;
	i++;
	}
}
numOfStars=1000;
SDELog.WriteMessage("кол-во звезд:%d",numOfStars);
srand(2006);
SDELog.WriteMessage("Инициализация...");
for ( i=0;i<numOfStars/3;i++){
// инициализация звезд 1/3
	float xS=20.0f*(FLOAT)(rand())/RAND_MAX-10.0f;
	float yS=20.0f*(FLOAT)(rand())/RAND_MAX-10.0f;
	float zS=20.0f*(FLOAT)(rand())/RAND_MAX-10.0f;
	v_galaxy[i].pos.x=xS;
	v_galaxy[i].pos.y=yS;
	v_galaxy[i].pos.z=zS;
	v_galaxy[i].color=0xffffffff;
}
float st=2*3.1415926/(numOfStars/3),r=0;
for (i=numOfStars/3-1;i<numOfStars;i++){
// инициализация звезд 2/3
	float xS=cos(r)*(10.0f-i/200.0f);
	float yS=sin(r)*(10.0f-i/200.0f);
	float zS=2.0f*(FLOAT)(rand())/RAND_MAX-1.0f;
	v_galaxy[i].pos.x=xS;
	v_galaxy[i].pos.y=yS;
	v_galaxy[i].pos.z=zS;
	v_galaxy[i].color=0xffffffff;
	r=r+st;

	fire[0].pos=D3DXVECTOR3(-0.5f,-0.5f,0.0f);
	fire[1].pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	fire[2].pos=D3DXVECTOR3(0.5f,-0.5f,0.0f);
	fire[0].color=0xffffffff;
	fire[1].color=0xffffffff;
	fire[2].color=0xffffffff;

	line[0].pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	line[1].pos=D3DXVECTOR3(0.0f,0.0f,100.0f);
	line[0].color=0xffffffff;
	line[1].color=0xffffffff;

}
SDELog.WriteMessage("...закончена");
//	id_galaxy=engine->LoadVertexBuffer(&v_galaxy,sizeof(v_galaxy),TVERTEXXYZ|TVERTEXDIFFUSE);

//	tar_i=engine->LoadVertexBuffer(&v_tar,sizeof(v_tar),D3DFVF_XYZ|D3DFVF_TEX1);
//	tar_tex=engine->LoadTexture("Base\\Images\\target3.bmp");

//	target_enemy_buf1=engine->LoadVertexBuffer(&horizont,sizeof(horizont),D3DFVF_XYZ|D3DFVF_DIFFUSE);
//	target_enemy_buf2=engine->LoadVertexBuffer(&ugol,sizeof(ugol),D3DFVF_XYZ|D3DFVF_DIFFUSE);
	
// Загрузка по порядку:
// 1 Звезда
// 2 Планета
// 3 кобра :)
// 4 станция
// 5 viper
// 6 крейсер
// 7 ракета
// 8 контейнер
// 9 сфера

//	tObjResource tmp;
//	tmp.m_BB=0;
//	tmp.m_BSv=0;
//	tmp.m_BSi=0;
//	tmp.m_tex=0;
//	tmp.p_d3dx_mesh=NULL;
//	string name="base\\models\\x\\";
//	string n=name+"planet"+".x";
//	tmp.p_d3dx_mesh=engine->LoadMeshFromX(n,1,tmp.p_d3dx_mesh);
//	m_Res.insert("planet",tmp);

// Объект с нулевым индексом будет пустым
/*
	m_Res.push_back(tmp);

	tmp.p_d3dx_mesh=engine->LoadMeshFromX("base\\models\\x\\star.x",1.0f/2.0f,tmp.p_d3dx_mesh);
	tmp.m_tex=engine->LoadTexture("base\\images\\could.bmp");
	tmp.m_BB=CreateBoundBox(tmp.p_d3dx_mesh);
	m_Res.push_back(tmp);// 1 индекс

	tmp.p_d3dx_mesh=engine->LoadMeshFromX("base\\models\\x\\zemla.x",1.0f/2.4f,tmp.p_d3dx_mesh);
	tmp.m_tex=engine->LoadTexture("base\\images\\map.bmp");
	tmp.m_BB=CreateBoundBox(tmp.p_d3dx_mesh);
	m_Res.push_back(tmp);// 2 индекс

	tmp.p_d3dx_mesh=engine->LoadMeshFromX("base\\models\\x\\kobra.x",1.0f,tmp.p_d3dx_mesh);
	tmp.m_BB=CreateBoundBox(tmp.p_d3dx_mesh);
	tmp.radius=CreateBoundSphere(tmp.p_d3dx_mesh,tmp.m_BSv,tmp.m_BSi,tmp.m_NumVertices,tmp.m_NumFaces);
	tmp.id_fire=engine->LoadVertexBuffer(&v_fire,sizeof(v_fire),TVERTEXXYZ|TVERTEXDIFFUSE);
	m_Res.push_back(tmp);// 3 индекс

	tmp.p_d3dx_mesh=engine->LoadMeshFromX("base\\models\\x\\station.x",0.010f,tmp.p_d3dx_mesh);
	tmp.m_tex=engine->LoadTexture("base\\images\\station.bmp");
	tmp.m_BB=CreateBoundBox(tmp.p_d3dx_mesh);
	tmp.radius=GetMax(tmp.p_d3dx_mesh);
	m_Res.push_back(tmp);// 4 индекс

	tmp.p_d3dx_mesh=engine->LoadMeshFromX("base\\models\\x\\shokar1.x",0.05f,tmp.p_d3dx_mesh);
	tmp.m_BB=CreateBoundBox(tmp.p_d3dx_mesh);
//	tmp.radius=CreateBoundSphere(tmp.p_d3dx_mesh,tmp.m_BSv,tmp.m_BSi,tmp.m_NumVertices,tmp.m_NumFaces);
	m_Res.push_back(tmp);// 5 индекс

	tmp.p_d3dx_mesh=engine->LoadMeshFromX("base\\models\\x\\membar.x",1.0f,tmp.p_d3dx_mesh);
	m_Res.push_back(tmp);// 6 индекс

	tmp.p_d3dx_mesh=engine->LoadMeshFromX("base\\models\\x\\missile.x",1.0f,tmp.p_d3dx_mesh);
	m_Res.push_back(tmp);// 7 индекс

	tmp.p_d3dx_mesh=engine->LoadMeshFromX("base\\models\\x\\rubish.x",1.0f,tmp.p_d3dx_mesh);
	m_Res.push_back(tmp);// 8 индекс

	tmp.p_d3dx_mesh=engine->LoadMeshFromX("base\\models\\x\\boundsph.x",1.0f,tmp.p_d3dx_mesh);
	m_Res.push_back(tmp);// 8 индекс
*/
}
/*
int tResManager::CreateBoundBox(LPD3DXMESH p_mesh){

	BYTE* pVerticies;
	DWORD tNumVertices=p_mesh->GetNumVertices();
	DWORD tNumFaces=p_mesh->GetNumFaces();
	DWORD tFVF=p_mesh->GetFVF();

	p_mesh->LockVertexBuffer(D3DLOCK_NOSYSLOCK,&pVerticies);

	float Xmin,Xmax,Ymin,Ymax,Zmin,Zmax;
	Xmin=Xmax=Ymin=Ymax=Zmin=Zmax=0;

	for(DWORD i=0; i<tNumVertices; i++ ){
		//Вычисление смещение в вертекс-буфере
		DWORD Offset = i * D3DXGetFVFVertexSize(tFVF);
		my_coord = (COORDS*)&pVerticies[Offset];
		if (Xmin>my_coord->x) Xmin=my_coord->x;
		if (Xmax<my_coord->x) Xmax=my_coord->x;
		if (Ymin>my_coord->y) Ymin=my_coord->y;
		if (Ymax<my_coord->y) Ymax=my_coord->y;
		if (Zmin>my_coord->z) Zmin=my_coord->z;
		if (Zmax<my_coord->z) Zmax=my_coord->z;
	}
	p_mesh->UnlockVertexBuffer();

	for(int j=0;j<16;j++){
		v_cub[j].pos.x=(((4&ind[j])==0)?Xmin:Xmax);
		v_cub[j].pos.y=(((2&ind[j])==0)?Ymin:Ymax);
		v_cub[j].pos.z=(((1&ind[j])==0)?Zmin:Zmax);
	}
	int id=engine->LoadVertexBuffer(&v_cub,sizeof(v_cub),TVERTEXXYZ|TVERTEXDIFFUSE);
	return id;
	
}
*/
/*
float tResManager::CreateBoundSphere(LPD3DXMESH p,int &v,int &i,DWORD &num_v,DWORD &num_f){
LPD3DXMESH p_mesh=NULL;
float m=GetMax(p);

p_mesh=engine->LoadMeshFromX("base\\models\\x\\boundsph.x",m,p_mesh);
//	BYTE *tmpVerticies,*tmpVerticiesInd;
	DWORD tmpNumVertices;
	DWORD tmpNumFaces;
	DWORD tmpFVF;

	tmpNumVertices=p_mesh->GetNumVertices();
	tmpNumFaces=p_mesh->GetNumFaces();
	tmpFVF=p_mesh->GetFVF();
	num_v=tmpNumVertices;
	num_f=tmpNumFaces;
	int s=D3DXGetFVFVertexSize(tmpFVF);
	s*=tmpNumVertices;
	int s2=tmpNumFaces*3*2;
	LPDIRECT3DINDEXBUFFER8 tib=NULL;
	LPDIRECT3DVERTEXBUFFER8 tvb=NULL;
	p_mesh->GetVertexBuffer(&tvb);
	p_mesh->GetIndexBuffer(&tib);

	BYTE* tmpVer2;
	tvb->Lock(0,s,&tmpVer2,D3DLOCK_NOSYSLOCK);
	v=engine->LoadVertexBuffer(tmpVer2,s,tmpFVF);
	tvb->Unlock();

	tib->Lock(0,s2,&tmpVer2,D3DLOCK_NOSYSLOCK);
	i=engine->LoadIndexBuffer(tmpVer2,s2,D3DFMT_INDEX16);//tib,s2,D3DFMT_INDEX16);
	tib->Unlock();
p_mesh->Release();

return m;
}
*/
void tResManager::RMDestroy(){
	/*
	TObjRes::iterator i;
	for(i=m_Res.begin();i!=m_Res.end();i++){
//		tmp=(*i).second;
//		delete tmp;
		if ((*i).p_d3dx_mesh) (*i).p_d3dx_mesh->Release();
// В принципе Деструктор Вертексного буфера сам уничтожает 
// список буферов, но для порядку:
		if ((*i).m_BB) engine->ReleaseVertexBuffer((*i).m_BB);
	}
	m_Res.clear();
	*/
}

/*
double tResManager::GetMax(LPD3DXMESH p_mesh)
{
	BYTE* pVerticies;
	DWORD tNumVertices=p_mesh->GetNumVertices();
	DWORD tNumFaces=p_mesh->GetNumFaces();
	DWORD tFVF=p_mesh->GetFVF();

	p_mesh->LockVertexBuffer(D3DLOCK_NOSYSLOCK,&pVerticies);

	float Xmin,Xmax,Ymin,Ymax,Zmin,Zmax;
	Xmin=Xmax=Ymin=Ymax=Zmin=Zmax=0;

	for(DWORD i=0; i<tNumVertices; i++ ){
		//Вычисление смещение в вертекс-буфере
		DWORD Offset = i * D3DXGetFVFVertexSize(tFVF);
		my_coord = (COORDS*)&pVerticies[Offset];
		if (Xmin>my_coord->x) Xmin=my_coord->x;
		if (Xmax<my_coord->x) Xmax=my_coord->x;
		if (Ymin>my_coord->y) Ymin=my_coord->y;
		if (Ymax<my_coord->y) Ymax=my_coord->y;
		if (Zmin>my_coord->z) Zmin=my_coord->z;
		if (Zmax<my_coord->z) Zmax=my_coord->z;
	}
	p_mesh->UnlockVertexBuffer();
double max=0;
Xmax=abs(Xmax);Xmin=abs(Xmin);
Ymax=abs(Ymax);Ymin=abs(Ymin);
Zmax=abs(Zmax);Zmin=abs(Zmin);
max=Xmax;
if (max<Xmin) max=Xmin;
if (max<Zmin) max=Zmin;
if (max<Ymin) max=Ymin;
if (max<Ymax) max=Ymax;
if (max<Zmax) max=Zmax;
return max;
}
*/
