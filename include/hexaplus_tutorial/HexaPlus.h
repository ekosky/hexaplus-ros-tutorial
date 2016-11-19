#ifndef _HEXAPLUS_
#define _HEXAPLUS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <cstdlib>
#include <math.h>
#include <time.h>

#include "fuzzy/Fuzzy.h"
#include "navigation.h"
#include "HexaPlusSignals.h"

#define MAX_TIME_DELAY  100000L
#define PI_2           M_PI*2; 


class HexaPlus {
    public:
      HexaPlus() 
      {
         fS_stabX = new fuzzy::FuzzySet("StabX");
         fS_stabY = new fuzzy::FuzzySet("StabY");
         fS_stabZ = new fuzzy::FuzzySet("StabZ");
         fS_yaw   = new fuzzy::FuzzySet("Yaw");
         fS_hnav  = new fuzzy::FuzzySet("Hnav");
         initHexaPlus();
      };

      virtual ~HexaPlus() {};

      fuzzy::FuzzySet* fS_stabX;
      fuzzy::FuzzySet* fS_stabY;
      fuzzy::FuzzySet* fS_stabZ;
      fuzzy::FuzzySet* fS_yaw;
      fuzzy::FuzzySet* fS_hnav;
      
      fuzzy::Linguistic *fz_i_stabX;
      fuzzy::Linguistic *fz_i_stabY;
      fuzzy::Linguistic *fz_i_stabZ;

      fuzzy::Linguistic *fz_o_stabX;
      fuzzy::Linguistic *fz_o_stabY;
      fuzzy::Linguistic *fz_o_stabZ;

      fuzzy::Linguistic *fz_uavX_error;
      fuzzy::Linguistic *fz_uavY_error;
      fuzzy::Linguistic *fz_uavZ_error;

      fuzzy::Linguistic *fz_speed_uavX;
      fuzzy::Linguistic *fz_speed_uavY;
      fuzzy::Linguistic *fz_speed_uavZ;

      fuzzy::Linguistic *fz_accelY;
      fuzzy::Linguistic *fz_accelX;
      fuzzy::Linguistic *fz_accelZ;

      fuzzy::Linguistic *fz_Oroll;
      fuzzy::Linguistic *fz_Opitch;
      fuzzy::Linguistic *fz_Othrottle;

      fuzzy::Linguistic *fz_i_stab_yaw;
      fuzzy::Linguistic *fz_o_stab_yaw;

      fuzzy::Linguistic *fz_yaw_uav_goal_dist;

      fuzzy::Linguistic *fz_Oyaw;

      fuzzy::Linguistic *fz_i_hnav;
      fuzzy::Linguistic *fz_o_hnav;

      fuzzy::Linguistic *fz_hnav_uav_goal_dist;
      fuzzy::Linguistic *fz_hnav_speed_goal;

      fuzzy::Linguistic *fz_roll_error;
      fuzzy::Linguistic *fz_pitch_error;
      fuzzy::Linguistic *fz_yaw_error;
      fuzzy::Linguistic *fz_hnav_yaw_error;

      fuzzy::Linguistic *fz_Opitch_nav;


// Class methods
      void initFZ();
      void initHexaPlus();

};

#endif 
 
