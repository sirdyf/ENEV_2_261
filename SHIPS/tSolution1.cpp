// tSolution1.cpp: implementation of the tSolution1 class.
//
//////////////////////////////////////////////////////////////////////

#include "tSolution1.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tSolution1::tSolution1(){
id=1;
}

tSolution1::~tSolution1(){}

void tSolution1::Processing(){
// +������������ ���� � ����
//	��������
// ����������� �����:
// 1) ��������� � �����(�����)
// 2) ������ ����� �� �����(����)
// 3) ������
// ��������� �����:
// 1)������ �� ����������
// 2)��������� �� ���������� (�����,������)
	std::list<boost::intrusive_ptr<tShipCommand> >::const_iterator iSC;
	std::list<boost::intrusive_ptr<tObj> >::const_iterator iEnemy;
	boost::intrusive_ptr<tInterpretorCommandInterface> cmd;

	iSC=_base->defendShipsGroup.begin();
	iEnemy=_base->enemyShips.begin();
	if (iEnemy==_base->enemyShips.end()) return;
	
	SDELog.WriteMessage("Group %d tSolution1::Processing()",(*iSC)->GetShipIdGroup());

	_base->SetAllTarget((*iEnemy));
        while(iSC!=_base->defendShipsGroup.end()){
//			if ((*iSC)->_ship->HaveTarget()==false){
//     				(*iSC)->_ship->New_Target((*iEnemy));
					cmd=boost::intrusive_ptr<tInterpretorCommandInterface> (new tICommand6);
	       			(*iSC)->_command=cmd;// attack
		       		iEnemy++;
		      		if (iEnemy==_base->enemyShips.end()) iEnemy=_base->enemyShips.begin();
//			}
			iSC++;
        }

}
void tSolution1::WarningExecute(boost::intrusive_ptr<tShipCommand> shipCommand){
// ���� �������� �����:
// �������� �������������� ��� ���������� ������� - "�����"(5���.) ���� "������� �����������"(3���.)
// �������:
// ������� �� ����� ���� ������ ��� ������� (� ��� ����� ������ ���� ���� ������� ���������)
	int a=0;//debug
	shipCommand->SetMine();
// ���� �� ������ ������.
// ���� �� ������ ���������� �����
}
void tSolution1::Execute(boost::intrusive_ptr<tShipCommand> shipCmd){

// ���� ��������,����� if ((*iSh)->Validate()==true){
// �.�.��� ������� ��� ��� ���������
	float tmp=0;
	if (!shipCmd->_command) {
		shipCmd->_command=boost::intrusive_ptr<tInterpretorCommandInterface> (new tICommand6);
		shipCmd->m_refCounter+=tSolution1::m_refCounter-1;//???check!!!!
		return;
	}
	int id=shipCmd->_command->GetID();
	if (id==6){
		if (shipCmd->IsComplete())	{//�������� "&&(_base->role)" ������� ��������� ������� ��� ��������� � ����������
			shipCmd->_command=boost::intrusive_ptr<tInterpretorCommandInterface> (new tICommand7);//���� �� ������������
			shipCmd->m_refCounter+=tSolution1::m_refCounter-1;
			shipCmd->ResetCommand();
//			shipCmd->_command->Init(shipCmd->_ship);
//			shipCmd->_ship->obj->inertX.Value=shipCmd->_ship->aY;	//��������� ���� ��������
		}else{}
	}else{
		if (shipCmd->IsComplete())	{
			shipCmd->_command=boost::intrusive_ptr<tInterpretorCommandInterface> (new tICommand6);//���������,�����
			shipCmd->m_refCounter+=tSolution1::m_refCounter-1;
			shipCmd->ResetCommand();
		}
	}

/* !!!!!
	std::list<boost::intrusive_ptr<tObj> >::iterator iEnemy;
	iEnemy=base->enemyShips.begin();
	if ((*shipCmd)->_ship->HaveTarget()==false){
	       	(*shipCmd)->_ship->NewTarget((*iEnemy));
	       	(*shipCmd)->_command=0;// ???
	}
*/
}

