#include "ai_m_empty.h"
#include "tSolution5.h"

ai_m_empty::ai_m_empty(void)
{
}

ai_m_empty::~ai_m_empty(void)
{
}
void ai_m_empty::Processing(){
	if (solution)
		if (solution->GetID()==5) return;

	solution=boost::intrusive_ptr<tSolution5> (new tSolution5);
	solution->Init(_base);
	solution->Processing();// execute several command

}