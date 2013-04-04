#include "tComponents.h"


tComponents::tComponents(void) {counts=0;}

tComponents::~tComponents(void){}

void tComponents::Load(void){
//	return ;
	char szString[128];
	int s1=0;
	char s2[20]={0};
	char s3[50]={0};
	float s4=0;
	int s5=0,s6=0,s7=0;
	char mstr[512]={0};
//	FILE* mf=fopen("..\\ships\\data\\eq.txt","r+");
	SDELog.WriteMessage("Загрузка компонентов корабля из файла: data/eq.txt начата...");
	FILE* mf=fopen("Data/eq.txt","r+");
	if (mf==NULL) {
		SDELog.WriteError("не удалось открыть файл!");
		return ;}
	fgets(mstr,512,mf);
//	while(fscanf(mf,"%d %s %s %f %d %d %d",&s1,&s2[0],&s3[0],&s4,&s5,&s6,&s7)){
	while(fscanf(mf,"%d %s %s %f %d %d",&s1,&s2[0],&s3[0],&s4,&s5,&s7)){
//	for(int i=0;i<14;++i){
//		fscanf(mf,"%d %s %s %f %d %d %d",&s1,&s2[0],&s3[0],&s4,&s5,&s6,&s7);
		units[counts].uin=s1;
		memcpy(units[counts].name,s2,20);//
		memcpy(units[counts].dest,s3,50);//временная переменная
		units[counts].cost=s4;//временная переменная
		units[counts].tlevel=s5;
//		units[counts].max=s6;
		units[counts].types=s7;
		counts++;
	}
	counts--;
	fclose(mf);
	SDELog.WriteMessage("...закончена. Загружено %d элементов",counts);
}
int tComponents::GetCount(){
	return counts;
}