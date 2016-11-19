#ifndef _HEXAPLUSSIGNAL_
#define _HEXAPLUSSIGNAL_
#include <hexaplus_tutorial/navigation.h>
ret_tp ret;
polar_tp polar;

 float aXYZ[3], dinXYZ[3], doutXYZ[3];

 struct timeval ini_t,end_t;

 double iniX,iniY,iniZ;
 double endX,endY,endZ;
 double dX,dY,dZ;
 double dt;
 double speed_gpsX,speed_gpsY,speed_gpsZ; // Meters/sec
 double speed_uavX,speed_uavY,speed_uavZ; // Meters/sec

// Euler angle signal
 float eulerX;
 float eulerY;
 float eulerZ;

// GPS signal
 float gpsX;
 float gpsY;
 float gpsZ;

// Accelerometer signal
 float accelX;
 float accelY;
 float accelZ;

 float gpsX_setpoint;
 float gpsY_setpoint;
 float gpsZ_setpoint;

 float roll_setpoint; 
 float pitch_setpoint; 
 float yaw_setpoint; 
 float viewX_setpoint;
 float viewY_setpoint;

 float uav_goal_angle;
 float uav_goal_dist;

 float pitch_error; 
 float roll_error;     
 float yaw_error;  
 float viewX_error; 
 float viewY_error;
 float yaw_view_dist;
 float drift_angle;  

 float gpsX_error;
 float gpsY_error;
 float gpsZ_error;

 float uavX_error;
 float uavY_error;
 float uavZ_error;
 float speed_goal;

// Output signals
 float propForceFRONT       ;
 float propForceRIGHT_FRONT ;
 float propForceRIGHT_REAR  ;
 float propForceREAR        ;
 float propForceLEFT_REAR   ;
 float propForceLEFT_FRONT  ;

// Omega variables: Hovering, Throttle, roll, pitch and yaw
 float Othrottle;
 float Oroll;
 float Opitch;
 float Opitch_nav;
 float Oyaw;

double diffclock(struct timeval end_t, struct timeval ini_t) {
    return ((end_t.tv_sec - ini_t.tv_sec)*1000000L
           + end_t.tv_usec) - ini_t.tv_usec;
}
#endif 

