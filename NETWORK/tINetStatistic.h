#pragma once

#include "../phisics/tpointer.h"

class tINetStatistic:public tPointer{
public:
	virtual float GetAvgTimeRecv()=0;//среднее врем€ между приЄмом пакетов
	virtual float GetAvgTimeSend()=0;//—реднее врем€ между отправкой пакетов
	virtual float GetAvgTimePing()=0;//среднее врем€ доставки пакета(ping)
	virtual float GetAvgTimeServerWork()=0;//среднее врем€ задержки пакета сервером
	virtual float GetNumPacketsLost()=0;//кол-во потер€ных пакетов
	virtual int GetNumPackets()=0;
	virtual int GetNumPacketSend()=0;
	virtual int GetNumPacketRecv()=0;
	virtual float GetTrafic()=0;//Kbit per sec. "-1"=редко вызываетс€ - погрешность!
	virtual const char* GetServerIP()=0;
	virtual const char* GetClientIP()=0;
	virtual float GetPing(int i)=0;
	virtual float GetServerWorkTime(int i)=0;//врем€ которое пакет пробыл на сервере
	
	tINetStatistic(void){;}
	virtual ~tINetStatistic(void){;}
};
