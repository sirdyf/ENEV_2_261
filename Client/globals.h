#if !defined(AFX_GLOBALS_H__INCLUDED_)
#define AFX_GLOBALS_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <d3dx8math.h>

//Ускорение некоторых операций с плавающей точкой
//Иногда требуется выполнить простейшую операцию с вещественным числом,
// например, изменить знак или вычислить абсолютное значение.
//Если ваше вещественное число оказалось в памяти ( например это значение
// переменной и оптимизатор ее не сократил ), то некоторые операции 
// быстрее выполнять непосредственно меняя биты вещественного числа.
//Вот некоторые макросы, которые это делают:

#define NEG_FLOAT(x) (*((DWORD *)&(x))) ^= 0x80000000
#define MAKE_ABS_FLOAT(x) (*((DWORD *)&(x))) &= 0x7FFFFFFF
#define MAKE_ABS_DOUBLE(x) (*(((DWORD *)&(x)) + 1)) &= 0x7FFFFFFF
#define COPY_SIGN_FLOAT(to, from) { (*((DWORD *)&(to))) = ((*((DWORD *)&(to)))&0x7FFFFFFF) | ((*((DWORD *)&(from))) & 0x80000000); }
#define SET_SIGN_FLOAT(to, sign) {*((DWORD *)&(to)) = ((*((DWORD *)&(to)))&0x7FFFFFFF) | ((DWORD(sign)) << 31); }
/*
#define g_PI         3.14159265358979323846f // Pi
#define g_2_PI       6.28318530717958623200f // 2 * Pi
#define g_PI_DIV_2   1.57079632679489655800f // Pi / 2
#define g_PI_DIV_4   0.78539816339744827900f // Pi / 4
#define g_INV_PI     0.31830988618379069122f // 1 / Pi
#define g_DEGTORAD   0.01745329251994329547f // Degrees to Radians
#define g_RADTODEG  57.29577951308232286465f // Radians to Degrees
#define g_HUGE       1.0e+38f                // Huge number for FLOAT
#define g_EPSILON    1.0e-5f                 // Tolerance for FLOATs

#define g_ZDS		1500.0 //Зона Действия Станции
#define g_PLANETMAP	200000000.0f // масштабный коэф-т для расстояний между планетами в режиме планетарной карты
#define g_KURP		150000.0f //коэф-т уменьшения радиуса планеты в режиме планетарной карты
#define g_RS		500.0f // Radar Sensetive - чувствительность радара
#define g_DSD		100.0f //DockShipDistance - дистанция на которой корабль считается пристыковывающимся
*/
const float g_PI       =  3.14159265358979323846f; // Pi
const float g_2_PI     =  6.28318530717958623200f; // 2 * Pi
const float g_PI_DIV_2 =  1.57079632679489655800f; // Pi / 2
const float g_PI_DIV_4 =  0.78539816339744827900f; // Pi / 4
const float g_INV_PI   =  0.31830988618379069122f; // 1 / Pi
const float g_DEGTORAD =  0.01745329251994329547f; // Degrees to Radians
const float g_RADTODEG = 57.29577951308232286465f; // Radians to Degrees
const float g_HUGE     =  1.0e+38f;                // Huge number for FLOAT
const float g_EPSILON  =  1.0e-5f;                 // Tolerance for FLOATs

const float g_PLANETMAP	=200000000.0f; // масштабный коэф-т для расстояний между планетами в режиме планетарной карты
const float g_KURP		=150000.0f; //коэф-т уменьшения радиуса планеты в режиме планетарной карты
const float g_RS		=500.0f; //Radar Sensetive - чувствительность радара
const float g_DSD		=100.0f; //DockShipDistance - дистанция на которой корабль считается пристыковывающимся
const float g_ZDS		=5000.0f;//Зона Действия Станции
const float g_CZ		=300.0f; //Зона Стыковки

//Быстрая конверсия из double в int
//Нашел в туторе по оптимизации для AMD.
static inline int dtoi(double d){
  const double t = d + 6755399441055744.0;
  return *((int *)(&t));
}



/*
bool D3DMath_VectorCompare( D3DVECTOR3& vDest, D3DVECTOR3& vSrc){
	float a=D3DXVec3LengthSq(&vDest);//vDest.x*vDest.x+vDest.y*vDest.y+vDest.z*vDest.z;
	float b=D3DXVec3LengthSq(&vSrc);//vSrc.x*vSrc.x+vSrc.y*vSrc.y+vSrc.z*vSrc.z;
	if (a>=b) return true;
	else return false;
}
bool D3DMath_VectorCompareDist( D3DVECTOR3& vDest, float dist){
	float a=D3DXVec3LengthSq(&vDest);//vDest.x*vDest.x+vDest.y*vDest.y+vDest.z*vDest.z;
	float b=dist*dist;
	if (a>=b) return true;
	else return false;
}
*/
#endif