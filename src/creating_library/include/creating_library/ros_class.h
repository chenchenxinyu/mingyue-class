#ifndef ROS_CLASS_H_
#define ROS_CLASS_H_

#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <std_srvs/Trigger.h>

class RosClass
{
private:
    /* data */
    ros::NodeHandle nh_;
    ros::Subscriber message_subscriber_;
    ros::Publisher message_publisher_;
    ros::ServiceServer message_service_;
    
    double val_from_subscriber_;
    double val_to_remember_;
    
    void initializeSubscribers();
    void initializePublishers();
    void initializeServices();
    void subscriberCallback(const std_msgs::Float32& message_holder);
    bool serviceCallback(std_srvs::TriggerRequest& request,std_srvs::TriggerResponse& response);

public:
    RosClass(ros::NodeHandle* nodehandle);
    //RosClass(/* args */);
    //~RosClass();
};


#endif
