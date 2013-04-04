#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector.h"

class TCamera
{
private:
	
	float RotatedX, RotatedY, RotatedZ;	
	
public:

	Vector ViewDir;
	Vector RightVector;	
	Vector UpVector;
	Vector Position;
	
	float CameraMatrix[16]; 

	TCamera();				//inits the values
	void Apply ( void );	//executes some glRotates and a glTranslate command

	void Move 	 ( Vector Direction );
	void RotateX ( float Angle );
	void RotateY ( float Angle );
	void RotateZ ( float Angle );

	void MoveForward ( float Distance );
	void MoveUpward  ( float Distance );
	void StrafeRight ( float Distance );
	void StrafeLeft  ( float Distance );

	Vector GetViewDir		( void );
	Vector GetRightVector	( void );
	Vector GetUpVector		( void );
	Vector GetPosition		( void );
};
