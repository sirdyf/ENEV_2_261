#include "main.h"

float ProjectionMatrix[16]={0}; 


TScene::TScene()
{
}

void TScene::Init(HDC hDC)
{
	bool err=0;
	LogText("Start create Scene");

	fps_time = 0; fps_counter = 0; fps_show = 0; last_time = GetTickCount(); // расчет FPS

	int m_GLPixelIndex;
    PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize          = sizeof(pfd);
    pfd.nVersion       = 1;
    pfd.dwFlags		   = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType     = PFD_TYPE_RGBA;
    pfd.cColorBits     = 32;
    pfd.cRedBits       = 0;
    pfd.cRedShift      = 0;
    pfd.cGreenBits     = 0;
    pfd.cGreenShift    = 0;
    pfd.cBlueBits      = 0;
    pfd.cBlueShift     = 0;
    pfd.cAlphaBits     = 0;
    pfd.cAlphaShift    = 0;
    pfd.cAccumBits     = 0;    
    pfd.cAccumRedBits  = 0;
    pfd.cAccumGreenBits   = 0;
    pfd.cAccumBlueBits    = 0;
    pfd.cAccumAlphaBits   = 0;
    pfd.cDepthBits        = 32;
    pfd.cStencilBits      = 0;
    pfd.cAuxBuffers       = 0;
    pfd.iLayerType        = PFD_MAIN_PLANE;
    pfd.bReserved         = 0;
    pfd.dwLayerMask       = 0;
    pfd.dwVisibleMask     = 0;
    pfd.dwDamageMask      = 0;

    m_GLPixelIndex = ChoosePixelFormat( hDC, &pfd);
    
	if(m_GLPixelIndex==0) // Let's choose a default index.
    {
		m_GLPixelIndex = 1;    
		if(DescribePixelFormat(hDC,m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pfd)==0)
		{
			LogText("err: DescribePixelFormat");
			err = 0;
		}
    }

    if (SetPixelFormat( hDC, m_GLPixelIndex, &pfd)==FALSE)
	{
		LogText("err: SetPixelFormat");
        err = 1;
	}

	hGLRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hGLRC);

	if (err==0)
		LogText("End sucsesful create Scene");
	else
		LogText("err: create Scene!");

	SetDefaultOpenGL();
}

TScene::~TScene()
{
	delete Camera;
	delete Scaner;
	delete []Mesh;

	KillFont();
	if (hGLRC) 
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hGLRC);
	}
}


int TScene::_GetFps()
{
	int current_ticks = GlobalTimer;
	delta_time  = (current_ticks - last_time) / 1000.0;
	last_time   = current_ticks;

	if (delta_time > 50) delta_time = 0;  // удобная защита от скачков

    if ((current_ticks - fps_time) > 1000) 
	{
        fps_show = fps_counter;
        fps_counter = 0;
        fps_time = current_ticks;
    }
	fps_counter++;
	return fps_show;
}
int TScene::GetFps(){
	return fps_show;
}
void TScene::glPrint(GLint x, GLint y, const char *str, ...)
{

	char string[256];
	va_list	ap;          			// Указатель на список аргументов
	va_start(ap, str);       		// Разбор строки переменных
	vsprintf(string, str, ap);		// И конвертирование символов в реальные коды
	va_end(ap);

	PrintText(x, y, string);
}

void TScene::SetDefaultOpenGL(void)
{
	LogText("Set Default OpenGL");

	float mat_ambient[4] = { 0.4f, 0.2f, 0.2f, 1.0f };
	float mat_diffuse[4] = { 0.5f, 0.2f, 0.2f, 1.0f };
//	float mat_specular[4]= { 1.0f, 1.0f, 1.0f, 1.0f };
	float mat_specular[4]= { 0.0f, 0.0f, 0.0f, 0.0f };

	//Параметры источника света
	float light_position[4]={2.0f,0.0f,2.0f,0.0f};
	float light_intensity[4]={1.0f,1.0f,1.0f,1.0f};
	
	glMaterialf(GL_FRONT,GL_SHININESS,25.0);

	glLightfv(GL_LIGHT0,GL_AMBIENT, light_intensity);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_intensity);
	glLightfv(GL_LIGHT0,GL_DIFFUSE, light_intensity);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);

	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Начальные установки
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glewInit();
	
	int VSync = GetPrivateProfileInt("Options", "VSync", 0, "Data/graph.ini");
	if(wglSwapIntervalEXT) wglSwapIntervalEXT(VSync);	// отключаем вертикальную синхронизацию, 1 - включить

	glEnable(GL_BLEND);

	//Туман
	//glEnable(GL_FOG);                       // Включает туман (GL_FOG)

	//GL_EXP 	- Обычный туман, заполняющий весь экран. Во многом он напоминает туман отдаленно, но легко справляется со своей работой даже на старых PC.
	//GL_EXP2 	- Это следующий шаг после GL_EXP. Затуманит весь экран, за то придает больше глубины всей сцене.
	//GL_LINEAR - Это лучший режим прорисовки тумана. Объекты выходят из тумана и исчезают в нем гораздо лучше.	glFogi(GL_FOG_MODE, fogMode[fogfilter]);// Выбираем тип тумана
	glFogi(GL_FOG_MODE, GL_LINEAR);// Выбираем тип тумана
	float fogColor[4]= {0.0f, 0.0f, 0.0f, 0.0f}; // Цвет тумана
	glFogfv(GL_FOG_COLOR, fogColor);        // Устанавливаем цвет тумана
	// устанавливает, насколько густым будет туман. Увеличьте число, и туман станет более густым, уменьшите - менее густым
	glFogf(GL_FOG_DENSITY, 0.0f);          // Насколько густым будет туман
	//GL_DONT_CARE - позволяет OpenGL выбрать формулу для расчета тумана (по вершинам или по пикселям).
	//GL_NICEST - Создает туман по пикселям (хорошо смотрится).
	//GL_FASTEST - Вычисляет туман по вершинам (быстрее, но не так красиво)) .	glHint(GL_FOG_HINT, GL_DONT_CARE);      // Вспомогательная установка тумана
	glHint(GL_FOG_HINT, GL_FASTEST );      
	glFogf(GL_FOG_START, 0.0f);             // Глубина, с которой начинается туман
	glFogf(GL_FOG_END, 40.0f);              // Глубина, где туман заканчивается.

	LogText("End sucsesful Set Default OpenGL");

	BuildFont();
	InitStarField();

	Scaner = new TScaner();
	Camera = new TCamera();

	std::string SectionName="";
	int NumMesh = GetPrivateProfileInt("Mesh", "NumMesh", 0, "Data/graph.ini");
	Mesh   = new TMesh[NumMesh+1];

		char buf[30];
		char FileName[100];
	for (int i=1; i<=NumMesh; i++)
	{
		sprintf(buf, "%d", i);
		SectionName = "FileMesh";
		SectionName += buf;
		GetPrivateProfileStringA("Mesh", SectionName.c_str(), "", FileName, 100, "Data/graph.ini");
		Mesh[i].LoadModel(FileName);
	}

	//InitParticle();	// тестовя функция
}

void TScene::ResizeOpenGLWindow(int width, int height)
{
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	//Angle of view:40 degrees, aspect, near, far
	gluPerspective(40.0, (GLdouble)width/(GLdouble)height, 1.0, 2000.0);
	glViewport(0, 0, width, height);  //Use the whole window for rendering
    glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}    

void TScene::StartRender(void)
{
	GlobalTimer = timeGetTime();
	this->_GetFps();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
//	glMatrixMode(GL_PROJECTION);  
//	glLoadIdentity();
	
	Camera->Apply();
	glMultMatrixf(ProjectionMatrix);
	glMultMatrixf(Camera->CameraMatrix);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TScene::RenderPlanet(float radius, Vector pos, int NumMesh)
{
	glLoadIdentity();

	float dist = DistanceBetweenVector(pos, Camera->GetPosition());
	//glPrint(10, 60, "dist: %f", dist);

	if (dist < 1000.0f)
	{
		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(radius, radius, radius);
		//glPrint(10, 90, "PosPlanet: %f, %f, %f", pos.x, pos.y, pos.z);
	}
	else
	{
		Vector cam  = Camera->GetPosition(); 
		Vector a	= NormalizeVector( cam - pos);
		pos = cam - ScaleVector ( a, 1000.0f );
		glTranslatef( pos.x, pos.y, pos.z );
		float scale = (radius / dist) * 1000.0f;
		glScalef(scale, scale, scale);
		//glPrint(10, 90, "PosPlanet: %f, %f, %f", pos.x, pos.y, pos.z);
		//glPrint(10, 120, "scale: %f", scale);
	}

	Mesh[NumMesh].Render();

}


void TScene::RenderShip(Vector pos,Vector dir, Vector up, int NumMesh,float sc)
{
	glMatrixMode(GL_MODELVIEW);  
    glPushMatrix();
	glLoadIdentity();
	float mmodel[16]={0}; 
    gluLookAt(0,0,0,-dir.x,-dir.y,-dir.z,up.x,up.y,up.z);// ???
//    glPushMatrix();
    glGetFloatv(GL_MODELVIEW_MATRIX, mmodel);
//    glPopMatrix();
    glLoadIdentity();
    glTranslatef(pos.x, pos.y, pos.z);
//    glMultTransposeMatrixf(mmodel);
    glMultMatrixf(mmodel);
	glScalef(sc, sc, sc);//dyf
    Mesh[NumMesh].Render();
    glPopMatrix();
}
void TScene::RenderShipPreview(Vector pos,Vector dir, Vector up, int NumMesh)
{	
//  glPushMatrix();
//	glLoadIdentity();
	float mmodel[16]={0}; 
	Vector a(0,0,0),b(0,0,0);
	Vector eye=Camera->GetPosition()-pos;
		eye=NormalizeVector(eye);
		a=CrossProduct(&eye,&Camera->UpVector);
		a=NormalizeVector(a);
		b=CrossProduct(&a,&eye);//*-1.0f;
//		D3DXMatrixLookAtLH (&matView, &(eye*150.0f),&(b*50.0f),	&World.aiGlobal.cam->GetTy());
	glMatrixMode(GL_MODELVIEW);  
	glLoadIdentity();
    gluLookAt(eye.x*40.0f,eye.y*40.0f,eye.z*40.0f,-b.x*10.0f,-b.y*10.0f,-b.z*10.0f,Camera->UpVector.x,Camera->UpVector.y,Camera->UpVector.z);
//		engine->m_d3dDevice->SetTransform (D3DTS_VIEW, &matView);
    glGetFloatv(GL_MODELVIEW_MATRIX, mmodel);
//		World.resManager.m_Res[World.aiGlobal.cam->target->gRes].p_d3dx_mesh->DrawSubset( 0 );

//	if (World.aiGlobal.cam->target){
//		matWorld=World.aiGlobal.cam->target->GetCurMatrix();
//		engine->m_d3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	glMultMatrixf(ProjectionMatrix);
//    glMultTransposeMatrixf(mmodel);
	glMultMatrixf(mmodel);
//    glPushMatrix();
//    glPopMatrix();
	glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    gluLookAt(0,0,0,dir.x,dir.y,dir.z,up.x,up.y,up.z);
    glGetFloatv(GL_MODELVIEW_MATRIX, mmodel);
//    glPopMatrix();
    glLoadIdentity();
//    glTranslatef(pos.x, pos.y, pos.z);
    glMultTransposeMatrixf(mmodel);
    Mesh[NumMesh].Render();
//    glPopMatrix();
}
void TScene::RenderStarField()
{
	glLoadIdentity();
	DrawStarField(*Camera);
}

void TScene::SetPos(float x, float y, float z)
{
	glLoadIdentity();
	glTranslatef(x,y,z);
}
void TScene::SetOr(Vector dir, Vector up, Vector right)
{
	gluLookAt(dir.x, dir.y, dir.z, up.x, up.y, up.z, right.x, right.y, right.z);
}

void TScene::EndRender(void)
{
	glFinish();
	SwapBuffers(wglGetCurrentDC());
}



void TScene::InitParticle(void)
{
/*
	part p;

	for(int i=0; i<=100; i++)
	{
		p.age = 1.0f;
		p.speed = (rand() / 32767.0) / 1000.0 + 0.0005;

		p.pos.x = rand() / 32767.0 - 0.5;
		p.pos.y = 0;
		p.pos.z = 0;
		
		p.dir.x = 0;
		p.dir.y = (rand() / 32767.0) / 1000.0 + 0.0001 * 5;
		p.dir.z = 0;
		
		p.color = rand() / 32767.0 / 2 + 0.1;

		k.push_back(p);
	}
*/
/*
	for(int i=0; i<=50; i++)
	{
		p.pos.x = 0;
		p.pos.y = 0;
		p.pos.z = 0;
		k.push_back(p);
	}
*/
}

void TScene::TestRender(Vector pos)
{
/*
	glLoadIdentity();
	part p;

	dt += delta_time;
	if (dt > 0.06)
	{
		dt=0;
		p.pos.x = pos.x;
		p.pos.y = pos.y;
		p.pos.z = pos.z;
		k.insert(k.begin(), p);
		
		k.pop_back();
	}

	glBegin(GL_LINE_STRIP);
	for(int i=0; i<k.size(); i++) 
	{
		float col = 1-i/50.0f;
		glColor3f(col, col, col);
		glVertex3f(k[i].pos.x, k[i].pos.y, k[i].pos.z);
	}
	glEnd();
	
/*
	for(int i=0; i<k.size(); i++) 
	{
		k[i].age = k[i].age - k[i].speed;
		
		if (k[i].age >= 0 )
		{
			k[i].pos = k[i].pos + k[i].dir;
		}
		else
		{
			k[i].age = 1.0f;
			k[i].speed = (rand() / 32767.0) / 1000.0 + 0.0005;

			k[i].pos.x = rand() / 32767.0 - 0.5;
			k[i].pos.y = 0;
			k[i].pos.z = 0;
			
			k[i].dir.x = 0;
			k[i].dir.y = (rand() / 32767.0) / 1000.0 + 0.0001 * 5;
			k[i].dir.z = 0;
	
			k[i].color = rand() / 32767.0 / 2 + 0.1;
		}
	}

	glPointSize(1);
	glBegin(GL_POINTS);
		for(int i=0; i<k.size(); i++) 
		{
			glColor3f(k[i].age, k[i].age, k[i].age);
			k[i].pos.x = Lerp(k[i].pos.x, 0, k[i].age);
			glVertex3f(k[i].pos.x, k[i].pos.y, k[i].pos.z);
		}
	glEnd();

	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex3f(-1, 0, -10);
		glColor3f(0.1, 0.1, 0.1);
		glVertex3f(1, 0, -10);
	glEnd();
*/
/*	
	float ctrlpoints[3][3]={  {-4.0,-4.0,0.0},
								{-5.0,5.0,0.0},
								//{0.0,0.0,0.0},
								{4.0,4.0,0.0}};
	glColor3f(0.0f, 0.5f, 0.5f);

	glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,3,&ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);

	glTranslatef(0,0,-15);

	//glRotatef(GlobalTimer / 50.0, 1, 0, 0);
	
	glBegin(GL_LINE_STRIP);
		for(int i=0; i<=10; i++) glEvalCoord1f((float)i/10.0f);
	glEnd();

      glPointSize(5.0);
      glColor3f(1.0,1.0,0.0);
      glBegin(GL_POINTS);
            for(int i=0;i<3;i++)
                  glVertex3fv(&ctrlpoints[i][0]);
      glEnd();

	glLoadIdentity();

	//glTranslatef(-3,0,-10);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0,1.0,1.0);
	glVertex3f( 0.0, 1.0, 0.0);                  // Верх треугольника (Передняя)
	glVertex3f(-1.0,-1.0, 1.0);                  // Левая точка
	glVertex3f( 1.0,-1.0, 1.0);                  // Правая точка
	glVertex3f( 0.0, 1.0, 0.0);                  // Верх треугольника (Правая)
	glVertex3f( 1.0,-1.0, 1.0);                  // Лево треугольника (Правая)
	glVertex3f( 1.0,-1.0, -1.0);                 // Право треугольника (Правая)
	glVertex3f( 0.0, 1.0, 0.0);                  // Низ треугольника (Сзади)
	glVertex3f( 1.0,-1.0, -1.0);                 // Лево треугольника (Сзади)
	glVertex3f(-1.0,-1.0, -1.0);                 // Право треугольника (Сзади)
	glVertex3f( 0.0, 1.0, 0.0);                  // Верх треугольника (Лево)
	glVertex3f(-1.0,-1.0,-1.0);                  // Лево треугольника (Лево)
	glVertex3f(-1.0,-1.0, 1.0);                  // Право треугольника (Лево)
	glEnd();

	glLoadIdentity();
*/
}


void TScene::DrawLine(Vector start, Vector end, Vector color)
{
	glLoadIdentity();
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_LINES);
		glVertex3f(start.x, start.y, start.z);
		glVertex3f(end.x, end.y, end.z);
	glEnd();

}

void TScene::DrawLine2D(float x1, float y1, float x2, float y2, Vector color)
{
	/*
	glOrtho(0,800,0,600,-1,1);							// Set Up An Ortho Screen
	glTranslated(x,y,0);								// Position The Text (0,0 - Bottom Left)
	glListBase(base);								    // Choose The Font
        glColor3f(0.6f, 0.6f, 0.6f);
	glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen
	*/
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	glOrtho(0,1,0,1,-1,1);								// Set Up An Ortho Screen

	glColor3f(color.x, color.y, color.z);
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}

void TScene::DrawIndicator(float pr, GLint x, GLint y, char *str, ...)
{
	char string[256];
	va_list	ap;          			// Указатель на список аргументов
	va_start(ap, str);       		// Разбор строки переменных
	vsprintf(string, str, ap);		// И конвертирование символов в реальные коды
	va_end(ap);
	
	PrintIndicator(pr, x, y, string);
}
#define g_EPSILON    1.0e-5f                 
// Tolerance for FLOATs

HRESULT OGLMath_VectorMatrixMultiply( Vector& vDest, Vector& vSrc,float mat[16]){
//    FLOAT x = vSrc.x*mat[ 0] + vSrc.y*mat[ 1] + vSrc.z* mat[ 2] + mat[ 3];
//    FLOAT y = vSrc.x*mat[ 4] + vSrc.y*mat[ 5] + vSrc.z* mat[ 6] + mat[ 7];
//    FLOAT z = vSrc.x*mat[ 8] + vSrc.y*mat[ 9] + vSrc.z* mat[10] + mat[11];
//    FLOAT w = vSrc.x*mat[12] + vSrc.y*mat[13] + vSrc.z* mat[14] + mat[15];   

	FLOAT x = vSrc.x*mat[ 0] + vSrc.y*mat[ 4] + vSrc.z* mat[ 8] + mat[12];
	FLOAT y = vSrc.x*mat[ 1] + vSrc.y*mat[ 5] + vSrc.z* mat[ 9] + mat[13];
	FLOAT z = vSrc.x*mat[ 2] + vSrc.y*mat[ 6] + vSrc.z* mat[10] + mat[14];
	FLOAT w = vSrc.x*mat[ 3] + vSrc.y*mat[ 7] + vSrc.z* mat[11] + mat[15];   

    if( fabs( w ) < g_EPSILON ) return E_INVALIDARG;
    vDest.x = x/w;vDest.y = y/w;vDest.z = z/w;
return S_OK;
}

void TScene::DrawRadarLabel(Vector pos)
{
	// Draw Radar Slots
	glMatrixMode(GL_MODELVIEW);
	Vector col(0.25f,0.25f,0);
//	DrawLine2D(0.3f,0,0.7f,0,Vector(1,1,0));
	DrawLine2D(0.7f,0,0.7f,0.3f,col);
	DrawLine2D(0.7f,0.3f,0.3f,0.3f,col);
	DrawLine2D(0.3f,0.3f,0.3f,0,col);

	DrawLine2D(0.3f,1,0.3f,0.7f,col);
	DrawLine2D(0.3f,0.7f,0.7f,0.7f,col);
	DrawLine2D(0.7f,0.7f,0.7f,1,col);

	Vector lskPos(0,0,0),lskPos2(0,0,0),tmpV(0,0,0);
	float tmp=0;
	OGLMath_VectorMatrixMultiply( lskPos, pos, Camera->CameraMatrix);
	lskPos2=lskPos;
/*
	float mmodel[16]={0}; 
    gluLookAt(0,0,0,dir.x,dir.y,dir.z,up.x,up.y,up.z);
//    glPushMatrix();
    glGetFloatv(GL_MODELVIEW_MATRIX, mmodel);
//    glPopMatrix();
    glLoadIdentity();
    glTranslatef(pos.x, pos.y, pos.z);
    glMultTransposeMatrixf(mmodel);*/
	//Camera->Apply();
	float l=2000.0f-GetVectorLength(Camera->GetPosition()-pos);
	lskPos.x=lskPos.x/(3000.0f-l)+0.5f+0.35f;
	lskPos.y=lskPos.y/(3000.0f-l);//+0.5f;
	lskPos.z=-lskPos.z/(3000.0f-l)+0.5f-0.35f;
	if (lskPos.y>0.3f) lskPos.y=0.3f;
	if (lskPos.y<-0.3f) lskPos.y=-0.3f;
	DrawLine2D(lskPos.x, lskPos.z, lskPos.x, lskPos.z+lskPos.y, Vector(1,1,1));
	DrawLine2D(lskPos.x, lskPos.z+lskPos.y, lskPos.x+0.01f, lskPos.z+lskPos.y, Vector(1,1,1));
	DrawLine2D(0.85-0.01f,0.15,0.85+0.01f,0.15,Vector(1,1,1));
	DrawLine2D(0.85,0.15-0.01f,0.85,0.15+0.01f,Vector(1,1,1));

// Draw Label of Sphere Radar
	float mmodel[16]={0}; 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(0,0,10,0,2.3f,1,0,1,0);
    glGetFloatv(GL_MODELVIEW_MATRIX, mmodel);

	lskPos2=NormalizeVector(lskPos2)*1.2f;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(ProjectionMatrix);
	glMultMatrixf(mmodel);
	glMatrixMode(GL_MODELVIEW);
//	tmpV=Camera->GetPosition();
//	DrawLine(Vector(tmpV.x,tmpV.y,tmpV.z-1.0f),Vector(tmpV.x+50.0f,tmpV.y+50.0f,tmpV.z-100.0f), Vector(1,1,1));
//	DrawLine(Vector(0,0,0),Vector(100,100,-100),Vector(1,1,1));
	DrawLine(Vector(0,0,0),lskPos2,Vector(1,1,1));
//	glBlendFunc(GL_SRC_ALPHA,GL_NONE);					// Select The Type Of Blending
//	glEnable(GL_COLOR_MATERIAL);
//	glDisable(GL_LIGHTING);
//	glDisable(GL_LIGHT0);
	RenderPlanet(0.25f,Vector(0,0,0),6);
//	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(ProjectionMatrix);
	glMultMatrixf(Camera->CameraMatrix);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/*
procedure TForm1.RenderScaner(Obj: TGLBaseSceneObject; Color: TVector4f);
var
  v,v1: TVector;
  Scale: Single;
begin
  Scale := GLCamera1.DistanceTo(Obj);
  v:=VectorScale(GLCamera1.AbsoluteToLocal(TGLBaseSceneObject(Obj).AbsolutePosition), 0.3/Scale);
  v[2] := -v[2]; v1 := v; v[0] := v[0]-0.02;
  GLLines1.AntiAliased := true;
  GLLines1.AddNode(v);
  GLLines1.AddNode(v1);
  GLLines1.AddNode(v1);
  v1[1]:=0;
  GLLines1.AddNode(v1);
end;
*/
/*
void TScene::DrawRadarLabel(Vector pos)
{
	Vector v, v1;
	float Scale=DistanceBetweenVector(Camera->Position, pos);

	v = ScaleVector(v,0.3/Scale);
	v.z = -v.z; v1 = v; v.x = v.x-0.02;

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
		glVertex3f(v.x, v.y, v.z);
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v1.x, v1.y, v1.z);
		v1.y=0;
		glVertex3f(v1.x, v1.y, v1.z);
	glEnd();

	glPrint(10,128,"v:%f %f %f", v.x, v.y, v.z);
	glPrint(10,112,"pos:%f.2 %f.2 %f.2", pos.x, pos.y, pos.z);

	//OGLMath_VectorMatrixMultiply( lskPos, pos, Camera->CameraMatrix);

	//DrawLine2D(lskPos.x, lskPos.z, lskPos.x, lskPos.z+lskPos.y, Vector(1,1,1));
	//DrawLine2D(lskPos.x, lskPos.z+lskPos.y, lskPos.x+0.01f, lskPos.z+lskPos.y, Vector(1,1,1));
}
*/