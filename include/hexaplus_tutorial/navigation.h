#ifndef _NAVIGATION
#define _NAVIGATION

typedef struct rettp {
   float x,y;
} ret_tp;
typedef struct polartp {
   float dist, angle; 
} polar_tp;

int multiplyMatrix(int rf ,int cf ,float mf[] ,int rs ,int cs ,float ms[] ,float mout[]);

int Rx(float angle_rad,float mx[3][3]);
int Ry(float angle_rad,float my[3][3]);
int Rz(float angle_rad,float mz[3][3]);

int translationXYZ(float aXYZ[3], float dinXYZ[3], float doutXYZ[3]);

void ret2polar(ret_tp *ret, polar_tp *polar) ;

#endif

