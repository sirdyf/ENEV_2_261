// time-wait.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
//#include <windows.h>
#include "..\\..\\..\\main\ttick.h"

void _tmain(void){
	tTick tst;
	float t=50;
	tst.Init(t);
	for (int i=0;i<50;i++){
		//Sleep(5);
		tst.Wait();
		Sleep(40);
	}
	printf ("time work %.1f mSec. avg=%.5f sleep=%.5f",t,tst.dt_avg,tst.dt_avg_sleep);
	getch();

	return;
}

