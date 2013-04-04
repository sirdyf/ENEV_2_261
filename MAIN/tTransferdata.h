#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <d3dx8math.h>
#include "..\ships\tsShip.h"
#include "..\ships\tsEngine.h"
#include "..\ships\tsWeapon.h"
#include "..\main\tComponents.h"
#include "..\main\tmenu.h"

class tServiceInfo{
public:
	int iUinClient;
	int mode;

	tServiceInfo(){		iUinClient=0;mode=0;	}
    template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & BOOST_SERIALIZATION_NVP(iUinClient);
		ar & BOOST_SERIALIZATION_NVP(mode);
//		ar & BOOST_SERIALIZATION_NVP(dwServerWork);
//		ar & BOOST_SERIALIZATION_NVP(numPacket);
	}
};
// �������� ����� ������ �� ����� 15 �����!!
class tTradeInfo{
	tMenu menuInfo;//������
	int goodsCost[15];// ���������
	int goodsCount[15];// � �������
};
class tNewShipInfo{
	tMenu menuInfo;
	tsShip newShipInfo;
};
class tComponentsInfo{
	tMenu menuInfo;// ���.���������
	tComponents componentInfo; // ����(��������) � ���.����������
//	int cur[15]; // ���.���������
	int type[15];//��� ����������
	int max[15];//��������
};
class tStationMainInfo{
public:
	int iUinSol;// ��� �������������� ����� ������-������
	int iUinPlanet;//��� �������
	int iTechLevel;//"����������� ������� �������-");
	float fPopulation;//"��������� �������-");
	int iPoliticalSystem;//"������������ �����-");
	int pTypePlanet;//"��� �������");
	tStationMainInfo(){
		iUinSol=0;iUinPlanet=0;iTechLevel=0;fPopulation=0;iPoliticalSystem=0;pTypePlanet=0;
	}
	virtual ~tStationMainInfo(){}
    template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & BOOST_SERIALIZATION_NVP(iUinSol);
		ar & BOOST_SERIALIZATION_NVP(iUinPlanet);
		ar & BOOST_SERIALIZATION_NVP(iTechLevel);
		ar & BOOST_SERIALIZATION_NVP(fPopulation);
		ar & BOOST_SERIALIZATION_NVP(iPoliticalSystem);
		ar & BOOST_SERIALIZATION_NVP(pTypePlanet);
	}
};
class tShipInfo{
	tsShip ship;
	tsEngine engine;
	tsWeapon weapon;
	float cash;
	int goods[15];//������
	int equipmentComponents[15];//������������ �������
	tShipInfo(){}
	virtual ~tShipInfo(){}
};
//	Scene->glPrint(100,560,"Station in planet: %s		cash:%.2f cr Tonnage:%.2f",n,World.cam->cash,World.cam->Ship.tonnage);

class tSendData{
public:
	int radius;
	int uin;//����������� �������� ���� ������ ����� �� �������� - ��� ������
	D3DXVECTOR3 pos;
	D3DXVECTOR3 dir;
	D3DXVECTOR3 up;
	tSendData(){//default constructor
//		::ZeroMemory(&cmd[0],sizeof(cmd));
		pos=D3DXVECTOR3(0,0,0);
		dir=D3DXVECTOR3(0,0,1);
		up=D3DXVECTOR3(0,1,0);
		radius=1;uin=0;
	}
	virtual ~tSendData(){}
    template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & BOOST_SERIALIZATION_NVP(radius);
		ar & BOOST_SERIALIZATION_NVP(uin);
		ar & BOOST_SERIALIZATION_NVP(pos.x);
		ar & BOOST_SERIALIZATION_NVP(pos.y);
		ar & BOOST_SERIALIZATION_NVP(pos.z);
		ar & BOOST_SERIALIZATION_NVP(dir.x);
		ar & BOOST_SERIALIZATION_NVP(dir.y);
		ar & BOOST_SERIALIZATION_NVP(dir.z);
		ar & BOOST_SERIALIZATION_NVP(up.x);
		ar & BOOST_SERIALIZATION_NVP(up.y);
		ar & BOOST_SERIALIZATION_NVP(up.z);
	}
};
 //   template<class Archive>
	//void serialize(Archive & ar, const unsigned int version){
	//	ar & BOOST_SERIALIZATION_NVP(udpSocket);
	//	ar & BOOST_SERIALIZATION_NVP(tcpSocket);
	//}
