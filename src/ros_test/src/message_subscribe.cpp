#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <message_test/new_message.h>

void messageCallback(const message_test::new_message& message_holder)
{
    std::vector <double> vec_double = message_holder.double_vector;
    int nvals = vec_double.size();
    for(int i = 0;i < nvals;i++)
    {
        ROS_INFO("vec[%d]=%f",i,vec_double[i]);
        //ROS_INFO("run_time = %d",message_holder.header.stamp)
    }
    ROS_INFO("\n");    

}


int main(int argc, char **argv)
{
    ros::init(argc,argv,"subscribe_message");
    ros::NodeHandle n;
    ros::Subscriber message_subscribe_object = n.subscribe("vector_data",1,messageCallback);
    ros::spin();
    return 0;


}
