#include "Font.h"

GLuint	base;				// Base Display List For The Font
GLuint	loop;				// Generic Loop Variable
GLuint	texture;			// Storage For Our Font Texture

GLuint LoadTexture( const char * filename, int width, int height )
{
	GLuint texture;
	unsigned char * data;
	FILE * file;
	file = fopen( filename, "rb" ); 
	if ( file == NULL ) return 0;
	data = (unsigned char *)malloc( width * height * 3 );
	fread( data, 54, 1, file );	 // заголовок BMP 54 байта отбрасываем
	fread( data, width * height * 3, 1, file ); 
	fclose( file ); 
	glGenTextures( 1, &texture ); 
	glBindTexture( GL_TEXTURE_2D, texture ); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); 
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	free( data ); 
	return texture;
}

GLvoid BuildFont(GLvoid)								// Build Our Font Display List
{
	float	cx;											// Holds Our X Character Coord
	float	cy;											// Holds Our Y Character Coord
	
	texture = LoadTexture("Data/font.bmp", 256, 256);

	base=glGenLists(256);								// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, texture);				// Select Our Font Texture
	for (loop=0; loop<256; loop++)						// Loop Through All 256 Lists
	{
		cx=float(loop%16)/16.0f;				// X Position Of Current Character
		cy=float(loop/16)/16.0f;						// Y Position Of Current Character
	
		glNewList(base+loop, GL_COMPILE);				// Start Building A List
			glBegin(GL_QUADS);							// Use A Quad For Each Character
				glTexCoord2f(cx, 1-cy-0.0625f);			// Texture Coord (Bottom Left)
				glVertex2i(0,0);						// Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f, 1-cy-0.0625f);	// Texture Coord (Bottom Right)
				glVertex2i(16,0);						// Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f,1-cy);			// Texture Coord (Top Right)
				glVertex2i(16,16);						// Vertex Coord (Top Right)
				glTexCoord2f(cx,1-cy);					// Texture Coord (Top Left)
				glVertex2i(0,16);						// Vertex Coord (Top Left)
			glEnd();									// Done Building Our Quad (Character)
			glTranslated(10,0,0);						// Move To The Right Of The Character
		glEndList();									// Done Building The Display List
	}													// Loop Until All 256 Are Built
}

GLvoid KillFont(GLvoid)									// Delete The Font From Memory
{
	glDeleteLists(base,256);							// Delete All 256 Display Lists
	glDeleteTextures( 1, &texture );
}

GLvoid PrintText(GLint x, GLint y, const char *string)		// Where The Printing Happens
{
	glEnable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Select The Type Of Blending
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,800,0,600,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glTranslated(x,y,0);								// Position The Text (0,0 - Bottom Left)
	glListBase(base);								    // Choose The Font
        glColor3f(0.6f, 0.6f, 0.6f);
	glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDisable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping
}

GLvoid PrintIndicator(float pr, GLint x, GLint y, char *string)		// Where The Printing Happens
{
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,800,0,600,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	pr = 198.0/100.0*pr;

	glDisable(GL_BLEND);

	glBegin(GL_LINE_STRIP);
		glColor3f(0.1, 0.1, 0.1);
		glVertex2f(x, y-2);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(x+200, y-2);
		glVertex2f(x+200, y+14);
		glColor3f(0.1, 0.1, 0.1);
		glVertex2f(x, y+14);
		glVertex2f(x, y-2);
	glEnd();

	//Style1
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_QUADS);
		glVertex2f(x+1, y);
		glVertex2f(x+pr, y);
		glVertex2f(x+pr, y+7);
		glVertex2f(x+1, y+7);
	glEnd();

	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_QUADS);
		glVertex2f(x+1, y+7);
		glVertex2f(x+pr, y+7);
		glVertex2f(x+pr, y+13);
		glVertex2f(x+1, y+13);
	glEnd();


/*	//Style2
	glBegin(GL_QUADS);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(x+1, y);
		glVertex2f(x+198, y);
		glColor3f(0.5, 0.5, 0.5);
		glVertex2f(x+198, y+13);
		glVertex2f(x+1, y+13);
	glEnd();
*/

	//Style3
/*
	glBegin(GL_QUADS);
		glColor3f(0.05, 0.05, 0.05);
		glVertex2f(x+1, y+2);
		glVertex2f(x+pr, y+2);
		glColor3f(0.1, 0.1, 0.1);
		glVertex2f(x+pr, y+7);
		glVertex2f(x+1, y+7);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(x+1, y+7);
		glVertex2f(x+pr, y+7);
		glColor3f(0.4, 0.4, 0.4);
		glVertex2f(x+pr, y+11);
		glVertex2f(x+1, y+11);
	glEnd();

	glBegin(GL_LINES);
		for(int i=x+1; i<x+pr; i+=3)
		{
			glColor3f(0.1, 0.1, 0.1);
			glVertex2f(i, y);
			glColor3f(0.1, 0.1, 0.1);
			glVertex2f(i, y+13);
		}
	glEnd();
*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Select The Type Of Blending

	glColor3f(0.5, 0.5, 0.5);
	glEnable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping
	glTranslated(x,y,0);								// Position The Text (0,0 - Bottom Left)

	glListBase(base);								    // Choose The Font
	glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDisable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping
}