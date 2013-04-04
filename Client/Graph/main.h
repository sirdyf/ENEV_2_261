#pragma once
#include <windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <MMSystem.h>
#include <stdarg.h> // Заголовочный файл для функций для работы с переменным количеством аргументов
#include <string>
#include <vector>
#include "camera.h"
#include "tools.h"
#include "vector.h"
#include "font.h"
#include "scaner.h"
#include "mesh.h"

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "glaux.lib")
#pragma comment (lib, "WinMM.Lib")

using namespace std;

class TScene
{
private:
		
	DWORD		GlobalTimer;

	DWORD		fps_time, fps_counter, fps_show, last_time; // расчет FPS
	
	HGLRC	hGLRC;
	int		_GetFps();

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
	void glPrint(GLint x, GLint y, const char *string, ...);
	void SetPos(float x, float y, float z);
	void SetOr(Vector x, Vector y, Vector z);
	void RenderPlanet(float radius, Vector pos, int NumMesh);
	void RenderShip(Vector pos, Vector dir, Vector up, int NumMesh,float scale=1.0f);
	void RenderShipPreview(Vector pos, Vector dir, Vector up, int NumMesh);
	void RenderStarField();
	void InitParticle(void);
	void DrawLine(Vector start, Vector end, Vector color);
	void DrawLine2D(float x1, float y1, float x2, float y2, Vector color);
	void DrawIndicator(float pr, GLint x, GLint y, char *str, ...);
	void DrawRadarLabel(Vector pos);
};
