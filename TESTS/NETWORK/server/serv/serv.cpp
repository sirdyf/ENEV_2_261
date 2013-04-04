// serv.cpp : Defines the entry point for the console application.
//

#define WIN32_LEAN_AND_MEAN
#define BOOST_LIB_DIAGNOSTIC 

#include "boost\smart_ptr.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <conio.h>

#include "..\..\..\..\network\tINetworkServer.h"
#include "..\..\..\..\network\tNetworkServer.h"

class tMain : public tINetworkServer{
public:
	void Init(){;}

	bool ClientIsUsed(int i){ return false;	}
	void NewClient(int i){;}
	void ClientRecvData(int i,char* buff,int sz){;}
	int GetData(int i,char* b){return 0;}
	void PrepareData(){;}

};

int main(int argc, char* argv[]){

	::setlocale( LC_ALL,"Russian" );

	boost::intrusive_ptr<tMain> tstMain (new tMain);
	tNetworkServer serv;
	std::cout << "\t\tDYF Network engine.\tAfaneor(c)2011.v1.0.\nStart test program.\n";
	serv.Init(tstMain);
	serv.SetSendTimeInterval(500);
	serv.Run();
	std::cout << "50 sec demo.\n";
	Sleep(50000);
	serv.Stop();
	serv.Destroy();
	std::cout << "\nEND Program.\n";
	//std::cout << 55 << std::setfill('0') << std::setw (10) << 123;
	//std::cout << 77 << std::endl;

	_getch();
	return 0;
}

