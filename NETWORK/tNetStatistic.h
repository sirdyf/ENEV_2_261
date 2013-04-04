#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <math.h>
#include "../main/tTick.h"
#include "tINetStatistic.h"

class tNetStatistic:public tINetStatistic{
	DWORD dwNetTime;
	float fPacketCount;//����� ���-�� �������
	float fByteSum;
	float fBitPerSec;
	float fPackets;// ������� � ���
	int send;
	int recv;
	int count;//������� ��� ������� ������� (0..99),�.�. ���� ��������� � 100 ��������� �������
	int count_avg;
	float fRecvTimeAvg;
	float fRecvTime;// ����� ����� ��������� ��������

	float times[100];
	float avgTime[100][3];//[0]-������ ���� [1]-����� �� ������� [2]-������ ���� ����� �������

	tTick mTick;
	void CalcAvgTime();
	void AddByte(float);
	int AddTimeSend(void);
	void AddTimeRecv(int,float);
	void AddByteSend(float);
	void AddByteRecv(float);
public:
	std::string serverIP;
	std::string clientIP;

	int Send(float byteSend);
	void Recv(float byteRecv,int count, float time);

	float GetAvgTimeRecv();//������� ����� ����� ������ �������
	float GetAvgTimeSend();//������� ����� ����� ��������� �������
	float GetAvgTimePing();//������� ����� �������� ������(ping)
	float GetAvgTimeServerWork();//������� ����� �������� ������ ��������
	float GetNumPacketsLost();//���-�� ��������� �������
	int GetNumPackets();
	int GetNumPacketSend();
	int GetNumPacketRecv();
	float GetTrafic();// Kbit per sec
	const char* GetServerIP();
	const char* GetClientIP();
	float GetPing(int i);//������ ����
	float GetServerWorkTime(int i);//����� ������� ����� ������ �� �������
	
	tNetStatistic(void);
	virtual ~tNetStatistic(void);
};
