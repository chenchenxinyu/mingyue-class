#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <message_test/new_message.h>

int main(int argc, char **argv)
{
    ros::init(argc,argv,"message_test");
    ros::NodeHandle n;
    ros::Publisher message_publisher_object = n.advertise<std_msgs::Float64>("test_data",1);
    ros::Publisher vector_publisher_object = n.advertise<message_test::new_message>("vector_data",1);
    std_msgs::Float64 float_test;
    message_test::new_message vector_test;
    
    double counter = 0;
    float_test.data = 6.6;
    vector_test.header.stamp = ros::Time::now();
    vector_test.header.seq = 0;
    vector_test.header.frame_id = "cxy_data";
    vector_test.message_int = 1;
    vector_test.double_vector.resize(3);
    vector_test.double_vector[0] = 21.892930;
    vector_test.double_vector[1] = 282.2;
    vector_test.double_vector[2] = 99.99;
    vector_test.double_vector.push_back(counter);
    
    ros::Rate naptime(0.5);  //表示频率  也就是赫兹
    while(ros::ok())
    {
        float_test.data = float_test.data + 0.002;
        message_publisher_object.publish(float_test);

        vector_test.header.seq++;
        vector_test.header.stamp = ros::Time::now();
        vector_test.message_int+=2.0;
        counter = counter+1.0;
        //vector_test.double_vector.push_back(counter);
        vector_publisher_object.publish(vector_test);

        naptime.sleep();    
    }

}
