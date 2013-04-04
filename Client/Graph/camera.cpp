#include "Camera.h"

TCamera::TCamera()
{
	//Init with standard OGL values:
	Position 	= Vector (0.0, 0.0, 0.0);
	ViewDir 	= Vector (0.0, 0.0, -1.0);
	RightVector = Vector (1.0, 0.0, 0.0);
	UpVector 	= Vector (0.0, 1.0, 0.0);

	RotatedX = RotatedY = RotatedZ = 0.0;
	//LogText("InitCamera");
}

void TCamera::Move (Vector Direction)
{
	Position = Position + Direction;
}


void TCamera::RotateX (float Angle)
{
	RotatedX += Angle;
	
	//Rotate viewdir around the right vector:
	ViewDir = NormalizeVector(ViewDir*cos(Angle*PIdiv180)
								+ UpVector*sin(Angle*PIdiv180));

	//now compute the new UpVector (by cross product)
	UpVector = CrossProduct(&ViewDir, &RightVector)*-1;
}

void TCamera::RotateY (float Angle)
{
	RotatedY += Angle;
	
	//Rotate viewdir around the up vector:
	ViewDir = NormalizeVector(ViewDir*cos(Angle*PIdiv180) - RightVector*sin(Angle*PIdiv180));

	//now compute the new RightVector (by cross product)
	RightVector = CrossProduct(&ViewDir, &UpVector);
}


void TCamera::RotateZ (float Angle)
{
	RotatedZ += Angle;
	
	//Rotate viewdir around the right vector:
	RightVector = NormalizeVector(RightVector*cos(Angle*PIdiv180)
								+ UpVector*sin(Angle*PIdiv180));

	//now compute the new UpVector (by cross product)
	UpVector = CrossProduct(&ViewDir, &RightVector)*-1;
}



void TCamera::MoveForward( float Distance )
{
	Position = Position + (ViewDir*-Distance);
}


void TCamera::StrafeRight ( float Distance )
{
	Position = Position + (RightVector*Distance);
}

void TCamera::StrafeLeft ( float Distance )
{
	Position = Position - (RightVector*Distance);
}

void TCamera::MoveUpward( float Distance )
{
	Position = Position + (UpVector*Distance);
}

void TCamera::Apply( void )
{
	//The point at which the camera looks:
	Vector ViewPoint = Position+ViewDir;

	//as we know the up vector, we can easily use gluLookAt:
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();

	gluLookAt(	Position.x,Position.y,Position.z,
				ViewPoint.x,ViewPoint.y,ViewPoint.z,
				UpVector.x,UpVector.y,UpVector.z);
	
    glGetFloatv(GL_PROJECTION_MATRIX, CameraMatrix);

	glLoadIdentity(); 
}

Vector TCamera::GetViewDir( void )
{
	return NormalizeVector(ViewDir);
}

Vector TCamera::GetRightVector( void )
{
	return Position + NormalizeVector(RightVector);
}

Vector TCamera::GetUpVector( void )
{
	return Position + NormalizeVector(UpVector);
}

Vector TCamera::GetPosition( void )
{
	return Position;
}
