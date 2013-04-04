#include "tNetStatistic.h"

tNetStatistic::tNetStatistic(void){
		dwNetTime=GetTickCount();
		fPacketCount=0;
		fByteSum=0;
		fBitPerSec=0;
		fPackets=0;
		send=0;
		recv=0;
		count=0;
		fRecvTime=0;
		count_avg=0;
		fRecvTimeAvg=0;
		ZeroMemory(&times[0],sizeof(times));//memset(&times[0],0,100);
		ZeroMemory(&avgTime[0],sizeof(avgTime));//memset(&avgTime[0],0,sizeof(float)*100*3);
}

tNetStatistic::~tNetStatistic(void){}

void tNetStatistic::AddByteSend(float cnt){
	AddByte(cnt);
	++send;
}
void tNetStatistic::AddByteRecv(float cnt){
	AddByte(cnt);
	++recv;
}
void tNetStatistic::AddByte(float cnt){
	fPacketCount++;
	fByteSum+=cnt;
}
int tNetStatistic::AddTimeSend(void){
	count++;
	if (count>99) {
		count=0;
		ZeroMemory(&times[0],sizeof(times));
	}
	times[count]=this->mTick.GetTime();
	return count;
}


int tNetStatistic::Send(float byteSend){
	int rc=0;
	this->AddByteSend(byteSend);//считаем посланные байты
	rc=this->AddTimeSend();//запоминаем время отправки
	return rc;//возвращаем номер запомненного пакета
}
void tNetStatistic::Recv(float byteRecv,int count, float time){
	this->AddByteRecv(byteRecv);
	this->AddTimeRecv(count,time);
}
void tNetStatistic::AddTimeRecv(int cnt,float dtServer){
	if (cnt>99) return;
	if (cnt<0) return;
	float tms=this->mTick.GetTime();
	if (times[cnt]){
		avgTime[count_avg][0]=tms-times[cnt]-dtServer;//чистый пинг
		avgTime[count_avg][1]=dtServer;//время на сервере
		if (fRecvTime!=0){
			avgTime[count_avg][2]=tms-fRecvTime;//дельта тайм приёма последнего пакета
		}
		fRecvTime=tms;

		count_avg++;
		//if (fmodf(count_avg,10)==0) this->CalcAvgTimePacketRecv();
		if (count_avg>99) count_avg=0;
		times[cnt]=0;
	}else{
		//Error!
		bool debug=true;
	}
}
void tNetStatistic::CalcAvgTime(){
	if (count_avg<10) return ;
	int cnt=0;
	fRecvTimeAvg=0;
	for (int i=0;i<99;i++){
		if (avgTime[i][2]!=0){
			if (avgTime[i][2]<2000){
				fRecvTimeAvg+=avgTime[i][2];
				cnt++;
			}
		}
	}
	fRecvTimeAvg/=cnt;
	return ;
}
float tNetStatistic::GetTrafic(){
	float tmp=0;
	DWORD cTime=::GetTickCount();
	DWORD dt=cTime-dwNetTime;
	if (dt>1000){
		fBitPerSec=fByteSum*9.0f/1024.0f;
		dwNetTime=cTime;
		fPackets=fPacketCount;
		fPacketCount=0;
		fByteSum=0;
	}
	if (dt>1100) return -1; //редко вызывается - погрешность!
	return fBitPerSec;
}
int tNetStatistic::GetNumPackets(){
	return fPackets;
}
int tNetStatistic::GetNumPacketSend(){
	return send;
}
int tNetStatistic::GetNumPacketRecv(){
	return recv;
}
const char* tNetStatistic::GetServerIP(){
	return this->serverIP.c_str();
}
const char* tNetStatistic::GetClientIP(){
	return this->clientIP.c_str();
}

float tNetStatistic::GetAvgTimeRecv(){//среднее время между приёмом пакетов
	return fRecvTimeAvg;
}
float tNetStatistic::GetAvgTimeSend(){//Среднее время между отправкой пакетов
	return 0;
}
float tNetStatistic::GetAvgTimePing(){//среднее время доставки пакета(ping)
	return 0;
}
float tNetStatistic::GetAvgTimeServerWork(){//среднее время задержки пакета сервером
	return 0;
}
float tNetStatistic::GetNumPacketsLost(){//кол-во потеряных пакетов
	return 0;
}
float tNetStatistic::GetPing(int i){//чистый пинг
	if ((i<0)||(i>99)) return -1;
	return avgTime[i][0];
}
float tNetStatistic::GetServerWorkTime(int i){//время которое пакет пробыл на сервере
	if ((i<0)||(i>99)) return -1;
	return avgTime[i][1];
}
