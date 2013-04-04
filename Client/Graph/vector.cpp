#include "Vector.h"

Vector SetVector(float x, float y, float z)
{
	Vector tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

float GetVectorLength(Vector  v)
{
	return (float)(sqrt( v.x * v.x + v.y * v.y + v.z * v.z));
}

float	DistanceBetweenVector(Vector  v1, Vector  v2)
{
	return (float)(sqrt( (v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z) ));
}

float GetQuadVectorLength(Vector  v)
{
	return fabsf( v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector NormalizeVector(Vector v)
{
	Vector res;
	float l = GetVectorLength(v);
	if (l == 0.0f) return NULL_VECTOR;
	res.x = v.x / l;
	res.y = v.y / l;
	res.z = v.z / l;
	return res;
}

Vector operator+ (Vector v, Vector u)
{
	Vector res;
	res.x = v.x+u.x;
	res.y = v.y+u.y;
	res.z = v.z+u.z;
	return res;
}


Vector operator- (Vector v, Vector u)
{
	Vector res;
	res.x = v.x-u.x;
	res.y = v.y-u.y;
	res.z = v.z-u.z;
	return res;
}


Vector operator* (Vector v, float r)
{
	Vector res;
	res.x = v.x*r;
	res.y = v.y*r;
	res.z = v.z*r;
	return res;
}
Vector operator/ (Vector v, float r)
{
	Vector res;
	res.x = v.x/r;
	res.y = v.y/r;
	res.z = v.z/r;
	return res;
}


Vector CrossProduct (Vector * u, Vector * v)
{
	Vector resVector;
	resVector.x = u->y*v->z - u->z*v->y;
	resVector.y = u->z*v->x - u->x*v->z;
	resVector.z = u->x*v->y - u->y*v->x;

	return resVector;
}


float operator* (Vector v, Vector u)	//dot product
{
	return v.x*u.x+v.y*u.y+v.z*u.z;
}

Vector RandomVector()
{
	return SetVector( rand()/32768.0-0.5, rand()/32768.0-0.5, rand()/32768.0-0.5);
}

Vector ScaleVector(Vector v, float Scale)
{
	return SetVector( v.x * Scale, v.y * Scale, v.z * Scale);
}

float Lerp(float start, float stop, float t)
{
   return start+(stop-start)*t;
}

Vector VectorLerp(Vector V1, Vector  V2, float t)
{
   return SetVector(V1.x+(V2.x-V1.x)*t, V1.y+(V2.y-V1.y)*t, V1.z+(V2.z-V1.z)*t);
}
