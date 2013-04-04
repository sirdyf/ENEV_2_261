// http://www.pmg.org.ru/nehe/nehe13.htm
// http://www.mirgames.ru/articles/opengl/around_gl.html
#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <stdio.h>

GLvoid PrintText(GLint x, GLint y,  const char *string);		// Where The Printing Happens
GLvoid KillFont(GLvoid);								// Delete The Font From Memory
GLvoid BuildFont(GLvoid);								// Build Our Font Display List
GLuint LoadTexture( const char * filename, int width, int height ); // Load Bitmaps And Convert To Textures
GLvoid PrintIndicator(float pr, GLint x, GLint y, char *string);

