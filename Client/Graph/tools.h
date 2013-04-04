#pragma once
#include <windows.h>
#include <stdio.h>
#include "camera.h"
#include "vector.h"

//extern float delta_time;
//extern int GlobalTimer;

void InitStarField();
void DrawStarField(TCamera Camera);
inline void GetStr(char *fmt, ...);

void ShowFPS(HWND hWnd);
BOOL LogText(char *lpszText, ...);

