/*---------------------- C++ source file -----------------------
 Project: ELITE
 Aliace:) Delite

Developer: DYF
 Website: www.elite-2k8.land.ru
 EMail: elite-2k8@land.ru

Original graph engine(LIB):
 Developer: KAS
--------------------------------------------------------------*/

#pragma once

#pragma warning (once:4786)//действует тока на этот CPP
#pragma warning (once:4005)
#pragma warning (once:4244)

#pragma comment (lib, "graph.lib")
//#pragma comment (lib, "ws2_32.lib")
//#pragma comment(lib, "IPHLPAPI.lib")

#include <winsock2.h>
//#include <iphlpapi.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <iphlpapi.h>

#include "boost\smart_ptr.hpp"

#include "graph.h"
#include "tWorld.h"
#include "tRender.h"
#include "..\main\log.h"
#include "..\main\tTick.h"
//--------------------network
//#include"..\main\tTransferData.h"
#include"..\network\tNetworkClient.h"

//bool g_bWork=true;

TScene *Scene=0;
HWND	hWnd=0;
HDC		hDC=0;

boost::intrusive_ptr<tWorld> World(new tWorld);
tRender my_render;
tNetworkClient netClient;
//tControl input;

bool bGameOver=false;
char g_diks[255]={0};

char space_name[65]="allexegezacebisousesarmaindirea?eratenberalavetiedorquanteisrion";

ESL::CLogFile SDELog("log.htm","Client Log");
ESL::CLogFile TMPlog("dump.htm","Dump Log");

std::string consoleString="";

LRESULT CALLBACK WindowFunc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR str, int nWinMode){	

	LOG_PREFIX("logs\\clientLog");
	LOG_LEVEL(logger::Debug); // уровень лога в рантайме (например, берём из командной строки)

	LOG_DEBUG << "WinMain starting..";
	Scene=0; hDC=0;
	int full=0; int WindowX=0; int WindowY=0; int Width=800; int Height=600;
	
	full	= GetPrivateProfileIntA("Options", "FullScreenEnable", 0, "Data/graph.ini");
	WindowX = GetPrivateProfileIntA("Options", "WindowX", 0, "Data/graph.ini");
	WindowY = GetPrivateProfileIntA("Options", "WindowY", 0, "Data/graph.ini");
	Width	= GetPrivateProfileIntA("Options", "Width", 800, "Data/graph.ini");
	Height	= GetPrivateProfileIntA("Options", "Height", 600, "Data/graph.ini");

Scene = new TScene();

	if ( full == 0 ){ 
		WNDCLASSA wcl;
			
		wcl.hInstance = hThisInst;
		wcl.lpszClassName = "OpenGLWinClass";
		wcl.lpfnWndProc = WindowFunc;
		wcl.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		
		wcl.hIcon = NULL;
		wcl.hCursor = LoadCursor(NULL,IDC_ARROW);
		wcl.lpszMenuName = NULL;
		
		wcl.cbClsExtra = 0;
		wcl.cbWndExtra = 0;
		
		wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//		RegisterClassA(&wcl);
		if ( !RegisterClassA(&wcl) ) return -1;//throw "RegisterClass";

		hWnd = CreateWindowA("OpenGLWinClass", "Elt",WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WindowX, WindowY, Width, Height, NULL, NULL, hThisInst, NULL);
		ShowWindow(hWnd, SW_SHOWNORMAL);
		UpdateWindow(hWnd);
	}	


	if ( full == 1 ){
		DEVMODE   ss;
		WNDCLASSA  wcl;

		memset(&ss, 0, sizeof(ss) );
		ss.dmSize    = sizeof(ss);
		ss.dmPelsWidth  = Width;
		ss.dmPelsHeight  = Height;
		ss.dmBitsPerPel  = 32;
		ss.dmFields    = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&ss, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) MessageBoxA(NULL, "Ошибка в ChangeDisplaySettings", "Error", MB_OK | MB_ICONSTOP);

		memset(&wcl, 0, sizeof(wcl) );
		wcl.lpfnWndProc		= (WNDPROC)WindowFunc;
		wcl.hInstance		= hThisInst;
		wcl.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
		wcl.hCursor			= LoadCursor(NULL, IDC_ARROW);
		wcl.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcl.lpszClassName	= "OpenGLWinClass";

		if ( !RegisterClassA(&wcl) ) return -1;//throw "RegisterClass";
		hWnd = CreateWindowA("OpenGLWinClass", "Elt", WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, Width, Height, NULL, NULL, hThisInst, NULL);
		if ( !hWnd ) return -1;//throw "CreateWindow";
		SetWindowPos( hWnd, HWND_TOPMOST, 0, 0, 0, 0, 1 ); 
		ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	}

	MSG msg;
	LOG_DEBUG << "WinMain started end";
	LOG_DEBUG << "World Init...";
	World->Init();
	LOG_DEBUG << "...End World Init";

//---network init
	LOG_DEBUG << "netClient.Init()";
	netClient.Init(World);
	//World->SetNetStatData(&netClient.mNetStat);
	netClient.SetTimeBetweenPacketsSend(500);
	LOG_DEBUG << "netClient.Run()";
	netClient.Run();
//---------------
	tTick gTick;
	gTick.Init(20);//50 раз в сек
	LOG_DEBUG << "Start Main loop";
	do{
		if(PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ))
		{
			if( msg.message == WM_QUIT ) break;
			TranslateMessage( &msg );
			DispatchMessage ( &msg );
		}
		World->CDM(); // Center of Decision Making (Graphics + Logic)
		gTick.Wait();//Зачем ждать? Перести в World->CDM() и если рано - не ждать а выходить
	}while(!bGameOver);
	LOG_DEBUG << "End Main loop";
	LOG_DEBUG << "World->Destroy()";
	World->Destroy();
//---network release
	LOG_DEBUG << "netClient.Stop()";
	netClient.Stop();
	LOG_DEBUG << "netClient.Release()";
	netClient.Release();
//----------
	if (Scene) delete Scene;
	LOG_DEBUG << "Scene deleted";

	LOG_DEBUG << "World destroy";
	DestroyWindow(hWnd);
	LOG_DEBUG << "Windows destroy";

	if ( full == 1 ) ChangeDisplaySettings(NULL, 0);
	LOG_DEBUG << "EXIT";
	return 0;
}

LRESULT CALLBACK WindowFunc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
			hDC	= GetDC(hWnd);
			Scene->Init(hDC);
		break; 

		case WM_DESTROY:
			ReleaseDC(hWnd, hDC);
			PostQuitMessage(0);
		break;
			
		case WM_SIZE:
			if (Scene) Scene->ResizeOpenGLWindow( LOWORD(lParam), HIWORD(lParam) );
		break;  
		
		case WM_KEYDOWN:
			g_diks[wParam] = 1;
			switch(wParam){
				case VK_ESCAPE:
				PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
		break;

   		case WM_KEYUP:
			g_diks[wParam] = 0;
		break;
		case WM_CHAR:
//			ProcessKeys(hWnd,msg,wParam,lParam);
//			engine->Console->cur_str+=(char)wParam;
			//if ((char)wParam!='`') 
			consoleString+=(char)wParam;
			break;
	}

	return DefWindowProc(hWnd,msg,wParam,lParam);
}

//HRESULT 
long D3DMath_VectorMatrixMultiply( D3DVECTOR& vDest, D3DVECTOR& vSrc,D3DMATRIX& mat){
    FLOAT x = vSrc.x*mat._11 + vSrc.y*mat._21 + vSrc.z* mat._31 + mat._41;
    FLOAT y = vSrc.x*mat._12 + vSrc.y*mat._22 + vSrc.z* mat._32 + mat._42;
    FLOAT z = vSrc.x*mat._13 + vSrc.y*mat._23 + vSrc.z* mat._33 + mat._43;
    FLOAT w = vSrc.x*mat._14 + vSrc.y*mat._24 + vSrc.z* mat._34 + mat._44;   
    if( fabs( w ) < g_EPSILON ) return E_INVALIDARG;
    vDest.x = x/w;vDest.y = y/w;vDest.z = z/w;
return S_OK;
}
