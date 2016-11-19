#include "hexaplus_tutorial/HexaPlus.h"
#include "ros/package.h"

///////////////////
// Fuzzy artefacts
//

void HexaPlus::initFZ() {
  std::string path = ros::package::getPath("hexaplus_tutorial");
  std::stringstream ssi,sso,ssr;

  fuzzy::FuzzyLoader fzLoader;

  ssi.str(""); ssi << path << "/fz/HexaPlus_i_stabX.fz";
  sso.str(""); sso << path << "/fz/HexaPlus_o_stabX.fz";
  ssr.str(""); ssr << path << "/fz/HexaPlus_r_stabX.fz";
  fzLoader.loadFromFile(fS_stabX,ssi.str().c_str(),sso.str().c_str(),ssr.str().c_str());


  ssi.str(""); ssi << path << "/fz/HexaPlus_i_stabY.fz";
  sso.str(""); sso << path << "/fz/HexaPlus_o_stabY.fz";
  ssr.str(""); ssr << path << "/fz/HexaPlus_r_stabY.fz";
  fzLoader.loadFromFile(fS_stabY,ssi.str().c_str(),sso.str().c_str(),ssr.str().c_str());

  ssi.str(""); ssi << path << "/fz/HexaPlus_i_stabZ.fz";
  sso.str(""); sso << path << "/fz/HexaPlus_o_stabZ.fz";
  ssr.str(""); ssr << path << "/fz/HexaPlus_r_stabZ.fz";
  fzLoader.loadFromFile(fS_stabZ,ssi.str().c_str(),sso.str().c_str(),ssr.str().c_str());

  fz_roll_error    = fS_stabX->inputLinguisticSet->getLinguisticByName("roll_error");
  fz_pitch_error   = fS_stabY->inputLinguisticSet->getLinguisticByName("pitch_error");
  fz_uavZ_error    = fS_stabZ->inputLinguisticSet->getLinguisticByName("uavZ_error");

  fz_speed_uavZ    = fS_stabZ->inputLinguisticSet->getLinguisticByName("speed_uavZ");

  fz_accelX        = fS_stabY->inputLinguisticSet->getLinguisticByName("accelX");
  fz_accelY        = fS_stabX->inputLinguisticSet->getLinguisticByName("accelY");

  fz_Oroll         = fS_stabX->outputLinguisticSet->getLinguisticByName("Oroll");
  fz_Opitch        = fS_stabY->outputLinguisticSet->getLinguisticByName("Opitch");
  fz_Othrottle     = fS_stabZ->outputLinguisticSet->getLinguisticByName("Othrottle");

// Orientation 

  ssi.str(""); ssi << path << "/fz/HexaPlus_i_stab_yaw.fz";
  sso.str(""); sso << path << "/fz/HexaPlus_o_stab_yaw.fz";
  ssr.str(""); ssr << path << "/fz/HexaPlus_r_stab_yaw.fz";
  fzLoader.loadFromFile(fS_yaw,ssi.str().c_str(),sso.str().c_str(),ssr.str().c_str());

  fz_yaw_error         = fS_yaw->inputLinguisticSet->getLinguisticByName("yaw_error");
  fz_yaw_uav_goal_dist = fS_yaw->inputLinguisticSet->getLinguisticByName("uav_goal_dist");
  fz_Oyaw              = fS_yaw->outputLinguisticSet->getLinguisticByName("Oyaw");

// Horizontal Navigation

  ssi.str(""); ssi << path << "/fz/HexaPlus_i_hnav.fz";
  sso.str(""); sso << path << "/fz/HexaPlus_o_hnav.fz";
  ssr.str(""); ssr << path << "/fz/HexaPlus_r_hnav.fz";
  fzLoader.loadFromFile(fS_hnav,ssi.str().c_str(),sso.str().c_str(),ssr.str().c_str());

  fz_hnav_uav_goal_dist = fS_hnav->inputLinguisticSet->getLinguisticByName("uav_goal_dist");
  fz_hnav_speed_goal    = fS_hnav->inputLinguisticSet->getLinguisticByName("speed_goal");
  fz_Opitch_nav         = fS_hnav->outputLinguisticSet->getLinguisticByName("Opitch_nav");

  // Check if the fuzzy set has been loaded
  if (fz_roll_error==NULL) 
     { std::cout << "Error: Linguistic fz_roll_error not found" << std::endl; exit(-1); }

  if (fz_pitch_error==NULL) 
     { std::cout << "Error: Linguistic fz_pitch_error not found" << std::endl; exit(-1); }

  if (fz_uavZ_error==NULL) 
     { std::cout << "Error: Linguistic fz_uavZ_error not found" << std::endl; exit(-1); }

  if (fz_speed_uavZ==NULL) 
     { std::cout << "Error: Linguistic fz_speed_uavZ not found" << std::endl; exit(-1); }

  if (fz_accelX==NULL) 
     { std::cout << "Error: Linguistic fz_accelX not found" << std::endl; exit(-1); }

  if (fz_accelY==NULL) 
     { std::cout << "Error: Linguistic fz_accelY not found" << std::endl; exit(-1); }

  if (fz_Oroll==NULL) 
     { std::cout << "Error: Linguistic fz_Oroll not found" << std::endl; exit(-1); }

  if (fz_Opitch==NULL) 
     { std::cout << "Error: Linguistic fz_Opitch not found" << std::endl; exit(-1); }

  if (fz_Othrottle==NULL) 
     { std::cout << "Error: Linguistic fz_Othrottle not found" << std::endl; exit(-1); }

  if (fz_yaw_error==NULL) 
     { std::cout << "Error: Linguistic fz_yaw_error not found" << std::endl; exit(-1); }

  if (fz_yaw_uav_goal_dist==NULL) 
     { std::cout << "Error: Linguistic fz_yaw_uav_goal_dist not found" << std::endl; exit(-1); }

  if (fz_Oyaw==NULL) 
     { std::cout << "Error: Linguistic fz_Oyaw not found" << std::endl; exit(-1); }

  if (fz_hnav_uav_goal_dist==NULL) 
     { std::cout << "Error: Linguistic fz_hnav_uav_goal_dist not found" << std::endl; exit(-1); }

  if (fz_hnav_speed_goal==NULL) 
     { std::cout << "Error: Linguistic fz_hnav_speed_goal not found" << std::endl; exit(-1); }

  if (fz_Opitch_nav==NULL) 
     { std::cout << "Error: Linguistic fz_Opitch_nav not found" << std::endl; exit(-1); }
} 

void HexaPlus::initHexaPlus() { 

     speed_gpsX,speed_gpsY,speed_gpsZ=0;
     speed_uavX,speed_uavY,speed_uavZ=0;
     float eulerX = 0;
     float eulerY = 0;
     float eulerZ = 0;

     float gpsX = 0;
     float gpsY = 0;
     float gpsZ = 0;

     float propForceFRONT       =0;
     float propForceRIGHT_FRONT =0;
     float propForceRIGHT_REAR  =0;
     float propForceREAR        =0;
     float propForceLEFT_REAR   =0;
     float propForceLEFT_FRONT  =0;

     iniX=iniY=iniZ = 0;
     endX=endY=endZ = 0;
     dX=dY=dZ=dt    = 0;

     gpsX_setpoint  = 0;
     gpsY_setpoint  = 0;
     gpsZ_setpoint  = 0;

     roll_setpoint  = 0;
     pitch_setpoint = 0;
     yaw_setpoint   = 0;

     initFZ(); 
}

