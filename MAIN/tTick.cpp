#pragma once

#define WIN32_LEAN_AND_MEAN

#include "tTick.h"

float tTick::GetDeltaTime(int i=0){
	if (i==0) return dt;
	if (i<0) return 0;
	if (i>99) return 0;
	return mas[i][0];
}

tTick::tTick(void){
	bWork=false;
	res_time=0;
	dt_test=0; // temp variable
	dt_const=1000;
	dt=0;
	QueryPerformanceFrequency(&freq);
	cnt=0;
}

tTick::~tTick(void){}

float tTick::GetTime(){
	QueryPerformanceCounter(&ct3);
	double tmp=(double)( *(__int64*)&ct3  )/ (double)(*(__int64*)&freq);
	return (float)tmp*1000.0f;
}
void tTick::Wait(){
	QueryPerformanceCounter(&ct2);
	res_time=(double)( *(__int64*)&ct2 - *(__int64*)&ct1 )/ (double)(*(__int64*)&freq);
	dt_test=1000.0f*(float)res_time;//переводим из мк—ек. в м—ек.
	mas[cnt][0]=dt_test;
	msec=0;
	if (bWork){
		if (dt_test<dt_const){//если есть запас времени
			msec=(float)dt_const-dt_test;
			Sleep(msec);//спим
			mas[cnt][1]=msec;
			QueryPerformanceCounter(&ct2);
			res_time=(double)( *(__int64*)&ct2 - *(__int64*)&ct1 )/ (double)(*(__int64*)&freq);
		}
	}
	ct1=ct2;
	++cnt;
	if (cnt>99) cnt=0;
	dt_test=1000.0f*(float)res_time;//переводим из мк—ек. в м—ек.
	dt=(float)dt_test;
}
void tTick::Init(DWORD millisec){
	bWork=true;
	dt_const=millisec;
	Sleep(10);// дл€ проверки
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&ct1);
}

void tTick::Stop(){
	bWork=false;
}