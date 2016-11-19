#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <opencv2/opencv.hpp>
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  cv::Mat cvImg;
  try
  {
    // The bridge between ROS and OpenCV images format 
    cvImg =  cv_bridge::toCvShare(msg, "bgr8")->image;
    cv::imshow("Camera", cvImg);

    cv::waitKey(10);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{ 
std::cout << "Init..." << '\n';
  ros::init(argc, argv, "Camera");
std::cout << "Window..." << '\n';
  cv::namedWindow("Camera");
std::cout << "StartWindowThread..." << '\n';
  cv::startWindowThread();
std::cout << "NodeHandle..." << '\n';
  ros::NodeHandle nh;
std::cout << "Image Transport..." << '\n';
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("/vrep/vCamera", 1, imageCallback);
  
std::cout << "Start reading image..." << '\n';
  ros::Rate loop_rate(100);
  while (ros::ok())
  {
    loop_rate.sleep();
    ros::spinOnce();
  }
  cv::destroyWindow("Camera");
}
