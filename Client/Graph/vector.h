#pragma once
#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <d3dx8math.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>

#define SQR(x) (x*x)
#define NULL_VECTOR Vector(0.0f,0.0f,0.0f)
#define PI 3.1415926535897932384626433832795
#define PIdiv180 (PI/180.0)

class Vector { //Float 3d-vect, normally used
public:
     float x;
     float y;
     float z;
     Vector (float a,float b,float c){x=a;y=b;z=c;}
	 Vector (D3DXVECTOR3 a){x=a.x;y=a.y;z=a.z;}
     Vector (){x=0;y=0;z=0;}
    template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & BOOST_SERIALIZATION_NVP(x);
		ar & BOOST_SERIALIZATION_NVP(y);
		ar & BOOST_SERIALIZATION_NVP(z);
	}
};

Vector 		RandomVector();
Vector 		ScaleVector(Vector v, float Scale);
Vector 		VectorLerp(Vector V1, Vector  V2, float t);
float 		GetVectorLength( Vector v );
//float 		GetVectorLength( Vector v );
float		GetQuadVectorLength( Vector  v );
float		DistanceBetweenVector(Vector  v1, Vector  v2);
Vector 		NormalizeVector( Vector v );
Vector 		operator+ ( Vector v, Vector u );
Vector 		operator- ( Vector v, Vector u );
Vector 		operator* ( Vector v, float r );
Vector 		operator/ ( Vector v, float r );

Vector 		CrossProduct( Vector * u, Vector * v );     //Cross product
float 		operator* (Vector v, Vector u);				//Dot product		скалярное произведение
float		Lerp(float start, float stop, float t);
