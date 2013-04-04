#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <math.h>
#include "../main/tTick.h"
#include "tINetStatistic.h"

class tNetStatistic:public tINetStatistic{
	DWORD dwNetTime;
	float fPacketCount;//общее кол-во пакетов
	float fByteSum;
	float fBitPerSec;
	float fPackets;// пакетов в сек
	int send;
	int recv;
	int count;//счётчик для массива времени (0..99),т.е. инфа храниться о 100 последних пакетах
	int count_avg;
	float fRecvTimeAvg;
	float fRecvTime;// время между принятыми пакетами

	float times[100];
	float avgTime[100][3];//[0]-чистый пинг [1]-время на сервере [2]-дельта тайм приёма пакетов

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

	float GetAvgTimeRecv();//среднее время между приёмом пакетов
	float GetAvgTimeSend();//Среднее время между отправкой пакетов
	float GetAvgTimePing();//среднее время доставки пакета(ping)
	float GetAvgTimeServerWork();//среднее время задержки пакета сервером
	float GetNumPacketsLost();//кол-во потеряных пакетов
	int GetNumPackets();
	int GetNumPacketSend();
	int GetNumPacketRecv();
	float GetTrafic();// Kbit per sec
	const char* GetServerIP();
	const char* GetClientIP();
	float GetPing(int i);//чистый пинг
	float GetServerWorkTime(int i);//время которое пакет пробыл на сервере
	
	tNetStatistic(void);
	virtual ~tNetStatistic(void);
};
