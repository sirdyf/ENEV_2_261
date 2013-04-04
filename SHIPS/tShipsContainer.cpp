// tShipsContainer.cpp: implementation of the tShipsContainer class.
//
//////////////////////////////////////////////////////////////////////

#include "tShipsContainer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tShipsContainer::tShipsContainer()
{

}

tShipsContainer::~tShipsContainer(){
	mShips.clear();
}

int tShipsContainer::GetNumShips(){

	return mShips.size();
}
/*
boost::intrusive_ptr<tObj> tShipsContainer::GetShipObj(int num){

	boost::intrusive_ptr<tObj> tmpObj;
	std::list< boost::intrusive_ptr<tShip> >::iterator iter=mShips.begin();
	if (num<=mShips.size()){
		for(;num>0;num--) iter++;
		tmpObj=(*iter)->obj;
	}
	return tmpObj;
}
*/
boost::intrusive_ptr<tObj> tShipsContainer::GetNextShip(int curShip){
	std::list< boost::intrusive_ptr<tShip> >::const_iterator _sh=mShips.begin();
	if (0==curShip) return (*_sh)->obj;
	int sz=mShips.size();
	if (curShip>=sz){_sh=mShips.end();return (*_sh)->obj;}
	for (int i=0;i<curShip;++i,++_sh){}
	return (*_sh)->obj;
}
boost::intrusive_ptr<tObj> tShipsContainer::GetNextShip(boost::intrusive_ptr<tObj> curShip){
	boost::intrusive_ptr<tObj> tmp;
	if (mShips.size()==0) return 0;
	std::list< boost::intrusive_ptr<tShip> >::const_iterator _sh=mShips.begin();
	if (!curShip) return (*_sh)->obj;
	std::list< boost::intrusive_ptr<tShip> >::const_iterator end=mShips.end();
	do {
		if ((*_sh)->obj==curShip) break;
	}while(++_sh!=end);

	if (_sh!=end){
		if (++_sh!=end){
			tmp=(*_sh)->obj;
			return tmp;
		}
	}
	_sh=mShips.begin();
	tmp=(*_sh)->obj;
	return tmp;
	
//	if (++_sh==end){
//		_sh=mShips.begin();
//		tmp=(*_sh)->obj;
//		return tmp;
//	}
}
boost::intrusive_ptr<tShip> tShipsContainer::GetNextShip(boost::intrusive_ptr<tShip> curShip){
	boost::intrusive_ptr<tShip> tmp;
	std::list< boost::intrusive_ptr<tShip> >::iterator _sh=mShips.begin();
	if (mShips.size()==0) return 0;
	if (!curShip) return (*_sh);

	while (_sh!=mShips.end()){
		if ((*_sh)==curShip) {
			break;
		}
		_sh++;
	}
	if (_sh==mShips.end()){
		_sh=mShips.begin();
		tmp=(*_sh);
		return tmp;
	}
	_sh++;
	if (_sh==mShips.end()){
		_sh=mShips.begin();
		tmp=(*_sh);
		return tmp;
	}
	tmp=(*_sh);
	return tmp;
}
bool tShipsContainer::AllowRegister(boost::intrusive_ptr<tObj> ship){
	std::list< boost::intrusive_ptr<tShip> >::iterator iShip;
	iShip=mShips.begin();
	while(iShip!=mShips.end()){
		if ((*iShip)->obj==ship) break;
		++iShip;
	}
	if (iShip!=mShips.end()){
		(*iShip)->connectContract=true;
		return true;
	}
	return false;
}

//void tShipsContainer::SolSystem(){// !!!!!!!!!!!!!}
