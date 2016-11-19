#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <time.h>
#include "hexaplus_tutorial/HexaPlusSignals.h"
#include "hexaplus_tutorial/fuzzy.h"

#include "ros/ros.h"
#include "std_msgs/Float32.h"

void callback_gpsX(const std_msgs::Float32 f) { gpsX = f.data; }
void callback_gpsY(const std_msgs::Float32 f) { gpsY = f.data; }
void callback_gpsZ(const std_msgs::Float32 f) { gpsZ = f.data; }

void callback_gpsX_error(const std_msgs::Float32 f) { gpsX_error = f.data; }
void callback_gpsY_error(const std_msgs::Float32 f) { gpsY_error = f.data; }
void callback_gpsZ_error(const std_msgs::Float32 f) { gpsZ_error = f.data; }

void callback_drift_angle(const std_msgs::Float32 f)    { drift_angle = f.data; }
void callback_uav_goal_angle(const std_msgs::Float32 f) { uav_goal_angle = f.data; }
void callback_uav_goal_dist(const std_msgs::Float32 f)  { uav_goal_dist = f.data; }
void callback_speed_uavZ(const std_msgs::Float32 f)     { speed_uavZ = f.data; }
void callback_speed_goal(const std_msgs::Float32 f)     { speed_goal = f.data; }

// Subscriber callback functions for operator setpoints
void callback_gpsX_setpoint(const std_msgs::Float32 f) {gpsX_setpoint = f.data;}
void callback_gpsY_setpoint(const std_msgs::Float32 f) {gpsY_setpoint = f.data;}
void callback_gpsZ_setpoint(const std_msgs::Float32 f) {gpsZ_setpoint = f.data;}

void callback_viewX_setpoint(const std_msgs::Float32 f) {viewX_setpoint = f.data;}
void callback_viewY_setpoint(const std_msgs::Float32 f) {viewY_setpoint = f.data;}


int main(int argc, char* argv[])
{
    unsigned long int time_delay=0;
///////////////////////////////////////////////////////////////
//
// Inicialization
//

// Initialize the ros subscribers

    ros::init(argc, argv, "rosvrep_telemetry");

    ros::NodeHandle n;

   // Telemetry
    ros::Subscriber sub_gpsX = n.subscribe("/vrep/gpsX",1, callback_gpsX);
    ros::Subscriber sub_gpsY = n.subscribe("/vrep/gpsY",1, callback_gpsY);
    ros::Subscriber sub_gpsZ = n.subscribe("/vrep/gpsZ",1, callback_gpsZ);

    ros::Subscriber sub_gpsX_error = n.subscribe("/hexaplus_tutorial/gpsX_error",1, callback_gpsX_error);
    ros::Subscriber sub_gpsY_error = n.subscribe("/hexaplus_tutorial/gpsY_error",1, callback_gpsY_error);
    ros::Subscriber sub_gpsZ_error = n.subscribe("/hexaplus_tutorial/gpsZ_error",1, callback_gpsZ_error);

    ros::Subscriber sub_drift_angel    = n.subscribe("/hexaplus_tutorial/drift_angle",1, callback_drift_angle);
    ros::Subscriber sub_uav_goal_angle = n.subscribe("/hexaplus_tutorial/uav_goal_angle",1, callback_uav_goal_angle);
    ros::Subscriber sub_uav_goal_dist  = n.subscribe("/hexaplus_tutorial/uav_goal_dist",1, callback_uav_goal_dist);
    ros::Subscriber sub_speed_uavZ     = n.subscribe("/hexaplus_tutorial/speed_uavZ",1, callback_speed_uavZ);
    ros::Subscriber sub_speed_goal     = n.subscribe("/hexaplus_tutorial/speed_goal",1, callback_speed_goal);

    // Operator setpoint subscribers
    ros::Subscriber sub_gpsX_setpoint = n.subscribe("/hexaplus_tutorial/gpsX_setpoint",1, callback_gpsX_setpoint);
    ros::Subscriber sub_gpsY_setpoint = n.subscribe("/hexaplus_tutorial/gpsY_setpoint",1, callback_gpsY_setpoint);
    ros::Subscriber sub_gpsZ_setpoint = n.subscribe("/hexaplus_tutorial/gpsZ_setpoint",1, callback_gpsZ_setpoint);

    ros::Subscriber sub_viewX_setpoint = n.subscribe("/hexaplus_tutorial/viewX_setpoint",1, callback_viewX_setpoint);
    ros::Subscriber sub_viewY_setpoint = n.subscribe("/hexaplus_tutorial/viewY_setpoint",1, callback_viewY_setpoint);

// the rosSignal is used to send signal to uav via Publisher.
    std_msgs::Float32 rosSignal;

    system("clear");
    ros::Rate loop_rate(1);
    while (ros::ok()) {

       printf("------------------- Telemetry ------------------------------\n");
       printf("gpsX ..................................: %f\n",gpsX);
       printf("gpsY ..................................: %f\n",gpsY);
       printf("gpsZ ..................................: %f\n",gpsZ);
       printf("gpsX_error ............................: %f\n",gpsX_error);
       printf("gpsY_error ............................: %f\n",gpsY_error);
       printf("gpsZ_error ............................: %f\n",gpsZ_error);
       printf("drift_angle ...........................: %f (%f degrees)\n",drift_angle,drift_angle * 57.29);
       printf("uav_goal_angle ........................: %f (%f degrees)\n",uav_goal_angle,uav_goal_angle * 57.29);
       printf("uav_goal_dist .........................: %f\n",uav_goal_dist);
       printf("speed_uavZ ............................: %f\n",speed_uavZ);
       printf("speed_goal ............................: %f\n",speed_goal);
       printf("---------------- Operator Command -------------------------\n");
       printf("gpsX_setpoint .........................: %f\n",gpsX_setpoint);
       printf("gpsY_setpoint .........................: %f\n",gpsY_setpoint);
       printf("gpsZ_setpoint .........................: %f\n\n",gpsZ_setpoint);

       printf("viewX_setpoint ........................: %f\n",viewX_setpoint);
       printf("viewY_setpoint ........................: %f\n",viewY_setpoint);
       printf("-----------------------------------------------------------\n");
       printf("Press CTRL-C to exit\n");
       loop_rate.sleep();
       ros::spinOnce();
       system("clear");
    }  // while (ros::ok())

  return 0;
}

