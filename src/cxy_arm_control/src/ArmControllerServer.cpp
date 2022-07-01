#include <ros/ros.h>
#include <iostream>
#include <string>
#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>
// #include <control_msgs/JointControllerState>
#include <robot_arm_message/robarm_gazebo.h>
using namespace std;

std_msgs::Bool workstate;
std_msgs::Float64 command0;
std_msgs::Float64 command1;
std_msgs::Float64 command2;
std_msgs::Float64 command3;

void clientCallback(const std_msgs::Bool &message_holder)
{
  workstate = message_holder;
  cout << "client get, and the state  is " << workstate << endl;
}
void clientAngleCallback(robot_arm_message::robarm_gazeboRequest &request, robot_arm_message::robarm_gazeboResponse &response)
{
  workstate.data = request.workstate;
  command0.data = request.ArmAngle[0];
  command1.data = request.ArmAngle[1];
  command2.data = request.ArmAngle[2];
  command3.data = request.ArmAngle[3];
  ROS_INFO("get the request data!");
  if (workstate.data)
  {
    response.controllerstate = true;
    ROS_INFO("state ok");
  }
  else
  {
    response.controllerstate = false;
    ROS_INFO("state wrong");
  }
}
// void ArmStateBcak()
// {

// }

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ArmController");
  ros::NodeHandle n;
  ROS_INFO("start controller work");
  ros::Publisher ArmJoint0Pub = n.advertise<std_msgs::Float64>("/cxyarm/joint0_position_controller/command", 1);
  ros::Publisher ArmJoint1Pub = n.advertise<std_msgs::Float64>("/cxyarm/joint1_position_controller/command", 1);
  ros::Publisher ArmJoint2Pub = n.advertise<std_msgs::Float64>("/cxyarm/joint2_position_controller/command", 1);
  ros::Publisher ArmJoint3Pub = n.advertise<std_msgs::Float64>("/cxyarm/joint3_position_controller/command", 1);
  // ros::Subscriber ArmJoint0State=n.subscribe("/cxyarm/joint0_position_controller/state",1,ArmStateBcak);
  // ros::Subscriber ArmJoint1State=n.subscribe("/cxyarm/joint1_position_controller/state",1,ArmStateBcak);
  // ros::Subscriber ArmJoint2State=n.subscribe("/cxyarm/joint2_position_controller/state",1,ArmStateBcak);
  // ros::Subscriber ArmJoint3State=n.subscribe("/cxyarm/joint3_position_controller/state",1,ArmStateBcak);
  ros::ServiceServer service = n.advertiseService("gazebo_arm", clientAngleCallback);

  ArmJoint0Pub.publish(command0);
  ArmJoint1Pub.publish(command1);
  ArmJoint2Pub.publish(command2);
  ArmJoint3Pub.publish(command3);
  ROS_INFO("controller success!");
  ros::spin();
}
