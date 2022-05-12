#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

ros::Publisher velPublisher;
geometry_msgs::Twist velMessage;


bool handle_drive_request(ball_chaser::DriveToTarget::Request &req,
                     ball_chaser::DriveToTarget::Response &res);

int main(int argc, char** argv){
  ros::init(argc,argv,"drive_bot");
  ros::NodeHandle nh;
  
  velPublisher = nh.advertise<geometry_msgs::Twist>("cmd_vel",10);
  
  ros::ServiceServer myServer = nh.advertiseService("/ball_chaser/command_robot",handle_drive_request);
  ROS_INFO("Service is ready");
  ros::spin();
  return 0;
  
}
                                                   
bool handle_drive_request(ball_chaser::DriveToTarget::Request &req,
                     ball_chaser::DriveToTarget::Response &res){
                     
  velMessage.linear.x = req.linear_x;
  velMessage.angular.z = req.angular_z; 
  velPublisher.publish(velMessage);
  res.msg_feedback = "Message have been published";
  return true; 
}