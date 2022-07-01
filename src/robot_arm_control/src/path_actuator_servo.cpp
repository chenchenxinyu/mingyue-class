#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <robot_arm_message/pathlist.h>
#include <robot_arm_message/robarm_server.h>
#include <robot_arm_message/ServoAngle.h>
#include <iostream>
#include "CSerialPort/SerialPort.h"
#include "FashionStar/UServo/FashionStar_UartServoProtocol.h"
#include "FashionStar/UServo/FashionStar_UartServo.h"
#include <math.h>
using namespace fsuservo;
using namespace std;

#define SERVO_PORT_NAME "/dev/ttyUSB0"  // Linux下端口号名称 /dev/ttyUSB{}
FSUS_Protocol protocol(SERVO_PORT_NAME, FSUS_DEFAULT_BAUDRATE);
FSUS_Servo servo0(1,&protocol);
FSUS_Servo servo1(2,&protocol);
FSUS_Servo servo2(3,&protocol);
FSUS_Servo servo3(4,&protocol);

std_msgs::Float64 command0;
std_msgs::Float64 command1;
std_msgs::Float64 command2;
std_msgs::Float64 command3;

uint16_t interval;  // 运行周期 单位ms 
uint16_t t_acc;     // 加速时间 单位ms
uint16_t t_dec;     // 减速时间 单位ms
float velocity;         // 目标转速 单位°/s

robot_arm_message::ServoAngle sgl;

robot_arm_message::pathlist path;
float x,y,z;
float angle0,angle1,angle2,angle3; 
void pathcallback(const robot_arm_message::pathlist& message_holder)
{
    path.pathlistdata = message_holder.pathlistdata;
    x = path.pathlistdata[0];
    y = path.pathlistdata[1];
    z = path.pathlistdata[2];
    ROS_INFO("get the path data");
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"path_actuator");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<robot_arm_message::robarm_server>("control_arm");
    ros::Publisher ArmJoint0Pub = n.advertise<std_msgs::Float64>("/cxyarm/joint0_position_controller/command", 1);
    ros::Publisher ArmJoint1Pub = n.advertise<std_msgs::Float64>("/cxyarm/joint1_position_controller/command", 1);
    ros::Publisher ArmJoint2Pub = n.advertise<std_msgs::Float64>("/cxyarm/joint2_position_controller/command", 1);
    ros::Publisher ArmJoint3Pub = n.advertise<std_msgs::Float64>("/cxyarm/joint3_position_controller/command", 1);
    ros::Subscriber path_subscriber = n.subscribe("path",1,pathcallback);
    double rate = 1;
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
        ROS_INFO("send pathlist position success");
        cout<<"angle0 is  "<<angle0<<endl;
        sgl.ServoAngle[0] = angle0*180/M_PI-137;
        sgl.ServoAngle[1] = angle1*180/M_PI+68;
        sgl.ServoAngle[2] = -angle2*180/M_PI-25;
        sgl.ServoAngle[3] = -angle3*180/M_PI-18;
        interval = 500;//运行周期 0.5s
        t_acc = 100;//加速时间
        t_dec = 100;//减速时间
        velocity = 100.0;//目标转速
        // servo0.setRawAngleByInterval(sgl.ServoAngle[0], interval, t_acc, t_dec, 0);
        // servo1.setRawAngleByInterval(sgl.ServoAngle[1], interval, t_acc, t_dec, 0);
        // servo2.setRawAngleByInterval(sgl.ServoAngle[2], interval, t_acc, t_dec, 0);
        // servo3.setRawAngleByInterval(sgl.ServoAngle[3], interval, t_acc, t_dec, 0);

        servo0.setRawAngleByInterval(angle0*180/M_PI-137, interval, t_acc, t_dec, 0);
        // servo1.setRawAngleByInterval(angle1*180/M_PI+68, interval, t_acc, t_dec, 0);
        // servo2.setRawAngleByInterval(-angle2*180/M_PI-25, interval, t_acc, t_dec, 0);
        // servo3.setRawAngleByInterval(-angle3*180/M_PI-18, interval, t_acc, t_dec, 0);
        servo3.setRawAngleByInterval(velocity-18, interval, t_acc, t_dec, 0);
        velocity = velocity+10;
        servo0.queryRawAngle();
		servo1.queryRawAngle();
		servo2.queryRawAngle();
		servo3.queryRawAngle();
        cout << "********romachen**data************"<<endl;
        cout << "*******Servo0 Angle: " <<  servo0.curRawAngle <<"***" <<endl;
		cout << "*******Servo1 Angle: " <<  servo1.curRawAngle <<"***" <<endl;
		cout << "*******Servo2 Angle: " <<  servo2.curRawAngle <<"***" <<endl;
		cout << "*******Servo3 Angle: " <<  servo3.curRawAngle <<"***" <<endl;
        cout << "**********************************"<<endl;
        ros::spinOnce();
        naptime.sleep();
    }
    return 0;

}