// inertion.cpp: implementation of the inertion class.
//
//////////////////////////////////////////////////////////////////////

#include "inertion.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

inertion::inertion(){
	curValue=steepness=Value=maximum=0.0f;
	maxPercent=1.0f;
	minPercent=0.3f;
	//accelStepPerSecond=1500.0f;
	curValueSign=0;
	maxStep=4.0f;
}
inertion::~inertion(){}
void inertion::operator =(const inertion tse){
	curValue=tse.curValue;
	steepness=tse.steepness;
	maximum=tse.maximum;
	Value=tse.Value;
}
void inertion::SetValuePrediction(int step){
//	float sgn=2.0f;
//	if (curValue<0) sgn=-2.0f;
//	if ((step>0)&&(curValue<0)) return;
//	if ((step<0)&&(curValue>0)) return;
	this->Value=-CalcFullPath(fabsf(step));//curValue+steepness*step*sgn;
}

float inertion::CalcCurrentPath(){
	if (steepness<=0) return 0;
// S=at*t+at
// a=steepness
// t=curValue/steepness
// at=curValue
// at*t = curValue*curValue/steepness
	float sgn=1.0f;
	if (curValue<0) sgn=-1.0f;
	float s=curValue*curValue/steepness+fabsf(curValue);
	return s*sgn;
}
float inertion::CalcFullPath(int stp=0){
	if (steepness<=0) return 0;
	if (stp<0) return 0;
	float sgn=1.0f;
	if (curValue<0) sgn=-1.0f;
	float stpns=fabsf(curValue/steepness)+stp;
	float s=steepness*stpns*stpns+steepness*stpns;
	return s*sgn;
}



void inertion::InertPrediction(){//	���������� ������ Value ���� ���, ��� �����-�� ����� ��������
	// accelStepPerSecond - ���-�� steepness � ��� 100-1000
	if (steepness==0) return;
	if (fabsf(Value)<=steepness) {
		if (fabsf(curValue)<=steepness){
			Value=0;curValue=0;
			return;
		}
	}

	//float tps=0,stpns=0,tp=0,vp=0,vv=0;
	//float curValueSign=1.0f;
	//if (curValue<0) curValueSign=-1.0f;
	//stpns=steepness;//*accelStepPerSecond
	//if (stpns!=0) tps=curValue/stpns;
	//tp=fabsf(tps);
	//vp=stpns*tp*(tp+1.0f)/2.0f*curValueSign;
	float vp1=CalcFullPath()/2.0f; //�.�.����������� ����,������� ������� �� ��������� - ����� �������� ������� ����
	float vp2=CalcFullPath(1)/2.0f; //�.�.����������� ����,������� ������� �� ��������� - ����� �������� ������� ����
	float vv1=vp1+Value;
	float vv2=vp2+Value;

//	CheckAndSetValue(vv,fDeltaTime);// ��������+=���������
	float sign=1.0f;
	if (vv1>0) {
		sign=-1.0f;
		if (vv2<0) sign=0.0f;
	}
	//if (vv==0) sign=0.0f;
	curValue+=steepness*sign;//*accelStepPerSecond

	Value+=curValue;// �������� �����: �������� ����-�+=���.����-�
}
//void inertion::CheckAndSetValue(float w,float fDeltaTime){
//	float sign=1.0f;
//	if (w>0) sign=-1.0f;
//	float stp=fabsf(curValue/steepness);
//// maxStep - �.�. �� 1 �� 10 accelStepPerSecond
////	if (stp>maxStep*maxPercent*accelStepPerSecond){//����������� �������� �� ���.����.
////		if (sign==curValue) return;
////	}
//	curValue+=steepness*sign;//*accelStepPerSecond
//}
void inertion::SetValue(float v){//������ ���������� �������� ��� �������� ��� ����������!
//	if (fabsf(curValue*fDeltaTime)>maximum*maxPercent) {
//		return;//curValue=maximum*maxPercent;
//	}
//	curValue+=(100.0f*fDeltaTime*steepness)*((dir==true)?1:-1);//;
	if ((!curValue)&&(!steepness)) curValue=v;//������� - ������ �� ������ ������
}

void inertion::SetSpeedValue(bool dir){
	curValue+=steepness*((dir==true)?1:-1);
	if (curValue>maximum*maxPercent) curValue=maximum*maxPercent;
	if (curValue<maximum*minPercent) curValue=maximum*minPercent;// ������!!! ���� minPercent ������ ������(� 0,1 �� 0,5) ���������� ������!
}
void inertion::InertPredictionSpeed(float tarDist,float fDeltaTime){

	float k=fabsf(Value-curValue)/steepness;//�� � ����� ������� �� �����
//	if (k<0){
//		SetSpeedValue(false);
//	}else{
//		float dist=-1.0f*k*steepness;//���� ���������,�� ������� ����� ����
		if (fabsf(curValue*k-tarDist)>50.0f){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			SetSpeedValue(true);
		}else{
			SetSpeedValue(false);
		}
//	}
}
 float inertion::GetCurValue(float fDeltaTime){
	return curValue;
}
 void inertion::SetAcceleration(float stpns,int maxStep){
	maximum=stpns*maxStep;
	steepness=stpns;
	curValue=0;
}
 float inertion::GetSteepness(){
	return steepness;
}
bool inertion::Check(){
	if (curValue<steepness) return true;
	else return false;
}

/*
float inertion::GetValue(bool dir){
	curValue+=steepness*((dir==true)?1:-1);
	if (curValue>maximum) curValue=maximum;
	if (curValue<-maximum) curValue=-maximum;
	Value+=curValue;
	return curValue;
}
*/

//	if ((fabs(curValue)==0.0f)&&(fabs(Value)<stpns*2.0f)) fl=0.0f;
//	if (curValue==stpns) curValue=0.0f;
//	if (curValue==0.0f) 
//	if (fabs(curValue)<0.01f)

//	if (fabs(Value)>0.01f) curValue+=stpns*fl;


float inertion::GetMaximum(){
	return maximum;
}

bool inertion::SetMaxValueInPercent(float percent){
	if (percent>1.0f) percent=1.0f;
	if (percent<minPercent+0.1f) percent=minPercent+0.1f;
	maxPercent=percent;
	return true;
}

bool inertion::SetMinValueInPercent(float percent){
	if (percent>maxPercent-0.1f) percent=maxPercent-0.1f;
	minPercent=percent;
	return true;
}
//��������� ��������� �������� � ��������� ������
//������ ��������� ��������� ���������� �������� � ������������ ������, ��������, �������� ���� ��� ��������� ���������� ��������.
//���� ���� ������������ ����� ��������� � ������ ( �������� ��� �������� ���������� � ����������� �� �� �������� ), 
//�� ��������� �������� ������� ��������� ��������������� ����� ���� ������������� �����. ��� ��������� �������, ������� ��� ������:
//#define DWORD unsigned long
//#define NEG_FLOAT(x) (*((DWORD *)&(x))) ^= 0x80000000
//#define MAKE_ABS_FLOAT(x) (*((DWORD *)&(x))) &= 0x7FFFFFFF
//#define MAKE_ABS_DOUBLE(x) (*(((DWORD *)&(x)) + 1)) &= 0x7FFFFFFF
//#define COPY_SIGN_FLOAT(to, from) { (*((DWORD *)&(to))) = ((*((DWORD *)&(to)))&0x7FFFFFFF) | ((*((DWORD *)&(from))) & 0x80000000); }
//#define SET_SIGN_FLOAT(to, sign) {*((DWORD *)&(to)) = ((*((DWORD *)&(to)))&0x7FFFFFFF) | ((DWORD(sign)) << 31); }
