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
// +распределить цели и роли
//	зациклен
// агрессивная атака:
// 1) сближение и атака(лазер)
// 2) маневр ухода от атаки(мины)
// 3) повтор
// пассивная атака:
// 1)отойти на расстояние
// 2)атаковать на расстоянии (лазер,ракеты)
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
// сюда попадаем когда:
// Получено предупреждения при выполнении команды - "хвост"(5сек.) либо "большие повреждения"(3сек.)
// Пробуем:
// уходить от атаки либо меняем вид маневра (в том числе ставим мину если условия позволяют)
	int a=0;//debug
	shipCommand->SetMine();
// мина не должна лететь.
// мина не должна уничтожать своих
}
void tSolution1::Execute(boost::intrusive_ptr<tShipCommand> shipCmd){

// сюда попадаем,когда if ((*iSh)->Validate()==true){
// т.е.нет команды или она выполнена
	float tmp=0;
	if (!shipCmd->_command) {
		shipCmd->_command=boost::intrusive_ptr<tInterpretorCommandInterface> (new tICommand6);
		shipCmd->m_refCounter+=tSolution1::m_refCounter-1;//???check!!!!
		return;
	}
	int id=shipCmd->_command->GetID();
	if (id==6){
		if (shipCmd->IsComplete())	{//Заменить "&&(_base->role)" Сделать отдельную команду для атакующих и защитников
			shipCmd->_command=boost::intrusive_ptr<tInterpretorCommandInterface> (new tICommand7);//Уход от столкновения
			shipCmd->m_refCounter+=tSolution1::m_refCounter-1;
			shipCmd->ResetCommand();
//			shipCmd->_command->Init(shipCmd->_ship);
//			shipCmd->_ship->obj->inertX.Value=shipCmd->_ship->aY;	//вычислить угол поворота
		}else{}
	}else{
		if (shipCmd->IsComplete())	{
			shipCmd->_command=boost::intrusive_ptr<tInterpretorCommandInterface> (new tICommand6);//сближение,атака
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

