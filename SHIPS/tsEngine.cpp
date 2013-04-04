// tsEngine.cpp: implementation of the tsEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "tsEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tsEngine::tsEngine(){
	DistOfHyperJamp=0;
	HaveHyperJamp=false;
	Massa=0;
	name[0]=0;

//	indEng=0;
}

tsEngine::~tsEngine(){
}

void tsEngine::operator =(const tsEngine tse){
	DistOfHyperJamp=tse.DistOfHyperJamp;
	HaveHyperJamp=tse.HaveHyperJamp;
	Massa=tse.Massa;
	strcpy(name,tse.name);
//	indEng=tse.indEng;
}

bool tsEngine::SetValue(std::string buf)
{
	int tst=0,cmd=0;
	std::string buf2;
				tst=buf.find(" ");
				if (tst<1) return false;
// чувствителен к регистру!!!
				
				if (buf.find("Name")==0) cmd=1;
				if (buf.find("HaveHyperJamp")==0) cmd=2;
				if (buf.find("DistOfHyperJamp")==0) cmd=3;
				if (buf.find("Vmax")==0) cmd=4;
				if (buf.find("Massa")==0) cmd=5;
//				if (buf.find("InertionSTEP")==0) cmd=6;
//				if (buf.find("InertSpeedSTEP")==0) cmd=7;
//				if (buf.find("InertSpeedMAX")==0) cmd=8;
				if (cmd==0) return false;//Unknown Value
				buf2=buf.substr(tst+1,buf.length());
				switch(cmd){
				case 1:
					strcpy(name,buf2.c_str());
					break;
				case 2:
					if (buf2.compare("Yes")==0) HaveHyperJamp=true;
					else HaveHyperJamp=false;
					break;
				case 3:
					DistOfHyperJamp=atof(buf2.c_str());
					break;
				case 4:
					break;
				case 5:
					Massa=atof(buf2.c_str());
					break;
/*
				case 6:
					if (buf.compare("default")==0)
						Inertion=0;
					else
						Inertion=atof(buf.c_str());
					break;
				case 7:
					if (buf.compare("default")==0)
						InertSpeedSTEP=0;
					else
						InertSpeedSTEP=atof(buf.c_str());
					break;
				case 8:
					if (buf.compare("default")==0)
						InertSpeedMAX=0;
					else
						InertSpeedMAX=atof(buf.c_str());
					break;
*/
				default:
					return false;
					break;
				}
return true;
}
