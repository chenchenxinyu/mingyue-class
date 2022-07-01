#include <ros/ros.h>
#include <message_test/service_message.h>
#include <iostream>
#include <string>
using namespace std;

bool callback(message_test::service_message& request, message_test::service_message& response)
{
    ROS_INFO("callback success");
    string in_name(request.name);
    response.on_the_list = false;
    if (in_name.compare("Bob") == 0)
    {
        ROS_INFO("asked about bob");
        response.age = 32;
        response.good_guy = false;
        response.on_the_list = true;
        response.nickname = "bbbbbbo";
    }
    if (in_name.compare("ted") == 0)
    {
        ROS_INFO("asked about ted");
        response.age = 321;
        response.good_guy = true;
        response.on_the_list = true;
        response.nickname = "tttedddddddd";
    }
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"service_test");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("look_up_name",callback);
    ROS_INFO("ready to look up the name!");
    ros::spin();
    return 0;
}
