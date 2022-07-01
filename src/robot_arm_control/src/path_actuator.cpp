#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32.h>
#include <robot_arm_message/pathlist.h>
#include <robot_arm_message/robarm_server.h>
#include <iostream>
#include <cmath>
using namespace std;
std_msgs::Float64 command0;
std_msgs::Float64 command1;
std_msgs::Float64 command2;
std_msgs::Float64 command3;

const float Rad_to_deg = 45.0 / atan(1.0);
robot_arm_message::pathlist path;
float x,y,z;
float angle0,angle1,angle2,angle3; 
void pathcallback(const robot_arm_message::pathlist& message_holder)
{
    path.pathlistdata = message_holder.pathlistdata;
    x = path.pathlistdata[0];
    y = path.pathlistdata[1];
    z = path.pathlistdata[2];
    ROS_INFO("subscribe path data");
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"path_actuator");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<robot_arm_message::robarm_server>("control_arm");//calculate angle
    ros::Publisher ArmJoint0Pub = n.advertise<std_msgs::Float64>("/cxyarm/joint0_position_controller/command", 1);
    ros::Publisher ArmJoint1Pub = n.advertise<std_msgs::Float64>("/cxyarm/joint1_position_controller/command", 1);
    ros::Publisher ArmJoint2Pub = n.advertise<std_msgs::Float64>("/cxyarm/joint2_position_controller/command", 1);
    ros::Publisher ArmJoint3Pub = n.advertise<std_msgs::Float64>("/cxyarm/joint3_position_controller/command", 1);//gazebo
    ros::Publisher Servo0Work = n.advertise<std_msgs::Float32>("servo0",1);
    ros::Publisher Servo1Work = n.advertise<std_msgs::Float32>("servo1",1);
    ros::Publisher Servo2Work = n.advertise<std_msgs::Float32>("servo2",1);
    ros::Publisher Servo3Work = n.advertise<std_msgs::Float32>("servo3",1);//servo work
    ros::Subscriber path_subscriber = n.subscribe("path",1,pathcallback);//sub point
    double rate = 3;
    //频率f  每次发送的周期T=1/f  点数据发布时间间隔要长于订阅者，保证数据全部被收到
    //订阅者进行解算角度，并且发布到gazebo和舵机中，舵机执行程序的订阅时间间隔要短于发布者，保证发布者每个信息被收到
    //f：1 3 10
    ros::Rate naptime(rate);
    command0.data = 0;
    command1.data = 0;
    command2.data = 0;
    command3.data = 0;
    x=1;
    y=1;
    z=1;
    robot_arm_message::robarm_server srv;


    while(ros::ok())
    {
        srv.request.xyz_vector[0] = x;
        srv.request.xyz_vector[1] = y;
        srv.request.xyz_vector[2] = z;
        if (client.call(srv))
        {
            if (srv.response.state)//if state is true
            {
                cout<<"calculate is right"<<endl;
                cout<<"theta0:"<<srv.response.theta_vector[0]<<endl;
                cout<<"theta1:"<<srv.response.theta_vector[1]<<endl;
                cout<<"theta2:"<<srv.response.theta_vector[2]<<endl;
                cout<<"theta3:"<<srv.response.theta_vector[3]<<endl;
                // gazebostate = true;
                angle0 = srv.response.theta_vector[0];
                angle1 = srv.response.theta_vector[1];
                angle2 = srv.response.theta_vector[2];
                angle3 = srv.response.theta_vector[3];
                cout<<"send controller success"<<endl;
                
            }else{
                cout<<"calculate is wrong, change the input"<<endl;
            }
        }else{
            ROS_ERROR("Failed to call service arm_control");
            return 1;
        }
        command0.data = angle0;
        command1.data = angle1;
        command2.data = angle2;
        command3.data = angle3;
        ArmJoint0Pub.publish(command0);
        ArmJoint1Pub.publish(command1);
        ArmJoint2Pub.publish(command2);
        ArmJoint3Pub.publish(command3);
        //舵机发送信息接收角度制，不是弧度制，需要区分 ps:similar float32 or 64   注意舵机虚位考虑
        command0.data = 90+137+angle0*Rad_to_deg;
        command1.data = 68+angle1*Rad_to_deg;
        command2.data = -25-angle2*Rad_to_deg;
        command3.data = -18-angle3*Rad_to_deg;
        Servo0Work.publish(command0);
        Servo1Work.publish(command1);
        Servo2Work.publish(command2);
        Servo3Work.publish(command3);
        ROS_INFO("PUBLISH pathlist position success");
        ros::spinOnce();
        naptime.sleep();
    }
    return 0;

}