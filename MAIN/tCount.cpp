#include "tCount.h"
#include "..\main\log.h"

extern ESL::CLogFile TMPlog;//("dump.htm","Dump Log");

int tCount::AddValue(float val){
	_tick.Wait();
	mas[_mcount]=val;
	++_mcount;
	if (_mcount>99) {
		if (_auto) WriteDump(_title);
		_mcount=0;
		return -1;
	}
	return _mcount;
}
tCount::~tCount(){
	if (_auto) WriteDump(_title);
}
tCount::tCount(){
		_title="";
		_auto=0;
		_mcount=0;
		_tick.Stop();
		_bWrite=false;
		ZeroMemory(&mas[0],sizeof(mas));
}

void tCount::Init(std::string mTitle){
		_mcount=0;
		_tick.Stop();
		_bWrite=false;
		ZeroMemory(&mas[0],sizeof(mas));
	_auto=mTitle.size();
	_title=mTitle;
}

void tCount::WriteDump(std::string title){
	if (_bWrite) return;
	TMPlog.WriteMessageLevelUp(title.c_str());
	for (int i=0;i<_mcount;i++){
		TMPlog.WriteMessage("n=%2d value=%.5f dt=%.5f",i,mas[i],_tick.GetDeltaTime(i));
	}
	_bWrite=true;
}
