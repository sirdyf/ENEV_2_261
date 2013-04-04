#pragma once

#include <windows.h>
#include <string>

class tTick{
	int cnt;
	float dt;
	bool bWork;
	LARGE_INTEGER ct1,ct2,ct3,freq;
	double res_time;// dt mkSec
	float dt_test;//temp variable
	DWORD dt_const;// time wait
	int msec;//temp variable
	float mas[100][2];
public:
	float GetTime();//врем€ в милисек
	void Init(DWORD millisec);
	// ∆дать или засечь врем€ между вызовами
	void Wait();
	// отключить ожидание по времени
	void Stop();
	tTick(void);
	virtual ~tTick(void);
	float GetDeltaTime(int i);
};


/*
__int64 fp_millis() 
{
  static __int64 freq;
  static BOOL fake = (QueryPerformanceFrequency((LARGE_INTEGER*)&freq),!(freq/=1000));
  __int64 val;
  QueryPerformanceCounter((LARGE_INTEGER*)&val);
  return val/freq;
}*/