#include "tOthers.h"

tOthers::tOthers(void){}

tOthers::~tOthers(void){
	objList.clear();
}

void tOthers::Processing(){
//	std::list< boost::intrusive_ptr<tObj> >::const_iterator i,ii,beg,end;
//	beg=objList.begin();
//	end=objList.end();
	AssemblyRubbish();
}
void tOthers::AssemblyRubbish(){
	std::list< boost::intrusive_ptr<tObj> >::iterator allShips=objList.begin();
	while (allShips!=objList.end()){
		if ((*allShips)->mustDestroy) {
			allShips=objList.erase(allShips);
		}else{
			allShips++;
		}
	}

}
bool tOthers::AddObj(int gr,int indEng,float r,D3DXVECTOR3 p){
	return false;
	boost::intrusive_ptr<tObj> tmpObj=0;

	 //кто хранит мину??
	tmpObj=pEng->CreateObj(gr,r,p,indEng);
	objList.push_back(tmpObj);
	return true;
}
bool tOthers::AddObj(boost::intrusive_ptr<tObj> tmpO){
//	if (objList.size()>1) return false;
	objList.push_back(tmpO);
	return true;
}