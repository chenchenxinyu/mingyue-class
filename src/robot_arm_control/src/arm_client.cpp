#include <ros/ros.h>
#include <robot_arm_message/robarm_server.h>
#include <robot_arm_message/robarmAngle.h>
#include <std_msgs/Bool.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc,argv,"arm_client_node");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<robot_arm_message::robarm_server>("control_arm");
    ros::Publisher ArmGazebo = n.advertise<std_msgs::Bool>("BoolGazebo",1);//发布一个话题为“BoolGazebo”，消息类型bool，进行传参
    ros::Publisher ArmAngle = n.advertise<robot_arm_message::robarmAngle>("ArmControllerAngle",1);
    std_msgs::Bool ArmGazeboBool;
    robot_arm_message::robarmAngle Arm_Angle;
    robot_arm_message::robarm_server srv;
    //定义变量
    float x,y,z;

    //交互部分
    while (ros::ok())
    {
        ArmGazeboBool.data = false;
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
                //cout<<"using time:"<<srv.response.time<<endl;
                ArmGazeboBool.data = true;
                ArmGazebo.publish(ArmGazeboBool);
                Arm_Angle.ArmAngle[0] = srv.response.theta_vector[0];
                Arm_Angle.ArmAngle[1] = srv.response.theta_vector[1];
                Arm_Angle.ArmAngle[2] = srv.response.theta_vector[2];
                Arm_Angle.ArmAngle[3] = srv.response.theta_vector[3];
                ArmAngle.publish(Arm_Angle);
                cout<<"send controller success"<<endl;
                
            }else{
                cout<<"calculate is wrong, change the input"<<endl;
            }
            
        }else{
            ROS_ERROR("Failed to call service arm_control");
            return 1;
        }
        
    }
    return 0;
    
}


