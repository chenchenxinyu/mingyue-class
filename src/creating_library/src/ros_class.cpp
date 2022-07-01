#include <creating_library/ros_class.h>

//前导、构造函数 
RosClass::RosClass(ros::NodeHandle* nodehandle):nh_(*nodehandle)
{
    ROS_INFO("in class constructor of ros class");
    initializePublishers();
    initializeServices();
    initializeSubscribers();

    val_to_remember_ = 0.0;
}
//助手成员函数
void RosClass::initializeSubscribers()
{
    ROS_INFO("initialize subscriber");
    message_subscriber_ = nh_.subscribe("class_input_topic",1, &RosClass::subscriberCallback,this);

}

void RosClass::initializeServices()
{
    ROS_INFO("initialize services");
    message_service_ = nh_.advertiseService("class_service", &RosClass::serviceCallback,this);
}

void RosClass::initializePublishers()
{
    ROS_INFO("initialize publisher");
    message_publisher_ = nh_.advertise<std_msgs::Float32>("class_output_topic",1,true);
}

//回调函数
void RosClass::subscriberCallback(const std_msgs::Float32& message_holder)
{
    val_from_subscriber_ = message_holder.data;
    ROS_INFO("sub the callback:received value %f",val_from_subscriber_);
    std_msgs::Float32 output_msg;
    val_to_remember_ +=val_from_subscriber_;
    output_msg.data = val_to_remember_;
    message_publisher_.publish(output_msg);
}

bool RosClass::serviceCallback(std_srvs::TriggerRequest& request,std_srvs::TriggerResponse& response)
{
    ROS_INFO("service callback activated");
    response.success = true;
    response.message = "a response message";
    return true;
}

//主函数
int main(int argc, char** argv)
{
    ros::init(argc,argv,"rosclass");
    ros::NodeHandle nh;
    ROS_INFO("main:instanding an object of type rosclass");
    RosClass RosClass(&nh);
    ROS_INFO("main :going into spin;let callback work");
    ros::spin();
    return 0;
}
