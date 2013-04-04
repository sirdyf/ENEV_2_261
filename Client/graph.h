#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <vector>
#include "graph\vector.h"

using namespace std;
/*
struct Vector  //Float 3d-vect, normally used
{
	float x;
	float y;
	float z;
};
*/
/*
Vector CreateVector(float x, float y, float z)
{
	Vector tmp; tmp.x = x; tmp.y = y; tmp.z = z; return tmp;
}
*/
class TScaner
{
	private:
		GLuint list_scan;
	public:
	TScaner();
	~TScaner();
	void DrawScaner();
};

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

class TMesh
{
	private:
	public:
		TMesh();
		~TMesh();
		//Vector Position;
		GLuint VertexId;
		GLuint NormalId;
		float mat_ambient[3];
		float mat_diffuse[3];
		float mat_specular[3];
		float mat_shine[1];
		GLuint list_num;
		//float sx, sy, sz;
		unsigned int Vertices;
		unsigned int NumIndex;
		unsigned int Faces;
		int LoadModel(char *filename);
		void Render(void);
};

class TScene
{
private:
		
	DWORD		GlobalTimer;

	DWORD		fps_time, fps_counter, fps_show, last_time; // расчет FPS
	
	HGLRC	hGLRC;

public:
		
	struct part
	{
		float	age;
		float	speed;
		float	color;
		Vector	pos;
		Vector	dir;
	};

	vector <part> k;

	TScene();
	~TScene();

	TCamera *Camera;
	TScaner *Scaner;
	TMesh   *Mesh;

	int		GetFps();
	float	delta_time;
	void Init(HDC hDC);
	void StartRender(void);
	void EndRender(void);
	void TestRender(Vector pos);
	void SetDefaultOpenGL(void);
	void ResizeOpenGLWindow(int width, int height);
	void glPrint(GLint x, GLint y, char const *string, ...);
	void SetPos(float x, float y, float z);
	void SetOr(Vector x, Vector y, Vector z);
	void RenderPlanet(float radius, Vector pos, int NumMesh);
	void RenderShip(Vector pos, Vector dir, Vector up, int NumMesh, float scale=1.0f);
	void RenderShipPreview(Vector pos, Vector dir, Vector up, int NumMesh);
	void RenderStarField();
	void InitParticle(void);
	void DrawLine(Vector start, Vector end, Vector color);
	void DrawLine2D(float x1, float y1, float x2, float y2, Vector color);
	void DrawIndicator(float pr, GLint x, GLint y, char *str, ...);
	void DrawRadarLabel(Vector pos);
};
