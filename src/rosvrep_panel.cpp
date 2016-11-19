#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <time.h>
#include "hexaplus_tutorial/HexaPlusSignals.h"
#include "hexaplus_tutorial/fuzzy.h"

#include "ros/ros.h"
#include "std_msgs/Float32.h"

int main(int argc, char* argv[])
{
    unsigned long int time_delay=0;
///////////////////////////////////////////////////////////////
//
// Inicialization
//

// Initialize the ros subscribers

    ros::init(argc, argv, "rosvrep_panel");

    ros::NodeHandle n;

   // Operator setpoint Publishers 
    ros::Publisher rosAdv_gpsX_setpoint = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/gpsX_setpoint",1);
    ros::Publisher rosAdv_gpsY_setpoint = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/gpsY_setpoint",1);
    ros::Publisher rosAdv_gpsZ_setpoint = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/gpsZ_setpoint",1);

    ros::Publisher rosAdv_viewX_setpoint = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/viewX_setpoint",1);
    ros::Publisher rosAdv_viewY_setpoint = n.advertise<std_msgs::Float32>("/hexaplus_tutorial/viewY_setpoint",1);

// the rosSignal is used to send signal to uav via Publisher.
    std_msgs::Float32 rosSignal;

    float inputX, inputY, inputZ; 
    float input_view_X, input_view_Y; 
    char opt;

    system("clear");
    while (ros::ok()) {

       printf("\n==========================\n");
       printf("\nSetpoints for possition  [s]\n");
       printf("Setpoints for View heading [y]\n");
       printf("Or CTRL-C to exit.\n\n");
       printf("Enter the option: ");
       opt = getchar();
       if (opt=='s') {     

          printf("Enter X value: "); 
          scanf("%f",&inputX);
          gpsX_setpoint = inputX;

          printf("Enter Y value: "); 
          scanf("%f",&inputY);
          gpsY_setpoint = inputY;

          printf("Enter Z value: "); 
          scanf("%f",&inputZ);
          gpsZ_setpoint = inputZ;

          rosSignal.data = gpsX_setpoint; rosAdv_gpsX_setpoint.publish(rosSignal);
          rosSignal.data = gpsY_setpoint; rosAdv_gpsY_setpoint.publish(rosSignal);
          rosSignal.data = gpsZ_setpoint; rosAdv_gpsZ_setpoint.publish(rosSignal);

       } 

       if (opt=='y') {     

          printf("Enter X view value: "); 
          scanf("%f",&input_view_X);
          viewX_setpoint = input_view_X;

          printf("Enter Y view value: "); 
          scanf("%f",&input_view_Y);
          viewY_setpoint = input_view_Y;

          rosSignal.data = viewX_setpoint; rosAdv_viewX_setpoint.publish(rosSignal);
          rosSignal.data = viewY_setpoint; rosAdv_viewY_setpoint.publish(rosSignal);
       }
       ros::spinOnce();
    }  // while (ros::ok())

  return 0;
}

