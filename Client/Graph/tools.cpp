#include "Tools.h"

char str[256];	// Место для нашей строки

int	StarCount = 500;
Vector St[500];
GLuint list_num_star_back;


void InitStarField()
{
	Vector PosC = Vector(0,0,-1);
	float  rad=0;
	for( int i = 0; i < StarCount; i++)
	{
		St[i].x = rand() / 32767.0f - 0.5f;
		St[i].y = rand() / 32767.0f - 0.5f;
		St[i].z = rand() / 32767.0f - 0.5f;
		
		St[i] = NormalizeVector(St[i]);

		rad = 20 + rand() / 32767.0f * 100;

		St[i].x = (rand() / 32767.0f) * rad-rad/2;
		St[i].y = (rand() / 32767.0f) * rad-rad/2;
		St[i].z = (rand() / 32767.0f) * rad-rad/2;

		St[i].z = St[i].z - 25;
	}

	int	StarCountBack = 10000;
	list_num_star_back = glGenLists(1);
	glNewList( list_num_star_back, GL_COMPILE );
		//glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPointSize(1);
		glBegin(GL_POINTS);
			for( int i = 0; i < StarCountBack; i++)
			{
				Vector StBack;
				StBack.x = rand() / 32767.0f - 0.5f;
				StBack.y = rand() / 32767.0f - 0.5f;
				StBack.z = rand() / 32767.0f - 0.5f;

				StBack = NormalizeVector(StBack);
				StBack = StBack * 1900;

				//float color = rand() / 65535.0 + 0.5;
				float color = 0.1f + rand() / 65535.0f ;
				
				if (color > 0.5) color = 0.2f;

				glColor3f(color, color, color);
				glVertex3f(StBack.x, StBack.y, StBack.z);
			}
		glEnd();
		//glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
	glEndList();

}


void DrawStarField(TCamera Camera)
{

	Vector ViewDir 		= Camera.GetViewDir();
	Vector Position		= Camera.GetPosition();
	
	Vector PointPos;
	Vector PosC;
	
	glColor3f( 1, 1, 1 );
	for( int i=0; i < StarCount; i++)
	{
		PointPos = St[i];
		PosC = ViewDir * 25 + Position;

		if (GetQuadVectorLength(PointPos - PosC ) > 225)
		{
			St[i] = PosC + NormalizeVector(PosC - PointPos) * 14.99;
		}
	}

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_FOG);                       
	glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer( 3, GL_FLOAT, 0, St );
	glPointSize(2);
    glDrawArrays( GL_POINTS, 0, 50 );
	glPointSize(1);
    glDrawArrays( GL_POINTS, 0, StarCount-50 );
    glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_FOG);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	Vector campos = Camera.GetPosition();
	glTranslatef(campos.x, campos.y, campos.z);
	glCallList(list_num_star_back);

}


inline void GetStr(char *fmt, ...)
{
	va_list		ap;          			// Указатель на список аргументов
	va_start(ap, fmt);       			// Разбор строки переменных
	vsprintf(str, fmt, ap); 			// И конвертирование символов в реальные коды
	va_end(ap);                 		// Результат помещается в строку
}


BOOL LogText(char *lpszText, ...)
{
    va_list argList;
    FILE *pFile;

    // инициализируем список аргументов
    va_start(argList, lpszText);

    // открываем лог-файл для добавления данных
    if ((pFile = fopen("log.txt", "a+")) == NULL)
    return(FALSE);

    // пишем наш текст и переходим на новую строку
    vfprintf(pFile, lpszText, argList);
    putc('\n', pFile);

    // закрываем файл
    fclose(pFile);
    va_end(argList);

	return(TRUE);
}
