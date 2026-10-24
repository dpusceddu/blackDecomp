// Unmatched: 0x1aebf8: scalar matrix hypothesis still needs original VU0 lifetime structure.
#ifdef NONMATCHING
#include "ps2/prelude.h"
typedef struct {float x,y,z,w;} BkLightingVectorPS2;
extern BkLightingVectorPS2 D_004432F0;
void func_001AEBF8(const BkLightingVectorPS2 *rotation,const signed char *coefficients,BkLightingVectorPS2 *quadratic,BkLightingVectorPS2 *cross,BkLightingVectorPS2 *linear) {
 float l[9],m[4][4],r[4][4],tmp[4][4],out[4][4];int i,j,k;
 const float c1=0.4290429949760437f,c2=0.5116640329360962f,c3=0.7431250214576721f,c4=0.886227011680603f,c5=0.24770785868167877f;
 for(i=0;i<9;i++)l[i]=(float)coefficients[i]*(1.0f/128.0f);
 m[0][0]=c1*l[8];m[0][1]=c1*l[4];m[0][2]=c1*l[7];m[0][3]=c2*l[3];
 m[1][0]=c1*l[4];m[1][1]=-c1*l[8];m[1][2]=c1*l[5];m[1][3]=c2*l[1];
 m[2][0]=c1*l[7];m[2][1]=c1*l[5];m[2][2]=c3*l[6];m[2][3]=c2*l[2];
 m[3][0]=c2*l[3];m[3][1]=c2*l[1];m[3][2]=c2*l[2];m[3][3]=c4*l[0]-c5*l[6];
 if(rotation) {
  for(i=0;i<3;i++){r[i][0]=rotation[i].x;r[i][1]=rotation[i].y;r[i][2]=rotation[i].z;r[i][3]=0.0f;}
  r[3][0]=r[3][1]=r[3][2]=0.0f;r[3][3]=1.0f;
  for(i=0;i<4;i++)for(j=0;j<4;j++){tmp[i][j]=r[i][0]*m[0][j];for(k=1;k<4;k++)tmp[i][j]+=r[i][k]*m[k][j];}
  for(i=0;i<4;i++)for(j=0;j<4;j++){out[i][j]=tmp[i][0]*r[j][0];for(k=1;k<4;k++)out[i][j]+=tmp[i][k]*r[j][k];}
  for(i=0;i<4;i++)for(j=0;j<4;j++)m[i][j]=out[i][j];
 }
 quadratic->x=m[0][0]-m[2][2];quadratic->y=m[1][1]-m[2][2];quadratic->z=m[0][1]+m[1][0];quadratic->w=D_004432F0.w;
 cross->x=m[0][2]+m[2][0];cross->y=m[1][2]+m[2][1];cross->z=m[2][2]+m[3][3];cross->w=D_004432F0.w;
 linear->x=m[0][3]+m[3][0];linear->y=m[1][3]+m[3][1];linear->z=m[2][3]+m[3][2];linear->w=D_004432F0.w;
}

#endif
