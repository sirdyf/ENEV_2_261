// inert.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "..\\..\\inertion.h"
int _tmain(int argc, _TCHAR* argv[]){

	printf("Start test inertion\n");
	float check=0;
	inertion a;
	a.SetAcceleration(1,7);
	a.Value=9;
	printf("Sart Value=%.3f \n",a.Value);
	for (int i=0;i<60;i++){
		a.InertPrediction();
		if (i==2)	a.SetValuePrediction(5);
		printf("%.2d curValue=%.1f Value=%.1f \n",i,a.GetCurValue(0),a.Value);//deltaTime));
		if (a.GetCurValue(0)==0){
			if (a.Value==0){
				break;
			}
		}
	}
	printf("steepness=%.5f",a.GetSteepness());

//printf(s.c_str());
//char txt[50]={0};
//sprintf(txt,"%d",i);
//std::stringstream s;
//int i=25;
//s << i;
//printf(s.str().c_str());
	
	getch();
	return 0;
}

