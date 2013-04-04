#define WIN32_LEAN_AND_MEAN

#include "tStorage.h"

//struct sockaddr;
//#include <winsock2.h>

tStorage::~tStorage(void){}

tStorage::tStorage(void){
}

void tStorage::AddObj(boost::intrusive_ptr<tObj> obj){
	tSendData tmp;
	tmp.pos=obj->GetPos();
	tmp.dir=obj->tz;
	tmp.up=obj->ty;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	tmp.uin=obj->uin;
//	tmp.radius=obj->radius;
//	physObj.push_back(tmp);
}
void tStorage::ClearList(void){
	physObj.clear();
}
/*
	archive_stream.str("");
	boost::archive::text_oarchive os(archive_stream);
	os << BOOST_SERIALIZATION_NVP(tmpSI);
	//archive_stream.str("");
	//boost::archive::text_oarchive os(archive_stream);
	//os << BOOST_SERIALIZATION_NVP(tmpSI);
	//os << BOOST_SERIALIZATION_NVP(sendList);
*/