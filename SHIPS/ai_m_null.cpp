// ai_m_null.cpp: implementation of the ai_m_null class.
//
//////////////////////////////////////////////////////////////////////

#include "ai_m_null.h"
#include "tICommand1.h"
#include "tsolution1.h"
#include "tsolution2.h"
#include "tsolution3.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern float globalTT;

ai_m_null::ai_m_null(){}
ai_m_null::~ai_m_null(){}

void ai_m_null::Processing(){
// ������� ���������:
//1)������ ����.�������
//2)���������� �� ����������
	std::list<boost::intrusive_ptr<tShipCommand> >::const_iterator iSC;

if (_base->workStruct.enemy){

//	iSC=_base->attackShipsGroup.begin();
//	_base->attackShipsGroup.splice(iSC,_base->defendShipsGroup);
        
	if (solution) 
		if (solution->GetID()==1) return;
   	
	solution=boost::intrusive_ptr<tSolution1> (new tSolution1);
	solution->Init(_base);
	solution->Processing();// execute several command

        // +�������� ������� ������� � ����
	iSC=_base->defendShipsGroup.begin();
        while(iSC!=_base->defendShipsGroup.end()){
//        	(*iSC)->_ship->CleanTarget();
			if (_base->role==false){
				(*iSC)->_ship->obj->SetMaxSpeed(0.4f);//������������ ��� �������� - 40%
			}else{
//				(*iSC)->_ship->obj->SetMinSpeed(0.7f);//��������� ��� �������� - 70%
			}
        	(*iSC)->_command=0;
			iSC++;
        }
	return;
}

if (_base->workStruct.connectZone==false){
// ���� �������� �� �������
		if (solution)
			if (solution->GetID()==2) return;
       	solution=boost::intrusive_ptr<tSolution2> (new tSolution2);
		solution->Init(_base);
		solution->Processing();// execute several command
// if planet not have station ?? or dist > solsystem ??

}else{//connectZone=true!

//���� ������ ��������
		if (solution)
			if (solution->GetID()==3) return;
       	solution=boost::intrusive_ptr<tSolution> (new tSolution3);
		solution->Init(_base);
		solution->Processing();// execute several command

}

}
