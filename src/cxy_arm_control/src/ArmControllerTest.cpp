#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>
#include <control_msgs/JointControllerState>
#include <robot_arm_message/robarmAngle.h>
void ArmStateBcak()
{

}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"ArmController");
    ros::NodeHandle n;
    ros::Publisher ArmJoint0Pub=n.advertise<std_msgs::Float64>("/cxyarm/joint0_position_controller/command",1);
    ros::Publisher ArmJoint1Pub=n.advertise<std_msgs::Float64>("/cxyarm/joint1_position_controller/command",1);
    ros::Publisher ArmJoint2Pub=n.advertise<std_msgs::Float64>("/cxyarm/joint2_position_controller/command",1);
    ros::Publisher ArmJoint3Pub=n.advertise<std_msgs::Float64>("/cxyarm/joint3_position_controller/command",1);
    ros::Subscriber ArmJoint0State=n.subscribe("/cxyarm/joint0_position_controller/state",1,ArmStateBcak);
    ros::Subscriber ArmJoint1State=n.subscribe("/cxyarm/joint1_position_controller/state",1,ArmStateBcak);
    ros::Subscriber ArmJoint2State=n.subscribe("/cxyarm/joint2_position_controller/state",1,ArmStateBcak);
    ros::Subscriber ArmJoint3State=n.subscribe("/cxyarm/joint3_position_controller/state",1,ArmStateBcak);
    
    std_msgs::Float64 command0;
    std_msgs::Float64 command1;
    std_msgs::Float64 command2;
    std_msgs::Float64 command3;
    command0.data = 0;
    command1.data = 0;
    command2.data = 0;
    command3.data = 0;
    ros::Rate naptime(2);
    
    while (ros::ok())
    {
        command0.data = command0.data+0.1;
        command1.data = command1.data+0.1;
        command2.data = command2.data+0.1;
        command3.data = command3.data+0.1;
        ArmJoint0Pub.publish(command0);
        ArmJoint1Pub.publish(command1);
        ArmJoint2Pub.publish(command2);
        ArmJoint3Pub.publish(command3);
        naptime.sleep();
      /*  command0.data = 1.8+3.14;
        command1.data = -2.1+3.14;
        command2.data = 1.4+3.14;
        command3.data = 1.1+3.14;
        ArmJoint0Pub.publish(command0);
        ArmJoint1Pub.publish(command1);
        ArmJoint2Pub.publish(command2);
        ArmJoint3Pub.publish(command3);
        naptime.sleep();*/
    }
    
}

