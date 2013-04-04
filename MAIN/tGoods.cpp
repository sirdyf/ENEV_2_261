// tGoods.cpp: implementation of the tGoods class.
//
//////////////////////////////////////////////////////////////////////
#include "tGoods.h"
#include <stdio.h>

tGoods::tGoods(){
	counts=0;
//	curPos=0;
	delta=0;
}
tGoods::~tGoods(){}

void tGoods::Load(){

	int s1=0;
	char s2[30]={0};
	float s3=0;
	float s4=0;
	char s5[10]={0};
	char mstr[512]={0};
	SDELog.WriteMessage("Загрузка: Data/goods.txt");
	FILE* mf=fopen("Data/goods.txt","r+");
	if (mf==NULL) {
		SDELog.WriteError("Не удалось найти файл!");
		return ;
	}else{
		SDELog.WriteMessage("файл открыт...");
	}
	fgets(mstr,512,mf);
	while(fscanf(mf,"%d %s %f %f %s	",&s1,s2,&s3,&s4,s5)){
		fgets(mstr,512,mf);
//		printf("%d %s %f %f %s %s",s1,s2,s3,s4,s5,mstr);//){
		units[counts].num=s1;
//		strcpy(units[counts].name,s2);
		units[counts].name=s2;// Ошибка! S2 - временная переменная!
		units[counts].cost=s3;
		units[counts].delta=s4;
		units[counts].meas=s5;// Ошибка! S5 - временная переменная!
		units[counts].desc=mstr;
//		units[counts].amount=100.0f*(float)(rand())/RAND_MAX+20.0f;
		counts++;
	}
	counts--;
	fclose(mf);
	SDELog.WriteMessage("...Файл закрыт.Загрузка завершена.");
}

int tGoods::GetCount(){
return counts;
}
