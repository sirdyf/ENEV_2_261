#pragma once

#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#include <gl/gl.h>
#include <gl/glu.h>

class TScaner
{
	private:
		GLuint list_scan;
	public:
	TScaner();
	~TScaner();
	void DrawScaner();
};

