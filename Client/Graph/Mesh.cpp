#include "Mesh.h"

#define FindStr(str, fHandle) { do fgets(szString, 128, fHandle); while((strncmp(str, szString, sizeof(str)-1))&&(!feof(fHandle)));}
#define NextStr(fHandle) {fgets(szString, 128, fHandle);}

TMesh::TMesh()
{
}

TMesh::~TMesh()
{
	glDeleteLists(list_num, 1);
}

int TMesh::LoadModel(char *filename)
{
	FILE *fModel;
	char szString[128];

	unsigned int i, j;

	float *vx,*vy,*vz;	// Coords of vertices
	float	*nx,*ny,*nz;	// Face normals coords

	fModel=fopen( filename , "rb" );
	if(!fModel) return GL_MODEL_NOSUCHFILE;

	FindStr( "Mesh", fModel );
	NextStr( fModel );

	sscanf( szString, " %d", &Vertices );

	vx=new float[Vertices];
	vy=new float[Vertices];
	vz=new float[Vertices];

float maxX=0,maxY=0,maxZ=0;// dyf
float minX=0,minY=0,minZ=0;// dyf
float maximum=0;
	for( i = 0; i < Vertices; i++)
	{
		NextStr(fModel);
		sscanf(szString, "%f;%f;%f", &(vx[i]),&(vy[i]),&(vz[i]));
// dyf
		if (vx[i]>maxX) maxX=vx[i];
		if (vy[i]>maxY) maxY=vy[i];
		if (vz[i]>maxZ) maxZ=vz[i];

		if (vx[i]<minX) minX=vx[i];
		if (vy[i]<minY) minY=vy[i];
		if (vz[i]<minZ) minZ=vz[i];
	}
if (maximum<fabsf(maxX)) maximum = fabsf(maxX);
if (maximum<fabsf(maxY)) maximum = fabsf(maxY);
if (maximum<fabsf(maxZ)) maximum = fabsf(maxZ);

if (maximum<fabsf(minX)) maximum = fabsf(minX);
if (maximum<fabsf(minY)) maximum = fabsf(minY);
if (maximum<fabsf(minZ)) maximum = fabsf(minZ);
	// читаем индексы из файла
	NextStr(fModel);
	NextStr(fModel);
	sscanf(szString, " %d", &NumIndex);

	unsigned int in[10000][21]; // максимум 10000 граней
	
	for( i=0; i<NumIndex; i++)
	{
		NextStr(fModel);
		// максимум 20 индексов на грань
		sscanf(szString, "%d;%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &(in[i][0]), &(in[i][1]), &(in[i][2]), &(in[i][3]), &(in[i][4]), &(in[i][5]), &(in[i][6]), &(in[i][7]), &(in[i][8]), &(in[i][9]), &(in[i][10]), &(in[i][11]), &(in[i][12]), &(in[i][13]), &(in[i][14]), &(in[i][15]), &(in[i][16]), &(in[i][17]), &(in[i][18]), &(in[i][19]), &(in[i][20])); 
	}

	// тоже самое по нормалям
	nx=new float[Vertices];
	ny=new float[Vertices];
	nz=new float[Vertices];

	FindStr( " MeshNormals", fModel );
	NextStr( fModel );

	for( i = 0; i < Vertices; i++)
	{
		NextStr(fModel);
		sscanf(szString, "%f;%f;%f", &(nx[i]),&(ny[i]),&(nz[i]));
	}

	// создаем лист
	list_num = glGenLists(1);
	
	glNewList( list_num, GL_COMPILE );
	
	glColor3f(0.02, 0.02, 0.06);
	glPolygonMode(GL_FRONT, GL_FILL);
	glCullFace(GL_BACK);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 3.0);

	glDisable(GL_BLEND);

	for( i=0; i<NumIndex; i++)
	{
		glBegin(GL_POLYGON);
		for( j=1; j <= in[i][0]; j++)
		{
			glNormal3f(nx[in[i][j]],ny[in[i][j]],nz[in[i][j]]);
//			glVertex3f(vx[in[i][j]]/50.0,vy[in[i][j]]/50.0,vz[in[i][j]]/50.0);
			glVertex3f(vx[in[i][j]]/maximum,vy[in[i][j]]/maximum,vz[in[i][j]]/maximum);//dyf
		}
		glEnd();
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glDisable(GL_POLYGON_OFFSET_FILL);

	glColor3f(0.2, 0.2, 0.6);
	
	glPolygonMode(GL_FRONT, GL_LINE);
	glCullFace(GL_BACK);

	for( i=0; i<NumIndex; i++)
	{
		glBegin(GL_POLYGON);
		for( j=1; j <= in[i][0]; j++)
		{
			glNormal3f(nx[in[i][j]],ny[in[i][j]],nz[in[i][j]]);
//			glVertex3f(vx[in[i][j]]/50.0,vy[in[i][j]]/50.0,vz[in[i][j]]/50.0);
			glVertex3f(vx[in[i][j]]/maximum,vy[in[i][j]]/maximum,vz[in[i][j]]/maximum);//dyf
		}
		glEnd();
	}
	
	glDisable(GL_LINE_SMOOTH);
	glPolygonMode(GL_FRONT, GL_FILL);

	glEndList();

	delete(vx); delete(vy); delete(vz);
	delete(nx); delete(ny); delete(nz);

	return GL_MODEL_OK;
}


void TMesh::Render()
{
	/*
	glPushMatrix();

	float Mat[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f};

    glMultMatrixf(Mat);
	*/
	glCallList(list_num);

	//glPopMatrix();

}
