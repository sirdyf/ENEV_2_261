// client.cpp : Defines the entry point for the console application.
//
#include <conio.h>
#include <iostream>
#include "tNetworkClient.h"

using namespace std;

class tMain : public tINetworkClient{
	int FormatDataForSend(char*){return 0;}
	void ClientReciveData(const char* ,int){;}
};

int main(int argc, char* argv[]){
	boost::intrusive_ptr<tMain> tstMain(new tMain);
	tNetworkClient tstClient;
	cout << "\t\tStart program.\n\n";
	tstClient.Init(tstMain);
	cout << "Run network engine...\n";
	tstClient.Run();
	cout << "Wait 5 sec..\n";
	::Sleep(5000);
	std::cout << "\n\tResult:\n Packet Send:"
		<< tstClient._mNetStat.GetNumPacketSend()
		<< " Packed recv:" << tstClient._mNetStat.GetNumPacketRecv()
		<< " Total:" << tstClient._mNetStat.GetNumPackets()
		<< "\n\t\tTrafic:"	<< tstClient._mNetStat.GetTrafic()<< "Kbit in sec\n";
	cout << "Stop network engine.\n";
	tstClient.Stop();
	tstClient.Release();
	cout << "\n\n\t\tEnd program.\n";
	getch();
	return 0;
}

