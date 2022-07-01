#include <creating_library/ros_class.h>

int main(int argc, char** argv)
{
    ros::init(argc,argv,"lib_test");
    ros::NodeHandle nh;
    ROS_INFO("main in the lib test");
    RosClass RosClass(&nh);
    ROS_INFO("main :going into spin;let callback work");
    ros::spin();
    return 0;
}
