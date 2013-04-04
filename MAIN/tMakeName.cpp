#include "tMakeName.h" 
#include <stdlib.h>
extern char space_name[65];

void tMakeName::GenerateName(char* n){
	int t_pos=0;
	for(int st=0,c_pos=0;st<4;st++){
		c_pos=(32*(float)(rand())/RAND_MAX);
		if ((st==3)&&(c_pos>10)) break;
		c_pos*=2;
		*(n+t_pos)=space_name[c_pos];
		t_pos++;
		if (space_name[c_pos+1]==63) continue;
		*(n+t_pos)=space_name[c_pos+1];
		t_pos++;
	}
	*(n+t_pos)=0;
}
void tMakeName::GenerateName(char* tmpBuf,float u){
	srand(u);
	this->GenerateName(tmpBuf);
}
