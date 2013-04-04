#pragma once
#include "..\phisics\tpointer.h"

class tINetworkServer :	public tPointer{
	
public:
	virtual bool ClientIsUsed(int )=0;
	virtual int NewClient()=0;
	virtual void ClientRecvData(int,char* buff,int sz)=0;

	//�����,� ����������� �� ��������� �������, ���� ������������ ������������ ������,
	//���� ���� ������ ���������� ������ ��� �������� ��������.
	// ��������:
	// ����� ������ ����� ������������ ������, ������� ��������� ����� ������ �� ���� ����,���
	// ������ � ������������� ������� ����� ������������ �������� �������� � ������� ��������������� �������.
	virtual int GetData(int,char*)=0;

	virtual void PrepareData()=0;//����� ���������������� ������ ��� �������� ��������

	tINetworkServer(void){};
	virtual ~tINetworkServer(void){};
};
