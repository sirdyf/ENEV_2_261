#pragma once

class tNetInfo{
public:
	int typeOfService;//128-work 126-echo 127-loopback
	float dwServerWork;
	float dwServerTime;
	int clientNumPacket;
	float fUin;
	tNetInfo(){
		fUin=0;
		typeOfService=0;
		dwServerWork=0;
		clientNumPacket=0;
		dwServerTime=0;
	}
	virtual ~tNetInfo(){}
};
