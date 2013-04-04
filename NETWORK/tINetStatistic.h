#pragma once

#include "../phisics/tpointer.h"

class tINetStatistic:public tPointer{
public:
	virtual float GetAvgTimeRecv()=0;//������� ����� ����� ������ �������
	virtual float GetAvgTimeSend()=0;//������� ����� ����� ��������� �������
	virtual float GetAvgTimePing()=0;//������� ����� �������� ������(ping)
	virtual float GetAvgTimeServerWork()=0;//������� ����� �������� ������ ��������
	virtual float GetNumPacketsLost()=0;//���-�� ��������� �������
	virtual int GetNumPackets()=0;
	virtual int GetNumPacketSend()=0;
	virtual int GetNumPacketRecv()=0;
	virtual float GetTrafic()=0;//Kbit per sec. "-1"=����� ���������� - �����������!
	virtual const char* GetServerIP()=0;
	virtual const char* GetClientIP()=0;
	virtual float GetPing(int i)=0;
	virtual float GetServerWorkTime(int i)=0;//����� ������� ����� ������ �� �������
	
	tINetStatistic(void){;}
	virtual ~tINetStatistic(void){;}
};
