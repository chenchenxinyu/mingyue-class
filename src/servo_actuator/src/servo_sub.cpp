#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <iostream>
#include "CSerialPort/SerialPort.h"
#include "FashionStar/UServo/FashionStar_UartServoProtocol.h"
#include "FashionStar/UServo/FashionStar_UartServo.h"
using namespace fsuservo;

#define SERVO_PORT_NAME "/dev/ttyUSB0"
uint16_t interval;  // 运行周期 单位ms 
uint16_t t_acc;     // 加速时间 单位ms
uint16_t t_dec;     // 减速时间 单位ms

// 创建协议对象
FSUS_Protocol protocol(SERVO_PORT_NAME, FSUS_DEFAULT_BAUDRATE);
// 创建一个舵机对象
FSUS_Servo servo0(1, &protocol);//arm base
FSUS_Servo servo1(2, &protocol);//arm link1
FSUS_Servo servo2(3, &protocol);//arm link2
FSUS_Servo servo3(4, &protocol);//arm link3
FSUS_Servo servo4(5, &protocol);//gun base
FSUS_Servo servo5(6, &protocol);//gun tower
/* 舵机角度设置回调函数 */
void set_servo0_callback(const std_msgs::Float32& message_holder){
    ROS_INFO("[RECV] Servo ID = 1 Set Angle = %.1f", message_holder.data);
    // 设置舵机1角度
    // servo0.setRawAngle(message_holder.data, 0);
    servo0.setRawAngleByInterval(message_holder.data, interval, t_acc, t_dec, 0);
}
void set_servo1_callback(const std_msgs::Float32& message_holder){
    ROS_INFO("[RECV] Servo ID = 2 Set Angle = %.1f", message_holder.data);
    // 设置舵机2角度
    // servo1.setRawAngle(message_holder.data, 0);
    servo1.setRawAngleByInterval(message_holder.data, interval, t_acc, t_dec, 0);
}
void set_servo2_callback(const std_msgs::Float32& message_holder){
    ROS_INFO("[RECV] Servo ID = 3 Set Angle = %.1f", message_holder.data);
    // 设置舵机3角度
    // servo2.setRawAngle(message_holder.data, 0);
    servo2.setRawAngleByInterval(message_holder.data, interval, t_acc, t_dec, 0);
}
void set_servo3_callback(const std_msgs::Float32& message_holder){
    ROS_INFO("[RECV] Servo ID = 4 Set Angle = %.1f", message_holder.data);
    // 设置舵机4角度
    // servo3.setRawAngle(message_holder.data, 0);
    servo3.setRawAngleByInterval(message_holder.data, interval, t_acc, t_dec, 0);
}
void set_servo4_callback(const std_msgs::Float32& message_holder){
    ROS_INFO("[RECV] Servo ID = 5 Set Angle = %.1f", message_holder.data);
    // 设置舵机3角度
    // servo2.setRawAngle(message_holder.data, 0);
    servo4.setRawAngleByInterval(message_holder.data, interval, t_acc, t_dec, 0);
}
void set_servo5_callback(const std_msgs::Float32& message_holder){
    ROS_INFO("[RECV] Servo ID = 6 set Angle = %.1f", message_holder.data);
    // 设置舵机4角度
    // servo3.setRawAngle(message_holder.data, 0);
    servo5.setRawAngleByInterval(message_holder.data, interval, t_acc, t_dec, 0);
}

int main (int argc, char **argv)
{
    interval = 300;
    t_acc = 100;
    t_dec = 100;
    ros::init(argc,argv,"servo_sub");
    ros::NodeHandle nh;
    ros::Subscriber set_servo0_angle = nh.subscribe("servo0",1,set_servo0_callback);
    ros::Subscriber set_servo1_angle = nh.subscribe("servo1",1,set_servo1_callback);
    ros::Subscriber set_servo2_angle = nh.subscribe("servo2",1,set_servo2_callback);
    ros::Subscriber set_servo3_angle = nh.subscribe("servo3",1,set_servo3_callback);
    ros::Subscriber set_servo4_angle = nh.subscribe("servo4",1,set_servo4_callback);
    ros::Subscriber set_servo5_angle = nh.subscribe("servo5",1,set_servo5_callback);
    ROS_INFO("wait PUB cmd");
    ros::spin();
    return 0;
}

