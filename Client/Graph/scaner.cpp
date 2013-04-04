#include "Scaner.h"

TScaner::TScaner()
{
	// создаем лист
	list_scan = glGenLists(1);
	
	glNewList( list_scan, GL_COMPILE );
	
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0, -1.5, -5);
	glRotatef(60, 1, 0, 0);

	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glPolygonMode(GL_FRONT, GL_LINE);

	float grad = 3.14159265358979323846 / 180;

	glColor3f(0.1, 0.1, 0.2);

	int ch=3;
	glBegin(GL_POLYGON);
	for(float i=110*grad; i <= 430*grad; i+=15.2*grad)
	{
		if (ch==3)
		{
			glVertex3f(0, 0, 0);
			ch = 1;
		}
		ch++;
		glVertex3f(cosf(i), sinf(i), 0);
	}		
	glVertex3f(0, 0, 0);
	glEnd();

	glColor3f(0.2, 0.2, 0.3);

	glBegin(GL_LINES);
	for(float i=110*grad; i <= 430*grad; i+=15.2*grad)
	{
		glVertex3f(cosf(i)*0.7, sinf(i)*0.7, 0);
	}		
	glEnd();

	glDisable(GL_LINE_SMOOTH);
	glPolygonMode(GL_FRONT, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
	glEndList();
}

TScaner::~TScaner()
{
	glDeleteLists(list_scan, 1);
}

void TScaner::DrawScaner()
{
	glCallList(list_scan);
}