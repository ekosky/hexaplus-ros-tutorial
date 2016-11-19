#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hexaplus_tutorial/navigation.h"

int multiplyMatrix(int rf ,int cf ,float mf[] ,int rs ,int cs ,float ms[] ,float mout[]) {
  float sum=0;
  int p,q,c,d,k=0;

  if (cf != rs) {
     printf ("Matrices cat't be multiplied with each other.\n");
     mout = NULL;
     return -1;
  }

  for (c = 0; c < rf; c++) {
    for (d = 0; d < cs; d++) {
      for (k = 0; k < rs; k++) {
          sum  += (float) (mf[(c*cf)+k] * ms[k*cs+d]);
      }
        mout[d*cf+c] = sum;
        sum = 0;
    }
  }
 
  return 0;
}

int Rz(float angle_rad,float mz[3][3])  {
    mz[0][0] = (float) cos(angle_rad);
    mz[0][1] = (float) -sin(angle_rad);
    mz[0][2] = 0;
    mz[1][0] = (float) sin(angle_rad);
    mz[1][1] = (float) cos(angle_rad);
    mz[1][2] = 0;
    mz[2][0] = 0;
    mz[2][1] = 0;
    mz[2][2] = 1;
}

int Ry(float angle_rad,float my[3][3])  {
    my[0][0] = (float) cos(angle_rad);
    my[0][1] = 0;
    my[0][2] = (float) sin(angle_rad);
    my[1][0] = 0;
    my[1][1] = 1;
    my[1][2] = 0;
    my[2][0] = (float) -sin(angle_rad);
    my[2][1] = 0;
    my[2][2] = (float) cos(angle_rad);
}

int Rx(float angle_rad,float mx[3][3])  {
    mx[0][0] = 1;  
    mx[0][1] = 0;
    mx[0][2] = 0; 
    mx[1][0] = 0;
    mx[1][1] = (float) cos(angle_rad);
    mx[1][2] = (float) -sin(angle_rad);
    mx[2][0] = 0;
    mx[2][1] = (float)  sin(angle_rad);
    mx[2][2] = (float)  cos(angle_rad);
}
void printMatrix(int r, int c, float *m) {
    int i,j,k;
    printf("\n");
    for (i=0;i<r;i++) {
        for (j=0;j<c;j++) printf(" %f[%d][%d] ",m[i*r+j],i,j);
        printf("\n");
    }    
    printf("\n");
}
void ret2polar(ret_tp *ret, polar_tp *polar) {
     polar->dist = (float) pow(( ret->x * ret->x) + (ret->y * ret->y), 0.5);
     polar->angle = (float) atan2(ret->y,ret->x);
} 

int translationXYZ(float aXYZ[3], float dinXYZ[3], float doutXYZ[3]) {

    float mZ[3][3];  
    float mX[3][3];  
    float mY[3][3];  
    float tmp1[3][3];  
    float tmp2[3][3];  

    Rx(aXYZ[0],mX);
    Ry(-aXYZ[1],mY);
    Rz(-aXYZ[2],mZ);

    multiplyMatrix(3,3, (float *) mX, 3,3, (float *) mY, (float *) tmp1);
    multiplyMatrix(3,3, (float *) tmp1, 3,3, (float *) mZ, (float *) tmp2);
    multiplyMatrix(3,3, (float *) tmp2, 3,1, (float *) dinXYZ, (float *) doutXYZ);

}
/////////////////////////////////////////////////////////////////////////
//
// main function for teste
//

int main_translationXYZ(int argc, char *argv[]) {
    float aXYZ[3], dinXYZ[3], doutXYZ[3]; 

    if (argc < 6) {
       printf (" Enter angle:  X Y Z Distance: X Y Z\n\n");
       return 2;
    }

    aXYZ[0] = atof(argv[1]) * M_PI/180;
    aXYZ[1] = atof(argv[2]) * M_PI/180;
    aXYZ[2] = atof(argv[3]) * M_PI/180;

    dinXYZ[0] = atof(argv[4]);
    dinXYZ[1] = atof(argv[5]);
    dinXYZ[2] = atof(argv[6]);

    translationXYZ(aXYZ, dinXYZ, doutXYZ);
    printf("Dist. Out: X Y Z: %f %f %f \n", doutXYZ[0], doutXYZ[1], doutXYZ[2]);
}

// main for tests
int main_multiplyMatrix (int argc, char *argv[]) {
    float aX, aY, aZ;
    float mZ[3][3];  
    float mX[3][3];  
    float mY[3][3];  
    float tmp1[3][3];  
    float tmp2[3][3];  
    float din[3];  
    float dout[3];  

    if (argc < 6) {
       printf (" Enter angle:  X Y Z Distance: X Y Z\n\n");
       return 2;
    }
   
    aX = atof(argv[1]) * M_PI/180;
    aY = -atof(argv[2]) * M_PI/180;
    aZ = -atof(argv[3]) * M_PI/180;
    printf("%f, %f, %f\n",aX,aY,aZ);

    din[0] = atof(argv[4]);
    din[1] = atof(argv[5]);
    din[2] = atof(argv[6]);

    Rx(aX,mX);
    Ry(aY,mY);
    Rz(aZ,mZ);

    printMatrix(3,3,(float *) mZ);
    printMatrix(3,3,(float *) mX);
    printMatrix(3,3,(float *) mY);

    multiplyMatrix(3,3, (float *) mX, 3,3, (float *) mY, (float *) tmp1);
    multiplyMatrix(3,3, (float *) tmp1, 3,3, (float *) mZ, (float *) tmp2);

    multiplyMatrix(3,3, (float *) tmp2, 3,1, (float *) din, (float *) dout);
    printf("Dist. In.: X Y Z: %f %f %f \n", din[0], din[1], din[2]);
    printf("Dist. Out: X Y Z: %f %f %f \n", dout[0], dout[1], dout[2]);
}
int main_ret2polar (int argc, char *argv[]) {

    ret_tp   r;
    polar_tp p;
    if (argc < 3) {
       printf (" Entre com X, Y \n\n");
       return 2;
    }

    r.x=atof(argv[1]);
    r.y=atof(argv[2]);

   ret2polar(&r,&p);
   printf ("Polar...: %f (%f degree)\n",p.dist,p.angle* 180/M_PI);

}


