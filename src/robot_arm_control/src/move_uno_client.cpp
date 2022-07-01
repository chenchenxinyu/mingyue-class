#include <ros/ros.h>
#include <iostream>
#include <stdio.h>
#include <robot_arm_message/move_uno.h>
#include <std_msgs/Float64.h>
using namespace std;

std_msgs::Float64 CmdNumber; //1-7
std_msgs::Float64 RunTime; //ms

int main(int argc,char **argv)
{
    ros::init(argc,argv,"move_uno_client");
    ros::NodeHandle n;
    ros::ServiceClient MoveUnoClient = n.serviceClient<robot_arm_message::move_uno>("move_uno");
    robot_arm_message::move_uno unosrv;

    CmdNumber.data = 0;
    RunTime.data = 0;
    while(ros::ok())
    {
        float cmd,timer;
        cout<<endl;
        cout<<"enter state: "<<endl;
        cin>>cmd>>timer;
        CmdNumber.data = cmd;
        RunTime.data = timer;
        if(CmdNumber.data==9)
        {
            return 0;
        }
        unosrv.request.CmdNumber = CmdNumber.data;
        unosrv.request.RunTime = RunTime.data;

        if(MoveUnoClient.call(unosrv))
        {
            if(unosrv.response.UNOstate)
            {
                ROS_INFO("***uno move success***");
            }
            else{
                ROS_INFO("UNOstate false");
            }
        }else{
            ROS_ERROR("Failed to call service uno move");
            return 1;
        }
    }
    return 0;

}