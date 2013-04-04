// AI_Ships.cpp: implementation of the AI_Ships class.
//
//////////////////////////////////////////////////////////////////////

#include "AI_Ships.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


AI_Ships::~AI_Ships(){}

bool AI_Ships::CheckCameraFire(){
return false;
/* !!!
	bool dead=false;
	D3DXVECTOR3 t=D3DXVECTOR3(0,0,0);
	std::list< boost::intrusive_ptr<tShip> >::iterator iter=freeShipsContainer->mShips.begin();
	bool fll=false;
	float dam=0;
	int iGr=0;
	D3DXMATRIX inv,matView;
	D3DXMatrixIdentity(&inv);
	D3DXMatrixIdentity(&matView);

	D3DXVECTOR3 eye;
	eye=camera->GetPos()+camera->obj->tz;
	D3DXMatrixLookAtLH (&matView, &camera->GetPos(),&eye,&camera->obj->ty);

	while (iter!=freeShipsContainer->mShips.end()){//�������� �� ������ � �������?
//		fl=CheckHit(camera,(*iter)->obj);// ��� ������ ���� ������ �������� �� ������� �������!!!
		t=(*iter)->GetPos();
		D3DMath_VectorMatrixMultiply( t, t,matView);

		if ((t.z>0)&&(t.z<camera->GetWeaponDist())){
			t.z=0;
			float len=D3DXVec3Length(&t);//��������� �� ��� Z
			float rad=(*iter)->obj->GetRadius();//*10.0f;
			if (len<rad){
				dam=camera->GetWeaponDamage()*fDeltaTime;//*500.0f;
				dead=(*iter)->Hits(dam);
				if (dead) {
//					CheckBonus(camera);
					(*iter)->obj->mustDestroy=true;
				}
				fll=HitToGroup((*iter)->GetIdGroup(),camera->obj);//����������,����� ���������� ��������� �� ������?
// 				iGr=CheckHitGroup((*iter),camera->obj);
//				if (iGr) {
//					AddEventGroup(iGr);
//					fll=true;
//				}
			}
		}
		iter++;
	}
	return fll;
*/
}

bool AI_Ships::CheckHits(){
	// ��������� ��� � ���� �����
	int iGr=0;
	bool fll=false,fl=false,dead=false;
	float dam=0;
	std::list< boost::intrusive_ptr<AI_Group> >::const_iterator grI=groupShips.begin();
	std::list< boost::intrusive_ptr<tShip> >::const_iterator allShips,start,end;
	D3DXVECTOR3 t=D3DXVECTOR3(0,0,0);
	int id1=0,id2=0;
/* !!!
	if (camera->IsFire()) {
		fl=CheckCameraFire();// ������ � ����-�� ������
		if (fl) fll=true;
	}
*/
	// + check hits in station + check hits in others, mine - ? rokets - ?
	start=freeShipsContainer->mShips.begin();
	end=freeShipsContainer->mShips.end();
	while (grI!=groupShips.end()){
//	!!!		(*grI)->CheckHit(camera);//�������� ��������� "�������-������"
//	!!!		dead=camera->obj->mustDestroy;//IsDead();
//	!!!		if (dead) bGameOver=true;
		id1=(*grI)->GetUin();
// ���������: ������ ����������� ����� ��������� ��������� ����!!(aZ!!) ???
		allShips=start;
		while (allShips!=end){
			id2=(*allShips)->GetIdGroup();
			if (id1==id2) {
				allShips++;
				continue;//���������� "�����"
			}
			fl=(*grI)->CheckHit((*allShips));
			if (fl) {
				fll=(*grI)->AddEnemy((*allShips)->obj);
				if (fll) {
					(*grI)->needDM=true;
					//SDELog.WriteMessage("Group %d needDM set true(hits from enemy)",(*grI)->GetUin());
				}
			}
			allShips++;
		}
		grI++;
	}
return fll;
}
bool AI_Ships::CheckHit(boost::intrusive_ptr<tEquipment> attack, boost::intrusive_ptr<tObj> enemy){
	D3DXVECTOR3 t=D3DXVECTOR3(0,0,0);
	if (attack->IsFire()){
		t=attack->obj->GetPos();
//�������������� ������� �������
		D3DXMATRIX inv,matWorld;
		D3DXMatrixIdentity(&inv);
		matWorld=attack->obj->GetCurMatrix();//���
		D3DXMatrixTranslation(&inv,t.x,t.y,t.z);
		D3DXMatrixMultiply(&matWorld,&matWorld,&inv);
		D3DXMatrixIdentity(&inv);
		D3DXMatrixInverse(&inv,NULL,&matWorld);
		t=enemy->GetPos();
		D3DMath_VectorMatrixMultiply( t, t,inv);

		if ((t.z>0)&&(t.z<attack->GetWeaponDist())){
			t.z=0;
			float len=D3DXVec3Length(&t);//��������� �� ��� Z
			float rad=enemy->GetRadius();
			if (len<rad){
				return true;
			}
		}
	}
	return false;
}
// ����������� ������ ������� ����������� �������,���������� �����������
// � ���������� ��� � ������ ������!
//boost::intrusive_ptr<AI_Group> 
/*
int AI_Ships::CheckHitGroup(boost::intrusive_ptr<tShip> damageShip,boost::intrusive_ptr<tObj> _enemy){
	// �� �������� �����!!!
	// �������� ������ !!!
	std::list< boost::intrusive_ptr<AI_Group> >::iterator grI=groupShips.begin();
	while (grI!=groupShips.end()){
		if ((*grI)->CheckAccessoryShip(damageShip,_enemy)) return (*grI)->GetUin();
		grI++;
	}
	return false;
}
*/
bool AI_Ships::HitToGroup(int numGroup,boost::intrusive_ptr<tObj> _enemy){
	// �� �������� �����!!!
	// �������� ������ !!!
	bool fl=false;
	int damGroup=0;
	std::list< boost::intrusive_ptr<AI_Group> >::iterator grI=groupShips.begin();
	while (grI!=groupShips.end()){
		damGroup=(*grI)->GetUin();
		if (numGroup==damGroup){
			fl=(*grI)->AddEnemy(_enemy);
			if (fl) AddEventGroup((*grI));
			break;
		}
		grI++;
	}
	return fl;
}
void AI_Ships::AddEventGroup (boost::intrusive_ptr<AI_Group> g){
	std::list< boost::intrusive_ptr<AI_Group> >::iterator iGr;
	iGr=tmpGroup.begin();
	while (iGr!=tmpGroup.end()){
		if (g==(*iGr)) break;
		iGr++;
	}
	if (iGr==tmpGroup.end()){
		tmpGroup.push_back(g);
	}
}
void AI_Ships::AddEventGroup (int g){
	std::list< boost::intrusive_ptr<AI_Group> >::iterator iGr;
	iGr=tmpGroup.begin();
	while (iGr!=tmpGroup.end()){
		if (g==(*iGr)->GetUin()) break;
		iGr++;
	}
	if (iGr==tmpGroup.end()){
		tmpGroup.push_back((*iGr));
	}
}
void AI_Ships::EventGroups(){//��������� ������ ��������� ������
	// �� �������� �����!!!
	// �������� ������ !!!
	std::list< boost::intrusive_ptr<AI_Group> >::const_iterator iGr,end;
	iGr=groupShips.begin();
	end=groupShips.end();
	while (iGr!=end){
		if ((*iGr)->needDM){
			//SDELog.WriteMessage("Group %d has flag DM,Call DM()",(*iGr)->GetUin());
			(*iGr)->DecisionMaking();
			(*iGr)->needDM=false;
		}
		iGr++;
	}
	//���������� tmpGroup
	iGr=tmpGroup.begin();
	end=tmpGroup.end();
	while (iGr!=end){
		//SDELog.WriteMessage("Group %d in event list,Call DM()",(*iGr)->GetUin());
		(*iGr)->DecisionMaking();
		iGr++;
	}
	tmpGroup.clear();
}
bool AI_Ships::CheckAll(){//�������� ���������
	bool fl=false;
	fl=CheckHits();//��������� ��������� � ����� �������
	
	EventGroups();//��������� ������ ������� ���� ������� �������
	return fl;
}
void AI_Ships::Event(){//��������� ��� ������!
	// ��������� ���-�� ������� ��������!
	// ������� ���� �����
	std::list< boost::intrusive_ptr<AI_Group> >::const_iterator iGroup=groupShips.begin(),end=groupShips.end();
	while (iGroup!=end){
		if ((*iGroup)->base->enemyShips.size()){
			(*iGroup)->DecisionMaking();
		}
		iGroup++;
	}
}

boost::intrusive_ptr<tShipsInterface> AI_Ships::GetInterface(){
	return freeShipsContainer;
}
boost::intrusive_ptr<tGroupInterface> AI_Ships::GetInterface(int idGroup){
	std::list< boost::intrusive_ptr<AI_Group> >::const_iterator iGr=groupShips.begin();
	while(iGr!=groupShips.end()){
		if ((*iGr)->GetUin()==idGroup) break;
		iGr++;
	}
	if (iGr==groupShips.end()) return 0;//��� ����� ������
	return (*iGr);
}
void AI_Ships::Init(boost::intrusive_ptr<tStarInterface> sI){//, boost::intrusive_ptr<tEquipment> cmr){
	LoadEquipment();
	pEng->InitEngineList();
	freeShipsContainer=boost::intrusive_ptr<tShipsContainer> (new tShipsContainer);
	starInterface=sI;//!!!ERROR!!!
//	camera=cmr;
}

bool AI_Ships::AddNewShipToGroup(int numGroup){

	int gRes=3;// !!!
	std::list< boost::intrusive_ptr<AI_Group> >::const_iterator iGr=groupShips.begin();
	while(iGr!=groupShips.end()){
		if ((*iGr)->GetUin()==numGroup) break;
		iGr++;
	}
	if (iGr==groupShips.end()) return false;//��� ����� ������
	D3DXVECTOR3 pos=(*iGr)->base->GetComanderPos();//�������� ���������� 1-�� �������

	boost::intrusive_ptr<tShip> tmpShip(new tShip);

	float xS=100.0f*(FLOAT)(rand())/RAND_MAX+1.0f;
	float yS=100.0f*(FLOAT)(rand())/RAND_MAX+1.0f;
	float zS=100.0f*(FLOAT)(rand())/RAND_MAX+1.0f;
	

	tmpShip->Create(pEng->mShip[1],pEng->mEngine[1],mWeapon[0],55,pos+D3DXVECTOR3(xS,yS,zS));// !!! World.resManager->m_Res[gRes].radius,pos);
	freeShipsContainer->mShips.push_back(tmpShip);

	(*iGr)->AddShip(tmpShip);
//	if (!fl) return false;//� ������ ��� ��������� ����!
// ��������!!! ���� AddShip ���� �����, �� ��������� ������:
// freeShipsContainer - ��� �������� tmpShip!
// AddShip ������� ����� ������:�� ������ tObj! (��� �������� ����� � ��������)
	return true;
}
int AI_Ships::GetGroupCount(){
	return groupShips.size();
}

int AI_Ships::CreateGroup(D3DXVECTOR3 pos, bool role){
// ������� ������ ��� ��������
	uinGroupCount++;
	boost::intrusive_ptr<AI_Group> tmpGroup(new AI_Group);
	
	boost::intrusive_ptr<tShip> tmpShip(new tShip);

	float xS=100.0f*(FLOAT)(rand())/RAND_MAX-50.0f; // _dyf_
	float yS=100.0f*(FLOAT)(rand())/RAND_MAX-50.0f;
	float zS=0.0f;//200.0f*(FLOAT)(rand())/RAND_MAX+150.0f;
//srand(GetTickCount());
	int maxShip=pEng->nShip;//AI_Ships::nShip;
//int n=4.0f*(FLOAT)(rand())/RAND_MAX+1.0f;
	AI_Ships::curRND++;
	if (curRND>maxShip+1) curRND=1;
	tmpShip->Create(pEng->mShip[curRND],pEng->mEngine[1],mWeapon[0],0,pos+D3DXVECTOR3(xS,yS,zS));// !!! DYF
	freeShipsContainer->mShips.push_back(tmpShip);

	tmpGroup->Create(uinGroupCount, role,AI_Ships::starInterface);//motivations

	tmpGroup->AddShip(tmpShip);

	groupShips.push_back(tmpGroup);
	return uinGroupCount;
}


void AI_Ships::AsemblyRubish(){
// ���� 1 - ������ ����� ��������
	bool delShips=false;
	std::list< boost::intrusive_ptr<tShip> >::iterator allShips=freeShipsContainer->mShips.begin();
	while (allShips!=freeShipsContainer->mShips.end()){
		if ((*allShips)->obj->mustDestroy) {
			delShips=true;
			allShips=freeShipsContainer->mShips.erase(allShips);
		}else{
			allShips++;
		}
	}
// ������� ���� �����
	bool fl=false;
	std::list< boost::intrusive_ptr<AI_Group> >::iterator iGroup=groupShips.begin();
	while (iGroup!=groupShips.end()){
		fl=(*iGroup)->AssemblyRubbish();//������ ������
		if (fl) {
			pEng->ErasePointsForGroup((*iGroup)->GetUin());
			iGroup=groupShips.erase(iGroup);
		}else{	
			iGroup++;
		}	
	}
}

//		(*iGroup)->CheckEvents();//�������� ������� ��������� ��

void AI_Ships::Processing(){// !!! ��������� ������ � ������
// �������� ���������!
// ������� ������������ �������� �� ������.������->�������� ������ ������

	std::list< boost::intrusive_ptr<AI_Group> >::iterator iGroup=groupShips.begin();
	while (iGroup!=groupShips.end()){
		(*iGroup)->Processing();
		iGroup++;
	}

// ��������� ��������
	boost::intrusive_ptr<tObj> colObj=0;
	std::list< boost::intrusive_ptr<tShip> >::iterator allShips2;
	int id1=0,id2=0;
	bool fl=false;
	std::list< boost::intrusive_ptr<tShip> >::iterator allShips=freeShipsContainer->mShips.begin();
	allShips=freeShipsContainer->mShips.begin();
	while (allShips!=freeShipsContainer->mShips.end()){
// collision object
//		if (pEng->CheckCollision((*allShips)->obj)){//���������� ����� �����������
//			(*allShips)->status.SetStatus(9);
//		}
		colObj=pEng->CheckCollisionBigObj((*allShips)->obj);
		if (colObj){
			if ((*allShips)->HaveConnectContract()==false) {
				(*allShips)->status.SetStatus(9);//���������� ������ ������� �������, ���� ��� �������� "�������� �� ��������"
			}
		}
//------------------------------------------------------�������� ������������ ��������
		id1=(*allShips)->obj->GetIdGroup();
		allShips2=allShips;
		allShips2++;
		while (allShips2!=freeShipsContainer->mShips.end()){
			id2=(*allShips2)->obj->GetIdGroup();
			if (id1!=id2){
				fl=CheckCollisionShip((*allShips),(*allShips2)->obj);
				if (fl){
					(*allShips)->status.SetStatus(9);//���������� ������ ����� �������
				}
			}else{
// ���� ������ ������� � "�������" �����
			}
			allShips2++;
		}
/*	!!!
//-----------------------------------------------------�������� ������������ � �������
		fl=CheckCollisionShip((*allShips),camera->obj);
		if (fl){
			(*allShips)->status.SetStatus(9);//���������� ������ ����� �������
		}
----------------------------------------------------------
*/
		(*allShips)->Processing();// ��������!!! ������ ��� ���� �������� ������ "7"

		allShips++;
	}
//	if (delShips) Event(); //��������� pEngine!

}
//	sample:
//	a) counting all attacking ships and set him target
//	b) used data from pEngine for collisions break
//	c) dinamicaly modify behavior ships in depended afferentations
bool AI_Ships::CheckCollisionShip(boost::intrusive_ptr<tShip> myShip,boost::intrusive_ptr<tObj> enemyObj){
	D3DXVECTOR3 pos,tz,delta;
	float dist=0,ro=0,res=0,r=0;
	boost::intrusive_ptr<tObj> myObj=0;

	if (!myShip) return false;
	myObj=myShip->obj;
	if (myObj->mustDestroy) return false;
	if (!enemyObj) return false;
	if (enemyObj->mustDestroy) return false;


	pos=myObj->pos;// ->GetPos();
	tz=myObj->tz;
	r=myObj->radius;// >GetRadius();
	ro=enemyObj->radius;// >GetRadius();
//	if (ro>r*5.0f) break; // ���������� ������� 5 ������ ������
	delta=pos+tz*r*10.0f-enemyObj->pos;
	dist=D3DXVec3Length(&delta);
	res=r*5.0f+ro*5.0f;
	if (fabsf(res)>fabsf(dist)){
		return true;
	}
return false;
}

bool AI_Ships::LoadEquipment(){

	char mstr[255]={0};
	char* tstr=0;
	int cmd=0,eqType=0;
	nWeapon=-1;
	int tst=0;
	std::string buf;
	FILE* mf=0;
//	mf=fopen("..\\ships\\data\\equipment.str","rt");
	mf=fopen("Data/equipment.str","rt");
	if (mf==NULL) return false;
	while(fgets(mstr,255,mf)){//
		cmd=0;
		if (mstr[strlen(mstr)-1]<33) mstr[strlen(mstr)-1]=0;
		if (mstr[0]==0) continue;
		buf=mstr;
		buf=buf.substr(buf.find_first_not_of("	 "),buf.find_last_not_of("	 ")+1);
		if (buf.find("STRUCT")==0) cmd=2;
		if (buf.find("END")==0) cmd=4;
		if (buf.compare("STRUCT ShipEquipment")==0) cmd=1;
		if (buf.compare("END STRUCT")==0) cmd=3;

		switch(cmd){
		case 1:
			eqType=1;
		break;
		case 2:
			tstr=&mstr[8];
//			if (strcmp(tstr,"engine")==0) {eqType=21;break;}
			if (strcmp(tstr,"weapon")==0) {eqType=22;break;}
//			if (strcmp(tstr,"ship")==0) {eqType=23;break;}
// ���������� ��� ���������
			if (eqType==21) {
//				nEngine++;
			}
			if (eqType==22){
				nWeapon++;
			}
			if (eqType==23){
//				nShip++;
			}
		break;
		case 3:
			eqType=3;
		break;
		case 4:
		break;
		default:
			//��������� � ������ ���� ����������� ���-�
			//���� ���������
			if (eqType==21){
				//if (!mEngine[nEngine].SetValue(buf)){//Unknown Value ?
				//	char b[50]={0};
				//	strcat(b,buf.c_str());
				//	if (!pEng->SetEngineInertValue(nEngine,&b[0])){// inertion ?
				//		//Unknown Value !
				//	}
				//}
			}
			if (eqType==22){
				if (!mWeapon[nWeapon].SetValue(buf)){
					//Unknown Value
				}
			}
			if (eqType==23){
				//if (!mShip[nShip].SetValue(buf)){
					//Unknown Value
				//}
			}
		}		
	}
	fclose(mf);

	return true;
}


void AI_Ships::AttackAll(){

	if (groupShips.size()<2) return;
	std::list< boost::intrusive_ptr<tShip> >::iterator ts;
	std::list< boost::intrusive_ptr<AI_Group> >::iterator iGr;
	iGr=groupShips.begin();
	iGr++;
	ts=freeShipsContainer->mShips.begin();
	(*iGr)->base->enemyShips.push_back((*ts)->obj);
}
/*
// ����������� ������ ������� ����������� �������,���������� �����������
void AI_Ships::CheckHitGroup(boost::intrusive_ptr<tObj> damageShip,boost::intrusive_ptr<tObj> _enemy){
	// �� �������� �����!!!
	// �������� ������ !!!
	std::list< boost::intrusive_ptr<AI_Group> >::iterator grI=groupShips.begin();
	while (grI!=groupShips.end()){
		if ((*grI)->CheckAccessoryShip(damageShip,_enemy)) break;
		grI++;
	}
}
*/
/*
void AI_Ships::CreateGroup(	int ship,int engine,int weapon,
							int gres,int status,int role,
							D3DXVECTOR3 pos){

	boost::intrusive_ptr<tShip> tmpShip(new tShip);

//	tmpShip->obj=pEng->CreateObj(gres,engine, gres.radius -!!! ,pos);
	tmpShip->obj=pEng->CreateObj(gres,engine, 20 ,pos);

	tmpShip->Set(mShip[ship],mEngine[engine],mWeapon[weapon],status,role);
	freeShipsContainer->mShips.push_back(tmpShip);

	boost::intrusive_ptr<AI_Group> tmpGroup(new AI_Group);
	tmpGroup->Create();//motivations
	tmpGroup->AddShip(tmpShip,true);
	groupShips.push_back(tmpGroup);

}

void AI_Ships::CreateShip(int ship,int engine,int weapon,int gres,int status,int role,
				D3DXVECTOR3 pos,boost::intrusive_ptr<tObj> target){

	boost::intrusive_ptr<tShip> tmpShip(new tShip);

//	tmpShip->obj=pEng->CreateObj(gres,engine, m_Res[gres].radius -!!! ,pos);
	tmpShip->obj=pEng->CreateObj(gres,engine,20,pos);

	tmpShip->Set(mShip[ship],mEngine[engine],mWeapon[weapon],status,role);
	tmpShip->New_Target(target);
	freeShipsContainer->mShips.push_back(tmpShip);
//	return tmpShip;

}
*/
/*
bool AI_Ships::CheckHits1(){
	// ��������� ��� � ���� �����
	int iGr=0;
	bool fll=false;
	bool fl=false;
	bool dead=false;
	float dam=0;
	std::list< boost::intrusive_ptr<tShip> >::iterator allShips1;
	std::list< boost::intrusive_ptr<tShip> >::iterator allShips2;
	D3DXVECTOR3 t=D3DXVECTOR3(0,0,0);
	int id1=0,id2=0;
	if (camera->IsFire()) {
		fl=CheckCameraFire();// ������ � ����-�� ������
		if (fl) fll=true;
	}
	// + check hits in camera// + check hits in station// + check hits in others// mine - ?	// rokets - ?
	allShips1=freeShipsContainer->mShips.begin();
	while (allShips1!=freeShipsContainer->mShips.end()){
		allShips2=allShips1;
		allShips2++;
		if ((*allShips1)->IsFire()){
			fl=CheckHit((*allShips1),camera->obj);//�������� ��������� "�������-������"
			if (fl) {
				dam=(*allShips1)->GetWeaponDamage()*fDeltaTime;
				dead=camera->Hits(dam);
				if (dead) {
					bGameOver=true;
//					CheckBonus((*allShips1));
//					camera->obj->mustDestroy=true;
				}
			}
		}
// ���������: ������ ����������� ����� ��������� ��������� ����!!(aZ!!)
// ���������� �� ������ � ��������!? ���� ��������� � ������ - ���������� �����? (noFire)
		while (allShips2!=freeShipsContainer->mShips.end()){
			id1=(*allShips1)->obj->GetIdGroup();
			id2=(*allShips2)->obj->GetIdGroup();
//			if (id1!=id2){ // ���� �� �� ����� ������
				if ((*allShips1)->IsFire()){
					fl=CheckHit((*allShips1),(*allShips2)->obj);//�������� ��������� "�������-�������"
					if (fl) {
						if (id1==id2){
							(*allShips1)->NoFire();
						}else{
							dam=(*allShips1)->GetWeaponDamage()*fDeltaTime;
							dead=(*allShips2)->Hits(dam);
							if (dead) {
								(*allShips2)->obj->mustDestroy=true;
							}
							iGr=CheckHitGroup((*allShips2),(*allShips1)->obj);
							if (iGr) AddEventGroup(iGr);
							fll=true;
						}
					}
				}
				if ((*allShips2)->IsFire()){
					fl=CheckHit((*allShips2),(*allShips1)->obj);//�������� ��������� "�������-�������"
					if (fl) {
						dam=(*allShips2)->GetWeaponDamage()*fDeltaTime;
						dead=(*allShips1)->Hits(dam);
						if (dead) {
							(*allShips1)->obj->mustDestroy=true;
						}
						iGr=CheckHitGroup((*allShips1),(*allShips2)->obj);
						if (iGr) AddEventGroup(iGr);
						fll=true;
					}
				}
//			}
			allShips2++;
		}
		allShips1++;
	}
return fll;
}
*/
