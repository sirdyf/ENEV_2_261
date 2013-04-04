// AI_Motive.cpp: implementation of the AI_Motive class.
//
//////////////////////////////////////////////////////////////////////

#include "AI_Group.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


AI_Group::~AI_Group(){}

void AI_Group::Create(int nGr,bool role, boost::intrusive_ptr<tStarInterface> sI){
	base=boost::intrusive_ptr<ai_base> (new ai_base);
	base->starInterface=sI;
	base->role=role;
	numGroup=nGr;
}
void AI_Group::SetMotivationNull(){
	if (!base) return ;
	ai_m=boost::intrusive_ptr<ai_motivation> (new ai_m_null);
	ai_m->Init(base);
	ai_s=boost::intrusive_ptr<ai_motivation> (new ai_s_null);
	ai_s->Init(base);
}
void AI_Group::SetMotivationEmpty(){
	if (!base) return ;
	ai_m=boost::intrusive_ptr<ai_motivation> (new ai_m_empty);
	ai_m->Init(base);
	ai_s=0;
}
bool AI_Group::SetMotivationDefendObj(boost::intrusive_ptr<tObj> dObj){
	if (!dObj) return false;
	if (!base) return false;
	ai_m=boost::intrusive_ptr<ai_motivation> (new ai_m_defObj);
	ai_m->Init(base);
	ai_m->SetObj(dObj);
	return true;
}

bool AI_Group::AddShip(boost::intrusive_ptr<tShip> tmpShip){//, bool tipe){

	std::list< boost::intrusive_ptr<tShipCommand> >::iterator iGr;
	if (base->role==false){
		tmpShip->obj->SetMaxSpeed(0.4f);
	}
	int a=base->defendShipsGroup.size();
	if (a>=1){//первый корабль в группе - ведущий
//		создаем точку построения
		iGr=base->defendShipsGroup.begin();
		boost::intrusive_ptr<tObj> _obj;
		_obj=pEng->CreatePointObj(20,(*iGr)->_ship->obj,D3DXVECTOR3(0,0,-a*100),numGroup);
		base->vObjList.push_back(_obj);//запоминаем виртуальную точку в построении
	}
	boost::intrusive_ptr<tShipCommand> tmpSC(new tShipCommand);
	tmpSC->Assign(tmpShip);
	tmpShip->obj->SetIdGroup(numGroup);
	base->defendShipsGroup.push_back(tmpSC);
	return true;
}
int AI_Group::GetUin(){
	return numGroup;
}
void AI_Group::DecisionMaking(){
// не использовать эту конструкцию: 	
//	if (!base->HaveAttackShips()){
// противоречит подходу !!!
// решение об атаке должен принимать наследник ai_motivation

		//SDELog.WriteMessage("AI_Group::DM() for %d",AI_Group::numGroup);
//	обработать направляющего !!!
		if (ai_s) ai_s->Processing(); // обстановочная афферентация
		if (ai_m) ai_m->Processing(); // доминирующая мотивация
//		ai_p->Processing(); // пусковая афферентация (поиск решения мотивации)
//		ai_t->Processing(); // принятие решения
//		if (ai_m->solution) ai_m->solution->Processing();// execute several command перенес в ai_m, чтобы не вызывать часто
// проконтролировать! при атаке не надо вызывать, а при полете к станции и входе в ЗДС надо, чтобы сменить цель с планеты на станцию!	
		needDM=false;
}
bool AI_Group::AddEnemy(boost::intrusive_ptr<tObj> enemy){
	std::list< boost::intrusive_ptr<tShipCommand> >::iterator iSh;
	std::list< boost::intrusive_ptr<tObj> >::const_iterator iObj;
	if (enemy->mustDestroy) return false;
// проверка на попадание в "своих"
	if (enemy->GetIdGroup()==AI_Group::numGroup) return false;
// проверка наличия противника в списке
	iObj=base->enemyShips.begin();
	while (iObj!=base->enemyShips.end()){
		if ((*iObj)==enemy) break;
		iObj++;
	}
	if (iObj!=base->enemyShips.end()) return false;

	base->enemyShips.push_back(enemy);
	return true;
}
bool AI_Group::CheckHitObj(boost::intrusive_ptr<tObj> enemy){//для объектов
	bool fl=false,dead=false;
	float dam=0;
	std::list< boost::intrusive_ptr<tShipCommand> >::const_iterator iSh;
	std::list< boost::intrusive_ptr<tShipCommand> >::const_iterator end;
	iSh=base->defendShipsGroup.begin();
	end=base->defendShipsGroup.end();
	while(iSh!=end){
		if ((*iSh)->CheckFire()){
			(*iSh)->CheckHit(enemy);
			if (fl){
				dam=(*iSh)->_ship->GetWeaponDamage()*pEng->GetDeltaTime();
				dead=enemy->Hit(dam);
			}
		}
		iSh++;
	}
	return fl;
}
bool AI_Group::CheckHit(boost::intrusive_ptr<tEquipment> enemy){//для камеры и кораблей
	bool fl=false,dead=false;
	float dam=0;
	std::list< boost::intrusive_ptr<tShipCommand> >::const_iterator iSh;
	std::list< boost::intrusive_ptr<tShipCommand> >::const_iterator end;
	iSh=base->defendShipsGroup.begin();
	end=base->defendShipsGroup.end();
	while(iSh!=end){
		if ((*iSh)->CheckFire()){
			fl=(*iSh)->CheckHit(enemy->obj);
			if (fl){
				dam=(*iSh)->_ship->GetWeaponDamage()*pEng->GetDeltaTime();
				dead=enemy->Hits(dam);
			}
		}
		iSh++;
	}
	return fl;
}
bool AI_Group::CheckAccessoryShip(boost::intrusive_ptr<tShip> _sh,
								  boost::intrusive_ptr<tObj> enemy){
	bool fl=false;
	if (_sh->obj->GetIdGroup()==numGroup){
		fl=AddEnemy(enemy);
		fl=true;//если эта группа, то всегда возвращать признак принадлежности  к группе "истина"
	}
	return fl;
}
void AI_Group::Processing(){
/*AI_T::SolveWarning(){
	//пусковая афферентация
	if (base->enemyShips.size()==0){
		//режим полета
		//если мы здесь возможно столкновение с метеоритом?
	}else{
		//режим боя
		//получаем большие повреждения - уходим из под обстрела(проверить текущий маневр)
		//долго не можем снять "хвост" - ставим мину
	}
}*/
//	признак атаки !? классификацию противников делает ai_situation
	bool fl=false;
	std::list < boost::intrusive_ptr<tShipCommand> >::iterator iSh;
	iSh=base->defendShipsGroup.begin();
	while (iSh!=base->defendShipsGroup.end()){
//		fl=ai_s->CheckWarnings((*iSh));//Проверка состояния корабля (нет ли "хвоста" или "сильных повреждений")
//		if (fl) ai_t->SolveWarning((*iSh));//ищем путь решения проблемы
		(*iSh)->ProcessCommand();
		if ((*iSh)->Validate()==true) {//fl=true;
			if (ai_m->solution) {
				ai_m->solution->Execute((*iSh));// execute several command
			// проверка: если закончились команды - закончилась задача
				if ((*iSh)->Validate()==true) {
					//SDELog.WriteMessage("Group %d Processing.End command in Solution.Need DM()",AI_Group::numGroup);
					AI_Group::needDM=true;
				}else{}
			}else{
				//SDELog.WriteWarning("Group %d Processing.Solution==0.Need DM()",AI_Group::numGroup);
				AI_Group::needDM=true;
			}
		}
		iSh++;
	}

}
bool AI_Group::AssemblyRubbish(){
	bool needDM=false;
	bool changeMaster=false;
	boost::intrusive_ptr<tShipCommand> tmp;
	std::list< boost::intrusive_ptr<tShipCommand> >::iterator allShips;

	int def=base->defendShipsGroup.size();

	if (def){
		allShips=base->defendShipsGroup.begin();
		if ((*allShips)->_ship->obj->mustDestroy) { // смена ведущего
			tmp=(*allShips);
			changeMaster=true;
		}
		while (allShips!=base->defendShipsGroup.end()){
			if ((*allShips)->_ship->obj->mustDestroy) {
				allShips=base->defendShipsGroup.erase(allShips);
			}else{
				allShips++;
			}
		}
	}
	// проверить ликвидность атакующих
	std::list< boost::intrusive_ptr<tObj> >::iterator enemy=base->enemyShips.begin();
	while (enemy!=base->enemyShips.end()){
		if ((*enemy)->mustDestroy) {
			enemy=base->enemyShips.erase(enemy);
//???			SDELog->WriteMessage("Group %d needDM set true(hits from enemy)",(*iGr)->GetUin());
//???			needDM=true;
		}else{
			enemy++;
		}
	}
	def=base->defendShipsGroup.size();

	if (def==0){//уничтожение группы:
		return true;
	}
	boost::intrusive_ptr<tObj> p1;
	boost::intrusive_ptr<tObj> p2;
	if (changeMaster){
		allShips=base->defendShipsGroup.begin();
		if (allShips!=base->defendShipsGroup.end()){
			p1=tmp->_ship->obj;
			p2=(*allShips)->_ship->obj;
			pEng->ChangePointsMaster(p1,p2);
			tmp->_ship=0;
			tmp->_command=0;
		}
	}
	return false;
}
/*
void AI_Group::ProcessDefends(){
	bool fl=false;
	std::list < boost::intrusive_ptr<tShipCommand> >::iterator iSh;
	iSh=base->defendShipsGroup.begin();
	while (iSh!=base->defendShipsGroup.end()){
		(*iSh)->ProcessCommand();
		if ((*iSh)->Validate()==true) {//fl=true;
			if (ai_m->solution) {
				ai_m->solution->Execute((*iSh));// execute several command
			// добавить проверку, если закончились команды - закончилась задача
				if ((*iSh)->Validate()==true) {
					fl=true;
				}else{}
			}else{
				fl=true;
			}
		}
		iSh++;
	}
	if (fl){
		SDELog.WriteMessage("Group %d ProcessDefends,Call DM()",AI_Group::numGroup);
		DecisionMaking(); //
	}
}

bool AI_Group::ProcessAttack(){
	bool fl=false;
	std::list < boost::intrusive_ptr<tShipCommand> >::iterator iSh;
	iSh=base->defendShipsGroup.begin();
	while (iSh!=base->defendShipsGroup.end()){//перебор кораблей одной группы
//		if ((*iSh)->CheckWarnings()){//проверям эффективность ухода от атаки: нет ли "хвоста" или "сильных повреждений"
//			if (ai_m->solution) ai_m->solution->WarningExecute((*iSh));// execute several command
//		}
		(*iSh)->ProcessCommand();
		if ((*iSh)->Validate()==true) {//fl=true;
			if (ai_m->solution) ai_m->solution->Execute((*iSh));// execute several command
		}
		iSh++;
	}
return false;
}
*/
