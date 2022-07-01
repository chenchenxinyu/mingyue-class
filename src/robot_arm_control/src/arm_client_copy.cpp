#include <ros/ros.h>
#include <robot_arm_message/robarm_server.h>
#include <robot_arm_message/robarm_gazebo.h>
#include <std_msgs/Bool.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc,argv,"arm_client_node");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<robot_arm_message::robarm_server>("control_arm");
    ros::ServiceClient gazeboclient = n.serviceClient<robot_arm_message::robarm_gazebo>("gazebo_arm");
    robot_arm_message::robarm_server srv;
    robot_arm_message::robarm_gazebo gazsrv;
    //定义变量
    float x,y,z;
    float angle0,angle1,angle2,angle3; 
    bool gazebostate;
    //交互部分
    while (ros::ok())
    {
        cout<<endl;
        cout<<"enter a position(let x is -7 to quit):";
        cin>>x>>y>>z;
        if(x==-7)
        {
            return 0;
        }
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
                gazebostate = true;
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
        
        gazsrv.request.ArmAngle[0] = angle0;
        gazsrv.request.ArmAngle[1] = angle1;
        gazsrv.request.ArmAngle[2] = angle2;
        gazsrv.request.ArmAngle[3] = angle3;
        gazsrv.request.workstate = gazebostate;
        if(gazeboclient.call(gazsrv))
        {
            if(gazsrv.response.controllerstate)
            {
                
                ROS_INFO("get the work angle list, and start gazebo!");
            }else{
                ROS_INFO("not get the response from gazebo controller");
            }
        }else{
            ROS_ERROR("failed to call service arm_gazebo");
            return 1;
        }
        
    }
    return 0;
    
}


