cmake_minimum_required(VERSION 2.8.3)
project(hexaplus_tutorial)
find_package(
  catkin REQUIRED COMPONENTS
  roscpp
  roslib
  std_msgs
  image_transport
  cv_bridge
)
find_package( OpenCV 2 REQUIRED )

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES hexaplus_tutorial 
  CATKIN_DEPEND roscpp std_msgs roslib
  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
  include ${OpenCV_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS}
)

add_executable (rosvrep_controller src/rosvrep_controller.cpp)
add_executable (rosvrep_panel      src/rosvrep_panel.cpp)
add_executable (rosvrep_telemetry  src/rosvrep_telemetry.cpp)
add_executable (rosvrep_camera     src/rosvrep_camera.cpp)

add_library(MembershipFunction src/fuzzy/MembershipFunction.cpp)
add_library(Linguistic src/fuzzy/Linguistic.cpp)
add_library(LinguisticSet src/fuzzy/LinguisticSet.cpp)
add_library(RuleElement src/fuzzy/RuleElement.cpp)
add_library(Rule src/fuzzy/Rule.cpp)
add_library(RuleSet src/fuzzy/RuleSet.cpp)
add_library(FuzzySet src/fuzzy/FuzzySet.cpp)
add_library(FuzzyLoader src/fuzzy/FuzzyLoader.cpp)

add_library(navigation src/navigation.cpp)
add_library(HexaPlus src/HexaPlus.cpp)

target_link_libraries (rosvrep_controller 
                       HexaPlus 
                       navigation
                       FuzzyLoader 
                       FuzzySet 
                       Linguistic 
                       LinguisticSet
                       RuleSet
                       Rule
                       RuleElement
                       MembershipFunction 
                       ${catkin_LIBRARIES})
target_link_libraries (HexaPlus ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
target_link_libraries (rosvrep_panel HexaPlus ${catkin_LIBRARIES})
target_link_libraries (rosvrep_telemetry HexaPlus ${catkin_LIBRARIES})
target_link_libraries (rosvrep_camera HexaPlus ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})



