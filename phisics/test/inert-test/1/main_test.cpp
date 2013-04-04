#include <stdio.h>
#include <conio.h>
#include "..\\..\\inertion.h"
void main(void){
	printf("Start test inertion\n");
	float check=0,dt=1.0f/50.0f;
	inertion a;
	a.SetSteepness(50,2);
	a.SetValue(100);
	for (int i=0;++i;i<50){
		a.InertPrediction(dt);
		check+=a.GetCurValue(dt);
	}
	printf("delta time=%.1f Value=%.1f",dt,check);
	getch();
}