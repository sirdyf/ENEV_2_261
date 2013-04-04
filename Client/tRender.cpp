#include "tRender.h"
//#include "tNetStatistic.h"

#pragma warning (once:4244)//��������� ��� ������!
#pragma warning (once:4996)
//#pragma warning (once:4305)

//extern HANDLE hPeng;
extern std::string consoleString;
//extern bool bGameOver;




// Tolerance for FLOATs
/*
HRESULT D3DMath_VectorMatrixMultiply( D3DVECTOR& vDest, D3DVECTOR& vSrc,D3DMATRIX& mat){
    FLOAT x = vSrc.x*mat._11 + vSrc.y*mat._21 + vSrc.z* mat._31 + mat._41;
    FLOAT y = vSrc.x*mat._12 + vSrc.y*mat._22 + vSrc.z* mat._32 + mat._42;
    FLOAT z = vSrc.x*mat._13 + vSrc.y*mat._23 + vSrc.z* mat._33 + mat._43;
    FLOAT w = vSrc.x*mat._14 + vSrc.y*mat._24 + vSrc.z* mat._34 + mat._44;   
    if( fabs( w ) < g_EPSILON ) return E_INVALIDARG;
    vDest.x = x/w;vDest.y = y/w;vDest.z = z/w;
return S_OK;
}
*/
//void tRender::Init(boost::intrusive_ptr<tWorld> wrld){
//	this->_world=wrld;
//}

void tRender::SelComponents(tMenu *menu){
	Scene->StartRender();
	StationMainInfo();
	int base=380;
	char* n=0;
	Scene->glPrint(600,base+20,"cur type max");
	for(int i=0;i<menu->GetMaximum()+1;++i){
//		n=_world->mComp.units[i].name;
		Scene->glPrint(30,base-20.0f*i,"%s",n);
//		Scene->glPrint(230,base-20.0f*i,"%.1f",_world->mComp.units[i].cost);
//		n=_world->mComp.units[i].dest;
		Scene->glPrint(300,base-20.0f*i,"%s",n);
//		Scene->glPrint(600,base-20.0f*i,"%d",_world->cam.eqComp[i]);
//		Scene->glPrint(650,base-20.0f*i,"%d",_world->mComp.units[i].types);
//		Scene->glPrint(700,base-20.0f*i,"%d",_world->cam.Ship.eqTypesMax[_world->mComp.units[i].types]);
//		Scene->glPrint(700,base-20.0f*i,"%d",_world->mComp.units[i].max);
	}
/*		int uin;
		int tlevel;
		int max;
		int types; */
	Scene->glPrint(10,base-20.0f*menu->GetCurNum(),"->");

	DrawShip(0);

	Scene->EndRender();
}
void tRender::NewShip(tMenu* menu){
	Scene->StartRender();
	StationMainInfo();
	int base=240;
	Scene->glPrint(50,base+140,"�������� �������:");
	Scene->glPrint(50,base+120,"�����:");
	Scene->glPrint(50,base+100,"���������:");
	Scene->glPrint(50,base+80,"�����:");
	Scene->glPrint(50,base+60,"Max Class Engine:");
	Scene->glPrint(50,base+40,"���.������:");
	Scene->glPrint(50,base+20,"������ ��� �����:");
	Scene->glPrint(50,base+0,"��������:");
//	char* n=0;
//	n=_world->aiGlobal.Ships->mShip[0].name;
	int num=menu->GetCurNum();
/*
	Scene->glPrint(250,base+140,"%s",&_world->aiGlobal.Ships->mShip[num].name[0]);
	Scene->glPrint(250,base+120,"%d",_world->aiGlobal.Ships->mShip[num].massa);
	Scene->glPrint(250,base+100,"%d",_world->aiGlobal.Ships->mShip[num].cost);
	Scene->glPrint(250,base+80,"%.2f",_world->aiGlobal.Ships->mShip[num].tonnage);
	Scene->glPrint(250,base+60,"%d",_world->aiGlobal.Ships->mShip[num].engineClassMax);
	Scene->glPrint(250,base+40,"%d",_world->aiGlobal.Ships->mShip[num].techLevel);
	Scene->glPrint(250,base+20,"%d",_world->aiGlobal.Ships->mShip[num].missileSlots);
	Scene->glPrint(250,base+0,"%.2f",_world->aiGlobal.Ships->mShip[num].rad);
	Scene->glPrint(250,base-20,"%.2f",_world->aiGlobal.Ships->mShip[num].fBaseShield);

	DrawShip(_world->aiGlobal.Ships->mShip[num].gres);
*/
	Scene->EndRender();
}



void tRender::Trade(tMenu* menu){
	Scene->StartRender();
	StationMainInfo();
	int base=380;
	char* n=0;
	int full=menu->GetCurNum()+menu->GetStartNum();
	Scene->glPrint(50,base+20,"������: %d",full);
	Scene->glPrint(220,base+20,"����:");
	Scene->glPrint(300,base+20,"� �������:");
	Scene->glPrint(420,base+20,"��.���.");
	Scene->glPrint(10,base+80,"�������� ������:");
	Scene->glPrint(500,base+20,"������/�������:");
	//n=&_world->mGoods.units[full].desc[0];//!!!!!!!!!!!!!!!!
	int len=strlen(n);
char n1[256]={0};
char n2[256]={0};
	if (len>77){
		n2[0]=0;
		strcat(&n2[0],&n[77]);
		Scene->glPrint(10,base+40.0f,"%s",&n2[0]);
	}
	n1[0]=0;
	strcat(&n1[0],&n[0]);
	n1[77]=0;
	Scene->glPrint(10,base+60.0f,"%s",&n1[0]);
	Scene->glPrint(10,base-20.0f*menu->GetCurNum(),"->");
	float cost=0;
	float delta=0;
/*
	for (int i=0;i<=menu->GetMaximum();++i){
		n=&_world->mGoods.units[i+menu->GetStartNum()].name[0];
		Scene->glPrint(30,base-20.0f*i,"%s",n);
		delta=_world->mGalaxy.aiStar->mStarContainer->mStar->goods[i+menu->GetStartNum()];//��������� � tGalaxy !!!
		cost=_world->mGoods.units[i+menu->GetStartNum()].cost*delta;
		Scene->glPrint(220,base-20.0f*i,"%.2f",cost);
		cost=_world->mGalaxy.aiStar->mStarContainer->mStar->amount[i+menu->GetStartNum()];//��������� � tGalaxy !!!
		Scene->glPrint(350,base-20.0f*i,"%.2f",cost);
		n=&_world->mGoods.units[i+menu->GetStartNum()].meas[0];
		Scene->glPrint(450,base-20.0f*i,"%s",n);
		cost=_world->cam->goods[i+menu->GetStartNum()];
		Scene->glPrint(500,base-20.0f*i,"%.2f",cost);
	}
*/
	Scene->EndRender();
}

bool tRender::Render(){
	if (bGameOver) return false;
	if (Scene->GetFps()>10) return true;
	return false;
}
void tRender::StationMainInfo(){
/*
	curPlanet=_world->mGalaxy.aiStar->mStarContainer->GetNearPlanet();//!!!!!!!!!!
	char* n=&_world->mGalaxy.masOfGalaxy[_world->cam->curStar].name[0];
	Scene->glPrint(200,580,"Star system: `%s`",n);
	n=&curPlanet->obj->name[0];
	Scene->glPrint(100,560,"Station in planet: %s		cash:%.2f cr Tonnage:%.2f",n,_world->cam->cash,_world->cam->Ship.tonnage);
*/
	Scene->glPrint(10,540,"����������� ������� �������-");
	Scene->glPrint(10,520,"��������� �������-");
	Scene->glPrint(10,500,"������������ �����-");
	Scene->glPrint(10,480,"��� �������");
//	Scene->glPrint(10,10,"Trafic Kbit/sec=%.1f",_world->netStat.GetTrafic());
}
void tRender::DrawShip(int num){
//******************************
	float a=cosf(GetTickCount()/1000.1f);
	float b=sinf(GetTickCount()/1000.1f);
		Vector up(a,b,0);
		Vector dir(0,a,b);
//		Vector p(-3,3,15);
		Vector p(3,2,-10);
		Scene->RenderShip(p,dir,up,num);
//******************************
}
void tRender::MainMenu(){
	Scene->StartRender();
	DrawShip(1);
	Scene->glPrint(50,420,"��� ���������� � ��������...");
	Scene->DrawLine2D(0,0.2,1,0.2,Vector(0.5,0.5,0.5));
	Scene->EndRender();
}
void tRender::MainMenu(tMenu* menu,boost::intrusive_ptr<tINetStatistic> ns){
	Scene->StartRender();
	DrawShip(1);
	Scene->glPrint(50,200,consoleString.c_str());
	int base=400;

	Scene->glPrint(50,base+60,"send=%i recv=%i",ns->GetNumPacketSend(),ns->GetNumPacketRecv());
	Scene->glPrint(50,base+40,"UDP packet(send+recv)in sec=%d Trafic Kbit/sec=%.1f",ns->GetNumPackets(),ns->GetTrafic());
	Scene->glPrint(50,base+20,"����:");
	Scene->glPrint(10,base-20.0f*menu->GetCurNum(),"->");
	Scene->glPrint(30,base,"New Game");
	Scene->glPrint(30,base-20,"Load");
	Scene->glPrint(30,base-40,"Save");
	Scene->glPrint(30,base-60,"Options");
	Scene->glPrint(30,base-80,"Exit");

	Scene->glPrint(50,base-120,"Server IP-%s",ns->GetServerIP());
	Scene->glPrint(50,base-140,"Client IP-%s",ns->GetClientIP());
	float y=0,y2=0,dx=0,x2=0,x=0;
	float dx_const=1.0f/100.0f;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	float k=ns->GetAvgTimeRecv();
	Scene->glPrint(50,base-160,"avg time recv=%.2f",k);
	for (int i=1;i<100;i++){
		//[0]-������ ���� [1]-����� �� ������� [2]-������ ���� ����� �������
		// ���� 100 ���� �� �������
		y=ns->GetServerWorkTime(i)/100.0f;//0..100mSec
		y2=ns->GetServerWorkTime(i-1)/100.0f;//0..100mSec
//		dx=ns->avgTime[i][2];//
// 100 ���. * 50 ����.=5000
		//if ((dx!=0)&&(k!=0)){
		//	x2=x+dx_const*k/dx;// ���� ��������� 0<k/dx<1 ����� >2 ???
		//}else{
		//	x2=x+dx_const;
		//}

		x+=dx_const;
		x2=x+dx_const;
		Scene->DrawLine2D(x,0.2f*y2,x2,0.2f*y,Vector(0.9,0.1,0.1));//�������� �� �������
		Scene->DrawLine2D(x2,0,x2,0.2f*y,Vector(0.1,0.3,0.1));//���������

		y=ns->GetPing(i)/100.0f;//0..100mSec
		y2=ns->GetPing(i-1)/100.0f;//0..100mSec
		Scene->DrawLine2D(x,0.2f*y2,x2,0.2f*y,Vector(0.7,0.7,0.7));//������ ����
	}
	Scene->DrawLine2D(0,0.2,1,0.2,Vector(0.5,0.5,0.5));// 20 msec

	Scene->EndRender();
}
void tRender::InStationMain(tMenu* menu){
	Scene->StartRender();
	
	DrawShip(1);

	StationMainInfo();
	int base=400;
//	float dt=_world->netStat.GetAvgTimePacketRecv();

	Scene->glPrint(10, 30, "Elite NewEdge FPS: %d", Scene->GetFps());
//	Scene->glPrint(10,50,"uin=%i send=%i recv=%i",_world->uin,_world->netStat.GetNumPacketSend(),_world->netStat.GetNumPacketRecv());
	Scene->glPrint(50,base+20,"����:");
//	Scene->glPrint(150,base+20,"send=%i recv=%i dtRecv=%.1f",_world->netStat.GetNumPacketSend(),_world->netStat.GetNumPacketRecv(), dt);
//unsigned char str=0;
	Scene->glPrint(10,base-20.0f*menu->GetCurNum(),"->");
	Scene->glPrint(30,base,"����� �� �������");
	Scene->glPrint(30,base-20,"������");
	Scene->glPrint(30,base-40,"��������");
	Scene->glPrint(30,base-60,"��������� �������");
	Scene->glPrint(30,base-80,"������� ������ �������");
	Scene->glPrint(30,base-100,"����� ��������� �������");
	Scene->glPrint(30,base-120,"����� ���������");
	Scene->glPrint(40,base-140,"(����� � ��������)");
	Scene->glPrint(40,base-160,"(�������� �������)");


	Scene->EndRender();
//	Scene->glPrint(10, 30, "CamPos: %.1f, %.1f, %.1f", PosCam.x, PosCam.y, PosCam.z);
}
void tRender::PlanetMap(){
	Scene->StartRender();
/*
//	�������� ��������� ��������� �������
	boost::intrusive_ptr<tStarInterface> iStar=_world->mGalaxy.aiStar->GetInterface();
//	D3DXVECTOR3 tpos=iStar->GetStarPos();//Star
	float tsc=0;float tdist=0;
	boost::intrusive_ptr<tObj> tmpObj;
	Vector pos;

	D3DXVECTOR3 my_pos=D3DXVECTOR3(0,0,0);

	int maxPlanet=iStar->GetNumPlanets();
	
	boost::intrusive_ptr<tPlanet> tmpIterP;

	for (int numP=0;numP<maxPlanet;numP++){
		tmpObj=iStar->GetPlanetObj(numP);

		my_pos=tmpObj->GetPos();
		pos=Vector(my_pos.x,my_pos.y,my_pos.z);
//		tsc=tmpObj->GetRadius()/2.0f;

//		Scene->DrawPlanetMap(pos,"name",false);// ������������� ����� !!!! (-=KAS=-)
// (��� ������� ����� �� ����� ���������)
// � � � � � � � � � � :

// 1.������������ � ������� ���� ���������!
// 2.���� ���� ����� �������� ��� ���������� �� ����� �����, ����� ��������� ��� �������. ��� ����� ����� ���� ���������.
	}
*/
	Scene->EndRender();
}

extern float tStep;
//��� ��������� ���������� ������ ��� ������� �������� ���� ������� ���� ����� �������� ��������
// ���� ��� ��������� ��������� ��������(�.�. ������� ��� 20 ��� � ���) �������� ������������ �������
// ���� ���� ������� �����, ���� ��� ������������, ���� �������� ������������
void tRender::InSpaceMain(boost::intrusive_ptr<tCamera> cam,//�������� �� ����� - �������� ������
						std::list< tSendData > ::const_iterator beg2,
						std::list< tSendData > ::const_iterator end2){
//----------------------------------------------------------------------------
//	����:
//  1.��������� 3� �������
//    1.1 ��������� ��  ����������� ������� ��������
//    1.2 ��������� � ������������� ������� ��������
//  2.��������� 2� �������
//----------------------------------------------------------------------------
//std::list< boost::intrusive_ptr<tObj> >::const_iterator i,beg,end;
// ��������! ��� ������� ���������� �������(!), � �� ��������.

//	if(engine->BeginRender()) {

	D3DXVECTOR3 tp=cam->obj.pos;//->GetPos();
	Scene->Camera->Position.x=tp.x;
	Scene->Camera->Position.y=tp.y;
	Scene->Camera->Position.z=tp.z;
	
	tp=cam->obj.up;//->GetTy();
	Scene->Camera->UpVector.x=tp.x;
	Scene->Camera->UpVector.y=tp.y;
	Scene->Camera->UpVector.z=tp.z;

	tp=cam->obj.dir;//->GetTz();
	Scene->Camera->ViewDir.x=tp.x;
	Scene->Camera->ViewDir.y=tp.y;
	Scene->Camera->ViewDir.z=tp.z;
//	Scene->Camera->Apply();
	Vector PosCam = Scene->Camera->GetPosition();
	Scene->StartRender();

	float fps=Scene->GetFps();
	float dt=1.0f/fps;
	
//	fDeltaTime=dt;//1.0f/30.0f;

	Vector pos,dir,up;//(3,0,-100),dir(0,0,1),up(0,1,0);
	Vector r,c;
		D3DXVECTOR3 my_pos=D3DXVECTOR3(0,0,0);

		Scene->glPrint(30, 580-30, "tStep=%.5f FPS=%.1f CamPos: %.1f, %.1f, %.1f",tStep,fps, PosCam.x, PosCam.y, PosCam.z);
	//Scene->glPrint(10, 30, "Cam: aX=%.5f, aZ=%.5f", _world->cam->aX,_world->cam->aZ);

//	Scene->SetPos(0,0,-10);

	Scene->RenderStarField();

//	Scene->RenderShip(pos,5);
//	pos.x=200; pos.y=200; pos.z=-800;
//	Scene->RenderPlanet(100,pos,6);
//���������� tShipContainer(�� �������� tStarContainer)
//���������� ������ ������������� ���������� - ����� ������:
//���� ����� ����� ����������� ������� >1, �� ��� �������������
//����������,�� ������� ������ ���������� �� � 0, � � ������ ��������
// �������� ������.
//(������:���� ��� ��������� ������� �����,� ����� ��������� �������������
//����������-�����,�� Release() �������� ������ ��������� ����������
//������ ���,��� ��� ����������!!!)
// ������������ ������� ************************************
//		boost::intrusive_ptr<tShip> tmpShip;
//		boost::intrusive_ptr<tShip> tmpShip2;
//		boost::intrusive_ptr<tObj> tmpObj;
//		tmpShip=0;tmpShip2=0;
//��������������� ������������: ������ ����� ��� ����������
/*		std::list< boost::intrusive_ptr<tFormations> >::iterator vP=pEng->formationsObjList.begin();
		while (vP!=pEng->formationsObjList.end()){
			my_pos=(*vP)->obj->GetPos();
			pos.x=my_pos.x;pos.y=my_pos.y;pos.z=my_pos.z;
			Scene->RenderPlanet(1,pos,6);
			vP++;
		}
*/
		//if (_world->cam->HaveTarget()){
		//	tmpObj=_world->cam->GetTargetObj();
		//}

//--------network---***************************
//	Scene->glPrint(30,580-60,"UDP=%d Kbit/sec=%.1f",_world->netStat.GetNumPacketRecv(),_world->netStat.GetTrafic());
//		Scene->glPrint(30,580-60,"UDP= Kbit/sec=");
// ������ �����������
/*
		if (uinClient==1){//���� ������ - ������ �������
			pos=sTransfData[1].pos;
			dir=sTransfData[1].dir;
			up=sTransfData[1].up;
			Scene->RenderShip(pos,dir,up,1,1);//tmpShip->Ship.gres,tmpShip->Ship.rad);
			Scene->glPrint(350,350,"%.1f %.1f %.1f",pos.x,pos.y,pos.z);
		}
		if (uinClient==2){//���� ������ - �������
			pos=sTransfData[0].pos;
			dir=sTransfData[0].dir;
			up=sTransfData[0].up;
			Scene->RenderShip(pos,dir,up,1,1);//tmpShip->Ship.gres,tmpShip->Ship.rad);
			Scene->glPrint(350,370,"%.1f %.1f %.1f",pos.x,pos.y,pos.z);
		}
		Scene->glPrint(250,390,"Exch=%d",tNetExchange);
		Scene->glPrint(350,390,"Recv=%d",tNetRecv);
		Scene->glPrint(450,390,"Send=%d",tNetSend);
		Scene->DrawRadarLabel(pos);
*/
/*
	beg2=pEng->frameObjList.begin();
	end2=pEng->frameObjList.end();
	while(beg2!=end2){
		pos=(*beg2)->pos;
		dir=(*beg2)->tz;
		up=(*beg2)->ty;
		Scene->RenderShip(pos,dir,up,1,10);//tmpShip->Ship.gres,tmpShip->Ship.rad);
		Scene->DrawRadarLabel(pos);
		++beg2;
	}
*/
//-----------------
//::WaitForSingleObject(hPeng,INFINITE);
//	Scene->glPrint(30,580-90,"Ship %i",_world->frameObjList.size());
//std::list< tSendData > ::const_iterator beg2,end2;

//	Scene->glPrint(130,580-90,"fObjList2 %i",_world->fObjList2.size());
	
//std::list< boost::intrusive_ptr<tObj> > ::const_iterator beg3=0,end3=0;
//	beg2=_world->fObjList2.begin();
//	end2=_world->fObjList2.end();
	//end3=pEng->frameObjList.end();
	Vector v1,v2,v3;
//	D3DXVECTOR3 dir=D3DXVECTOR3(0,0,0);
//	D3DXVECTOR3 up=D3DXVECTOR3(0,0,0);
	float stp=0,deltaV=0,u1=0,u2=0;
	int debug=0;
	while(beg2!=end2){// �������� �� ������
		v1=(*beg2).pos;
		u1=(*beg2).uin;
//			Scene->glPrint(210,580-90,"Position player1 %f %f %f",v1.x,v1.y,v1.z);
		dir=(*beg2).dir;
		up=(*beg2).up;
		//if (u1!=_world->uin){
		//	Scene->RenderShip(v1,dir,up,1,10);//tmpShip->Ship.gres,tmpShip->Ship.rad);
		//	Scene->DrawRadarLabel(v1);
		//}
		++beg2;
	}
	if (debug==0){
		int error=1;
	}
//ReleaseMutex(hPeng);

//-----------------��������� ��������
/*
		// �������� ��������� �� �������
		boost::intrusive_ptr<tShipsInterface> iShips=_world->aiGlobal.Ships->GetInterface();
		int maxShips=iShips->GetNumShips();
//		Scene->glPrint(10, 50, "Max ship: %d", maxShips);
		if (bGameOver) Scene->glPrint(350,350,"G A M E   O V E R");

		float rad=0;
	for (int j=0;j<maxShips;j++){
		tmpShip=iShips->GetNextShip(tmpShip);

		if (tmpShip->obj==tmpObj) tmpShip2=tmpShip;

		my_pos=tmpShip->obj->GetPos();
		pos=Vector(my_pos.x,my_pos.y,my_pos.z);

		my_pos=-tmpShip->obj->tz;
		dir=Vector(my_pos.x,my_pos.y,my_pos.z);
		r=dir*5.0f;
		
		Scene->DrawLine(pos,pos+r,Vector(0,0,1));//�������-� ���-�: ��� Z
		my_pos=tmpShip->obj->ty;
		up=Vector(my_pos.x,my_pos.y,my_pos.z);
		r=up*5.0f;
		
		Scene->DrawLine(pos,pos+r,Vector(0,1,0));//�������-� ���-�: ��� Y

		rad=tmpShip->obj->GetRadius();
//		Scene->RenderShip(pos,dir,up,5,rad);
		Scene->RenderShip(pos,dir,up,tmpShip->obj->gRes,tmpShip->obj->GetRadius());//tmpShip->Ship.gres,tmpShip->Ship.rad);

//		Scene->RenderPlanet(rad,pos,6);//!!!!!!!
//		Scene->RenderPlanet(1,pos-dir*10.0f,6);//!!!!!!!
		
		if (tmpShip->IsFire()) {
			Scene->DrawLine(pos,pos-dir*500.0f,Vector(1,0,0));//laser
		}else{
			if (tmpShip->HaveTarget()) {
				my_pos=tmpShip->GetTargetPos();
				r=Vector(my_pos.x,my_pos.y,my_pos.z);
				Scene->DrawLine(pos,r,Vector(0.1f,0.1f,0.1f));
			}
		}
		if (_world->cam->HaveTarget()){
			my_pos=_world->cam->GetTargetPos();
			tmpObj=_world->cam->GetTargetObj();
			r=Vector(my_pos.x,my_pos.y,my_pos.z);
			Scene->DrawLine(r+Vector(-2,-2,0),r+Vector(2,2,0),Vector(1,1,1));
			Scene->DrawLine(r+Vector(-2,2,0),r+Vector(2,-2,0),Vector(1,1,1));
			Scene->glPrint(150,250,"ax Value=%.5f",tmpObj->inertX.Value);
			Scene->glPrint(150,270,"az Value=%.5f",tmpObj->inertZ.curValue);
//------------------
			if (tmpShip2){
				if (tmpShip2->tarLookMy) Scene->glPrint(150,150,"tarLookMy=true");
				else Scene->glPrint(150,150,"tarLookMy=false");
				Scene->glPrint(150,170,"tarLookAngle=%.5f",tmpShip2->tarLookAngle);

//				Scene->glPrint(150,170,"tarDir=%.5f",tmpShip2->tarDir);
				Scene->glPrint(150,190,"status=%d",tmpShip2->status._status);
				Scene->glPrint(150,210,"shield=%.1f",tmpShip2->obj->baseShield);

//				Scene->glPrint(10,150,"aZ=%.5f",tmpShip2->aZ);
//				Scene->glPrint(300,150,"aX=%.5f",tmpShip2->aX);
				D3DXVECTOR3 tdV=_world->cam->GetPos()-tmpShip2->GetPos();
				float td=D3DXVec3Length(&tdV);
				Scene->glPrint(800/2-4*16,600-20,"dist=%.2f",td);
			}
//------------------Z
			//Scene->glPrint(10,70,"Z Value=%.5f",tmpObj->inertZ.Value);
			//Scene->glPrint(10,90,"Z V=%.5f",tmpObj->inertZ.curValue);
			//Scene->glPrint(10,110,"ZmaxV=%.5f",tmpObj->inertZ.maximum);
			//Scene->glPrint(10,130,"ZmaxVP=%.5f",tmpObj->inertZ.maxPercent);
//------------------X
//			Scene->glPrint(300,70,"X Value=%.5f",tmpObj->inertX.Value);
//			Scene->glPrint(300,90,"X V=%.5f",tmpObj->inertX.curValue);
//			Scene->glPrint(300,110,"XmaxV=%.5f",tmpObj->inertX.maximum);
//			Scene->glPrint(300,130,"XmaxVP=%.5f",tmpObj->inertX.maxPercent);
//------------------Speed
			//Scene->glPrint(300,70,"inertSpeed.Value=%.5f",tmpObj->inertSpeed.Value);
			//Scene->glPrint(300,90,"inertSpeed.curValue=%.5f",tmpObj->inertSpeed.curValue);
			//Scene->glPrint(300,110,"inertSpeed.maximum=%.5f",tmpObj->inertSpeed.maximum);
			//Scene->glPrint(300,130,"inertSpeed.maxPercent=%.5f",tmpObj->inertSpeed.maxPercent);
//------------------
		}
		Scene->DrawRadarLabel(pos);
	}
//---------------����� ��������� ��������
*/
//*****************����������:
	float pr=cam->GetSpeedPercent();
	Scene->DrawIndicator(pr, 5, 10, "speed");
//	pr=_world->cam->energy;
	Scene->DrawIndicator(pr,5,30,"Energy");
//	pr=_world->cam->obj->GetShield()*10.0f;
	Scene->DrawIndicator(pr,5,50,"Shield");
//---------------------------
//	if (ttObj) {
//		my_pos=ttObj->GetPos();
//		Vector rr=Vector(my_pos.x,my_pos.y,my_pos.z);

//		Scene->DrawLine(rr-Vector(20.0f,0.0f,0.0f),rr+Vector(20.0f,0.0f,0.0f),Vector(0.5f,0.5f,0.5f));
//		Scene->DrawLine(rr-Vector(0.0f,20.0f,0.0f),rr+Vector(0.0f,20.0f,0.0f),Vector(0.5f,0.5f,0.5f));
//		Scene->DrawLine(rr-Vector(0.0f,0.0f,20.0f),rr+Vector(0.0f,0.0f,20.0f),Vector(0.5f,0.5f,0.5f));

//		Scene->RenderPlanet(10.0f/2.0f,rr,6);
//	}
// ------------____��������� ����������� �������___------------
	//std::list< tSendData > ::const_iterator iPlanetS,iPlanetE;
	//iPlanetS=_world->lBigObj.begin();
	//iPlanetE=_world->lBigObj.end();
	//float rP=0;
	//D3DXVECTOR3 posP=D3DXVECTOR3(0,0,0);
	//while (iPlanetS!=iPlanetE){
	//	rP=(*iPlanetS).radius;
	//	posP=(*iPlanetS).pos;
	//	Scene->RenderPlanet(rP,posP,2);
	//	iPlanetS++;
	//}
/*
float dist=0;
//	�������� ��������� ��������� �������
	boost::intrusive_ptr<tStarInterface> iStar=_world->mGalaxy.aiStar->GetInterface();
//	D3DXVECTOR3 tpos=iStar->GetStarPos();//Star
	float tsc=0;float tdist=0;
	int maxPlanet=iStar->GetNumPlanets();
	
	boost::intrusive_ptr<tPlanet> tmpIterP;

	for (int numP=0;numP<maxPlanet;numP++){
		tmpObj=iStar->GetPlanetObj(numP);
		tsc=tmpObj->GetRadius();// /2.0f;
		my_pos=tmpObj->GetPos();
		pos=Vector(my_pos.x,my_pos.y,my_pos.z);
		Scene->RenderPlanet(tsc,pos,6);
	}
	tmpObj=iStar->GetNearStation();
	my_pos=tmpObj->GetPos();
	dist=D3DXVec3Length(&my_pos);
	pos=Vector(my_pos.x,my_pos.y,my_pos.z);
//	Scene->glPrint(300,150,"distStation=%.1f",dist);
	Scene->glPrint(300,200,"distStation=%.1f",fDebug);
//	Scene->glPrint(300,220,"Shield=%.1f",_world->cam->obj->GetShield());
	if (iStar->StationZone()){
	// -----------------��������� �������-------------------------------
		my_pos=-tmpObj->tz;
		dir=Vector(my_pos.x,my_pos.y,my_pos.z);

		my_pos=tmpObj->ty;
		up=Vector(my_pos.x,my_pos.y,my_pos.z);

		Scene->RenderShip(pos,dir,up,6,20.0f);
//		Scene->RenderPlanet(20,pos,6);
//				if (tdist<g_ZDS){// ������� ����� � ���� �������� ������
				// ������ ��������� �������
				// ��������� ����������� ����� ��� ��������
				// ��������� ����� ��� ��������
//					}
	}

//-------------------------��������� �������������� ��������(����,������,...)
//	beg=Others->objList.begin();end=Others->objList.end();
//bool md=false;
//	for(i=beg;i!=end;++i){
//		md=(*i)->mustDestroy;
//		my_pos=(*i)->GetPos();
//		pos=Vector(my_pos.x,my_pos.y,my_pos.z);
//		Scene->RenderPlanet(1,pos,6);
//	}
	Scene->glPrint(1, 580, "Elite NewEdge FPS: %d", Scene->GetFps());//,pEng->deltaTime);

//	Scene->glPrint(1, 580, "Elite NewEdge FPS: %d:", Scene->GetFps());
//-----------------------------------------------------------------
	//if (_world->cam->IsFire()){
	//	my_pos=_world->cam->GetPos();
	//	pos=Vector(my_pos.x,my_pos.y,my_pos.z);

	//	my_pos=_world->cam->obj->tz;
 //		dir=Vector(my_pos.x,my_pos.y,my_pos.z);
	//	r=dir*100.0f;

	//	Scene->DrawLine(pos-Vector(-2.0f,-5.0f,0),pos+r,Vector(1.0f,1.0f,0));//�������-� ���-�: ��� Y
	//}
//-----------------------------------------------------------------
	float ab=0.03f;
	Scene->DrawLine2D(0.5-ab,0.5f,0.5f+ab,0.5f,Vector(1,1,1));
	Scene->DrawLine2D(0.5,0.5f-ab,0.5f,0.5f+ab,Vector(1,1,1));
//-----------------------------------------
//	if (_world->cam->target){
//
//		//my_pos=_world->cam->GetTargetPos();
//		tmpObj=_world->cam->GetTargetObj();
//		my_pos=tmpObj->GetPos();
////		pos.x=my_pos.x;pos.y=my_pos.y;pos.z=my_pos.z;
//		pos=Vector(my_pos.x,my_pos.y,my_pos.z);
//		my_pos=-tmpObj->tz;
//		dir=Vector(my_pos.x,my_pos.y,my_pos.z);
//		my_pos=tmpObj->ty;
//		up=Vector(my_pos.x,my_pos.y,my_pos.z);
//
//		Scene->RenderShipPreview(pos,dir,up,tmpObj->gRes);
//	}
//-----------------------------------------
//	Sleep(5);
*/
	Scene->EndRender();
//		engine->EndRender();
//msvcrt.lib(MSVCR80.dll) : error LNK2005: _sprintf already defined in LIBCMTD.lib(sprintf.obj)	
//msvcprt.lib(MSVCP80.dll) : error LNK2005: "public: char const * __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >::c_str(void)const " (?c_str@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QBEPBDXZ) already defined in AI_Group.obj
//Error	32	error LNK2001: unresolved external symbol __CrtDbgReportW	libcpmtd.lib
// libcmtd, libcpmtd
// msvcrt, msvcprt

/*
Vector sp = {-10,0,-30};
	Scene->StartRender();

	Vector dir, up, pos;
	
	dir.x	= 1;	dir.y		= 0;	dir.z	= 1;
	up.x	= 0;	up.y		= 1;	up.z	= 0;
	pos.x	= 0;	pos.y		= 0;	pos.z	= -10;

	//sp.x = sp.x; sp.y = sp.y; sp.z = sp.z + Scene->delta_time * 5;	
	
	Scene->RenderShip(pos, dir, up, 5);
	
	//Scene->TestRender(sp);

	pos.x = 200; pos.y = 200; pos.z = -800;
	Scene->RenderPlanet(100, pos, 6);

	Scene->RenderStarField();

	
	Vector start, end;
	start.x = -3; start.y = 0; start.z = -10;
	end.x = 3; end.y = 0; end.z = -10;
	Scene->DrawLine(start, end);

	start.x = 0; start.y = -2; start.z = -10;
	end.x = 0; end.y = 2; end.z = -10;
	Scene->DrawLine(start, end);

	Vector PosCam = Scene->Camera->GetPosition();
	Scene->glPrint(10, 30, "CamPos: %f, %f, %f", PosCam.x, PosCam.y, PosCam.z);
	Scene->glPrint(10, 10, "Elite NewEdge FPS: %d", Scene->GetFps());

	for(float i=0 ; i<1.1; i=i+0.1)
		Scene->DrawLine2D(0,0,i,0.9);

	Scene->EndRender();
*/
}
