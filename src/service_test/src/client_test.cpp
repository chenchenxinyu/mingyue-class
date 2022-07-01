#include <ros/ros.h>
#include <service_message_test/service_message.h>
#include <iostream>
#include <string>
using namespace std;
int main(int argc,char **argv)
{
    ros::init(argc,argv,"client_test_node");
    ros::NodeHandle n;
    ros::ServiceClient client=n.serviceClient<service_message_test::service_message>("look_up_name");
    service_message_test::service_message srv;
    //bool 
    string in_name="";
    while (ros::ok())
    {
        cout<<endl;
        cout<<"enter a name(x to quit):";
        cin>>in_name;
        if (in_name.compare("x")==0)
        {
            return 0;
        }
        srv.request.name = in_name;
        if (client.call(srv))
        {
            if (srv.response.on_the_list)
            {
                cout<<srv.request.name<<"is known as"<<srv.response.nickname<<endl;
                cout<<"he is "<<srv.response.age<<"years old"<<endl;
                if (srv.response.good_guy)
                {
                    cout<<"he is a good guy"<<endl;
                }else{
                    cout<<"he is not a good guy"<<endl;
                }
                
            }else{
                cout<<srv.request.name<<"is not in the database"<<endl;
            }
            
        }else{
            ROS_ERROR("Failed to call service look_up_name");
            return 1;
        }
        
        
    }
    return 0;
    
}