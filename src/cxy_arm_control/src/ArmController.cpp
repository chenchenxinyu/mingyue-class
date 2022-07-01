#include <ros/ros.h>
#include <iostream>
#include <string>
#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>
// #include <control_msgs/JointControllerState>
#include <robot_arm_message/robarmAngle.h>
using namespace std;
std_msgs::Bool workstate;
std_msgs::Float64 command0;
std_msgs::Float64 command1;
std_msgs::Float64 command2;
std_msgs::Float64 command3;

void clientCallback(const std_msgs::Bool& message_holder)
{
  workstate = message_holder;
  cout<<"client get, and the state  is "<<workstate<<endl;


}
void clientAngleCallback(const robot_arm_message::robarmAngle& message_holder)
{
  command0.data = message_holder.ArmAngle[0];
  command1.data = message_holder.ArmAngle[1];
  command2.data = message_holder.ArmAngle[2];
  command3.data = message_holder.ArmAngle[3];
  ROS_INFO("ArmAngle");
}
// void ArmStateBcak()
// {

// }

int main(int argc, char **argv)
{
    ros::init(argc,argv,"ArmController");
    ros::NodeHandle n;
    ros::Publisher ArmJoint0Pub=n.advertise<std_msgs::Float64>("/cxyarm/joint0_position_controller/command",1);
    ros::Publisher ArmJoint1Pub=n.advertise<std_msgs::Float64>("/cxyarm/joint1_position_controller/command",1);
    ros::Publisher ArmJoint2Pub=n.advertise<std_msgs::Float64>("/cxyarm/joint2_position_controller/command",1);
    ros::Publisher ArmJoint3Pub=n.advertise<std_msgs::Float64>("/cxyarm/joint3_position_controller/command",1);
    // ros::Subscriber ArmJoint0State=n.subscribe("/cxyarm/joint0_position_controller/state",1,ArmStateBcak);
    // ros::Subscriber ArmJoint1State=n.subscribe("/cxyarm/joint1_position_controller/state",1,ArmStateBcak);
    // ros::Subscriber ArmJoint2State=n.subscribe("/cxyarm/joint2_position_controller/state",1,ArmStateBcak);
    // ros::Subscriber ArmJoint3State=n.subscribe("/cxyarm/joint3_position_controller/state",1,ArmStateBcak);
    ros::Subscriber client_state = n.subscribe("BoolGazebo",1,clientCallback);
    ros::Subscriber client_angle = n.subscribe("ArmControllerAngle",1,clientAngleCallback);

    ros::Rate naptime(2);
    
    while (ros::ok())
    {
        // command0.data = command0.data+0.1;
        // command1.data = command1.data+0.1;
        // command2.data = command2.data+0.1;
        // command3.data = command3.data+0.1;
        ArmJoint0Pub.publish(command0);
        ArmJoint1Pub.publish(command1);
        ArmJoint2Pub.publish(command2);
        ArmJoint3Pub.publish(command3);
        naptime.sleep();

    }
    
}

