#include "ros/ros.h"
#include "ros/package.h"
#include "std_msgs/Float32.h"
#include "std_msgs/String.h"
#include "hexaplus_tutorial/HexaPlus.h"

// file: rosvrep_controller.cpp 
// Description: 
//     The main controller.
//     This programm basically represent the plant, the hexacopter
//     It does a) read the sensors data
//             b) execute pre-process to trasform the data as needed
//             c) process de fuzzing logic, and
//             d) apply result to the actuators at plant, the rotors
//             e) Finally, send some telemtry data 

/////////////   THE CALLBACK FUNCTION ///////////////////////////////
//
// Subscriber callback functions for euler angles
void callback_eulerX(const std_msgs::Float32 f) { eulerX = f.data; }
void callback_eulerY(const std_msgs::Float32 f) { eulerY = f.data; }
void callback_eulerZ(const std_msgs::Float32 f) { eulerZ = f.data; }

// Subscriber callback functions for GPS position 
void callback_gpsX(const std_msgs::Float32 f) { gpsX = f.data; }
void callback_gpsY(const std_msgs::Float32 f) { gpsY = f.data; }
void callback_gpsZ(const std_msgs::Float32 f) { gpsZ = f.data; }

// Subscriber callback functions for acceleroter sensor 
void callback_accelX(const std_msgs::Float32 f) { accelX = f.data; }
void callback_accelY(const std_msgs::Float32 f) { accelY = f.data; }
void callback_accelZ(const std_msgs::Float32 f) { accelZ = f.data; }

// Subscriber callback functions for operator setpoints
void callback_gpsX_setpoint(const std_msgs::Float32 f) {gpsX_setpoint = f.data;}
void callback_gpsY_setpoint(const std_msgs::Float32 f) {gpsY_setpoint = f.data;}
void callback_gpsZ_setpoint(const std_msgs::Float32 f) {gpsZ_setpoint = f.data;}

void callback_viewX_setpoint(const std_msgs::Float32 f) {viewX_setpoint = f.data;}
void callback_viewY_setpoint(const std_msgs::Float32 f) {viewY_setpoint = f.data;}
//
/////////////  END CALLBACK FUNCTION ///////////////////////////////

int main(int argc, char* argv[])
{ 
    unsigned long int time_delay=0;
///////////////////////////////////////////////////////////////
//
// Inicialization
//

// Initialize the ros subscribers

   ros::init(argc, argv, "rosvrep_controller");

   ros::NodeHandle n;

// the rosSignal is used to send signal to uav via Publisher.
   std_msgs::Float32 rosSignal;

   // Hexacopter sensor subscribers
   ros::Subscriber sub_eulerX = n.subscribe("/vrep/eulerX",1, callback_eulerX);
   ros::Subscriber sub_eulerY = n.subscribe("/vrep/eulerY",1, callback_eulerY);
   ros::Subscriber sub_eulerZ = n.subscribe("/vrep/eulerZ",1, callback_eulerZ);

   ros::Subscriber sub_gpsX = n.subscribe("/vrep/gpsX",1, callback_gpsX);
   ros::Subscriber sub_gpsY = n.subscribe("/vrep/gpsY",1, callback_gpsY);
   ros::Subscriber sub_gpsZ = n.subscribe("/vrep/gpsZ",1, callback_gpsZ);

   ros::Subscriber sub_accelX = n.subscribe("/vrep/accelX",1, callback_accelX);
   ros::Subscriber sub_accelY = n.subscribe("/vrep/accelY",1, callback_accelY);
   ros::Subscriber sub_accelZ = n.subscribe("/vrep/accelZ",1, callback_accelZ);
 
   ros::Subscriber sub_gpsX_setpoint = n.subscribe("/hexaplus_tutorial/gpsX_setpoint",1, callback_gpsX_setpoint);
   ros::Subscriber sub_gpsY_setpoint = n.subscribe("/hexaplus_tutorial/gpsY_setpoint",1, callback_gpsY_setpoint);
   ros::Subscriber sub_gpsZ_setpoint = n.subscribe("/hexaplus_tutorial/gpsZ_setpoint",1, callback_gpsZ_setpoint);

   ros::Subscriber sub_viewX_setpoint = n.subscribe("/hexaplus_tutorial/viewX_setpoint",1, callback_viewX_setpoint);
   ros::Subscriber sub_viewY_setpoint = n.subscribe("/hexaplus_tutorial/viewY_setpoint",1, callback_viewY_setpoint);

// Initialize the ros Publishers
   // Rotors publishers
   ros::Publisher rosAdv_propFRONT       = n.advertise<std_msgs::Float32>("/vrep/propFRONT",1);
   ros::Publisher rosAdv_propLEFT_FRONT  = n.advertise<std_msgs::Float32>("/vrep/propLEFT_FRONT",1);
   ros::Publisher rosAdv_propLEFT_REAR   = n.advertise<std_msgs::Float32>("/vrep/propLEFT_REAR",1);
   ros::Publisher rosAdv_propREAR        = n.advertise<std_msgs::Float32>("/vrep/propREAR",1);
   ros::Publisher rosAdv_propRIGHT_FRONT = n.advertise<std_msgs::Float32>("/vrep/propRIGHT_FRONT",1);
   ros::Publisher rosAdv_propRIGHT_REAR  = n.advertise<std_msgs::Float32>("/vrep/propRIGHT_REAR",1);
   ros::Publisher rosAdv_propYaw         = n.advertise<std_msgs::Float32>("/vrep/Yaw",1);

   // Telemetry 
   ros::Publisher rosAdv_gpsX_error      = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/gpsX_error",1);
   ros::Publisher rosAdv_gpsY_error      = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/gpsY_error",1);
   ros::Publisher rosAdv_gpsZ_error      = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/gpsZ_error",1);

   ros::Publisher rosAdv_drift_angle     = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/drift_angle",1);
   ros::Publisher rosAdv_uav_goal_angle  = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/uav_goal_angle",1);
   ros::Publisher rosAdv_uav_goal_dist   = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/uav_goal_dist",1);
   ros::Publisher rosAdv_speed_uavZ      = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/speed_uavZ",1);
   ros::Publisher rosAdv_speed_goal      = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/speed_goal",1);

//  
// Initialize all variables of sensors and rotors 
    HexaPlus hexaplus;

    // Spin once to get the first single values from ROS
    // just to calibrate setpoints and
    // set the rotors to zero

    rosSignal.data = 0;
    rosAdv_propFRONT.publish(rosSignal); 
    rosAdv_propRIGHT_FRONT.publish(rosSignal); 
    rosAdv_propRIGHT_REAR.publish(rosSignal); 
    rosAdv_propREAR.publish(rosSignal); 
    rosAdv_propLEFT_REAR.publish(rosSignal); 
    rosAdv_propLEFT_FRONT.publish(rosSignal); 
    rosAdv_propYaw.publish(rosSignal); 

    ros::spinOnce();

    gettimeofday(&ini_t,NULL);
    gpsX_setpoint  = gpsX;
    gpsY_setpoint  = gpsY;
    gpsZ_setpoint  = 0;
    yaw_setpoint   = eulerZ;
    viewX_setpoint = 0;
    viewY_setpoint = 0;

    roll_setpoint  = 0;
    pitch_setpoint = 0;
///////////////////////////////////////////////////////////////
//
// Main Control Loop
//
    ros::Rate loop_rate(10);
    while (ros::ok())
    {

       // Calculate the delta time and speed
        if(time_delay >= 10000) {

          endX = gpsX;
          endY = gpsY;
          endZ = gpsZ;

          gettimeofday(&end_t,NULL);
          dt = diffclock(end_t,ini_t);

          dX = (double) endX - iniX;
          dY = (double) endY - iniY;
          dZ = (double) endZ - iniZ;

          // Speedup calculation

          speed_gpsX = (double) (dX/dt) * 1000000L; 
          speed_gpsY = (double) (dY/dt) * 1000000L; 
          speed_gpsZ = (double) (dZ/dt) * 1000000L; 

          iniX  = endX;
          iniZ  = endZ;
          iniY  = endY;
          ini_t = end_t;
          time_delay=0;
        }
        time_delay++;

       // Determine the delta as errors. 
       // It means the diference between setpoint and current information
  
        // GPS error
        gpsX_error  = (float) gpsX_setpoint - gpsX;
        gpsY_error  = (float) gpsY_setpoint - gpsY;
        gpsZ_error  = (float) gpsZ_setpoint - gpsZ;

        // View possition error (yaw or heading of the hexacopter)
        viewX_error  = (float) viewX_setpoint - gpsX;
        viewY_error  = (float) viewY_setpoint - gpsY;

        // Calculate the drift_angle
        // This angle is the difference between direction to navigate and direction of view (yaw).
        drift_angle = (float) eulerZ - uav_goal_angle;

        // Calculate the yaw_error 
        // This angle is the difference between setpoint sent by operator and actual direction of view (yaw).
        yaw_error   = (float) eulerZ - yaw_setpoint;
        if (yaw_error >= M_PI)
           yaw_error = M_PI*2 - yaw_error;
        if (yaw_error <= -M_PI)
           yaw_error = -M_PI*2 + yaw_error;

        // Calculate the proportional amount to be consider to slop pitch and roll 
        // as the hexacoper goes to the correct direction
        pitch_setpoint = (float) Opitch_nav*cos(drift_angle);
        roll_setpoint  = (float) Opitch_nav*sin(drift_angle);

        pitch_error = (float) eulerY - pitch_setpoint;
        roll_error  = (float) eulerX - roll_setpoint;

// transform view XY (retangular) to |Z| angle (polar)
        ret.x = viewX_error;
        ret.y = viewY_error;
        ret2polar(&ret, &polar);
        yaw_setpoint  = polar.angle;
        yaw_view_dist = polar.dist;

        aXYZ[0]=0;
        aXYZ[1]=0;
        aXYZ[2]=eulerZ;

        dinXYZ[0]=gpsX_error;
        dinXYZ[1]=gpsY_error;
        dinXYZ[2]=0; 

        translationXYZ(aXYZ, dinXYZ, doutXYZ);
        uavX_error = doutXYZ[0];
        uavY_error = doutXYZ[1];

        uavZ_error = gpsZ_error;
        
        dinXYZ[0]=speed_gpsX;
        dinXYZ[1]=speed_gpsY;
        dinXYZ[2]=0;
        translationXYZ(aXYZ, dinXYZ, doutXYZ);
        speed_uavX = doutXYZ[0];
        speed_uavY = doutXYZ[1];

        speed_uavZ = (float) abs(speed_gpsZ*100000L)/100000L; 

        ret.x = gpsX_error;
        ret.y = gpsY_error;
        ret2polar(&ret, &polar);
        uav_goal_angle  = polar.angle;
        uav_goal_dist   = polar.dist;

        ret.x = speed_uavX;
        ret.y = speed_uavY;
        ret2polar(&ret, &polar);

//ignored = polar.angle; Must be the same of yaw_setpoint
        speed_goal = polar.dist;

        hexaplus.fz_uavZ_error->value = uavZ_error;
        hexaplus.fz_speed_uavZ->value = speed_uavZ;

        hexaplus.fz_accelX->value = accelX;
        hexaplus.fz_accelY->value = accelY;

        hexaplus.fz_yaw_error->value          = yaw_error; 
        hexaplus.fz_yaw_uav_goal_dist->value  = uav_goal_dist;
        hexaplus.fz_roll_error->value         = roll_error;
        hexaplus.fz_pitch_error->value        = pitch_error;

        hexaplus.fz_hnav_uav_goal_dist->value = uav_goal_dist;
        hexaplus.fz_hnav_speed_goal->value    = speed_goal;

// fuzzifying ...

        hexaplus.fS_stabX->fuzzifying();
        hexaplus.fS_stabY->fuzzifying();
        hexaplus.fS_stabZ->fuzzifying();
        hexaplus.fS_yaw->fuzzifying();
        hexaplus.fS_hnav->fuzzifying();

// finished fuzzifying, apply the outputs

        Opitch         = hexaplus.fz_Opitch->value;
        Oroll          = hexaplus.fz_Oroll->value;
        Othrottle      = hexaplus.fz_Othrottle->value; 
        Oyaw           = hexaplus.fz_Oyaw->value;
        Opitch_nav     = hexaplus.fz_Opitch_nav->value; 

        ret.x = Opitch;
        ret.y = Oroll;
        ret2polar(&ret, &polar);
        float angleOth = polar.angle;
        float zOth     = polar.dist;

        propForceFRONT       = (float) Othrottle - 0.45*zOth*cos(angleOth);
        propForceRIGHT_FRONT = (float) Othrottle - (0.45*zOth*(sin(angleOth) /1.1547 ));
        propForceRIGHT_REAR  = (float) Othrottle - (0.45*zOth*(sin(angleOth) /1.1547 ));
        propForceREAR        = (float) Othrottle + 0.45*zOth*cos(angleOth);
        propForceLEFT_REAR   = (float) Othrottle + (0.45*zOth*(sin(angleOth) /1.1547 ));
        propForceLEFT_FRONT  = (float) Othrottle + (0.45*zOth*(sin(angleOth) /1.1547 ));


// Send signals to the rotors 

        rosSignal.data = propForceFRONT;       rosAdv_propFRONT.publish(rosSignal); 
        rosSignal.data = propForceRIGHT_FRONT; rosAdv_propRIGHT_FRONT.publish(rosSignal); 
        rosSignal.data = propForceRIGHT_REAR;  rosAdv_propRIGHT_REAR.publish(rosSignal); 
        rosSignal.data = propForceREAR;        rosAdv_propREAR.publish(rosSignal); 
        rosSignal.data = propForceLEFT_REAR;   rosAdv_propLEFT_REAR.publish(rosSignal); 
        rosSignal.data = propForceLEFT_FRONT;  rosAdv_propLEFT_FRONT.publish(rosSignal); 
        rosSignal.data = Oyaw;                 rosAdv_propYaw.publish(rosSignal); 

// Send additional telemetry signals

        rosSignal.data = gpsX_error;          rosAdv_gpsX_error.publish(rosSignal); 
        rosSignal.data = gpsY_error;          rosAdv_gpsY_error.publish(rosSignal); 
        rosSignal.data = gpsZ_error;          rosAdv_gpsZ_error.publish(rosSignal); 

        rosSignal.data = drift_angle;          rosAdv_drift_angle.publish(rosSignal); 
        rosSignal.data = uav_goal_angle;       rosAdv_uav_goal_angle.publish(rosSignal); 
        rosSignal.data = uav_goal_dist;        rosAdv_uav_goal_dist.publish(rosSignal); 
        rosSignal.data = speed_uavZ;           rosAdv_speed_uavZ.publish(rosSignal); 
        rosSignal.data = speed_goal;           rosAdv_speed_goal.publish(rosSignal); 

// Finally, interact with the hexacoper and dashboard telemetry (rosvpre_telemetry) 
// receiving and sending signal to/from the sensors and rotors respectively by ros:: spinOnce();

        loop_rate.sleep();
        ros::spinOnce();

    } // end while (ros::ok())

    return 0;
}

