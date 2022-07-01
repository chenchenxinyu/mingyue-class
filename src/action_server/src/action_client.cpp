#include <ros/ros.h>
#include <actionlib/client/action_client.h> //actionlib库文件
#include <action_server/demoAction.h>//消息定义

void doneCB(const actionlib::ClientGoalState& state, const action_server::demoResultConstPtr& result)
{
    ROS_INFO("doneCB server response with state[%s]",state.toString().c_str());
    int diff = result->output - result->goal_stamp;//次数作差值，我们希望为0
    ROS_INFO("got result output = %d; goal_stamp = %d; diff = %d", result->output, result->goal_stamp, diff);

}



int main(int argc,char** argv)
{
    ros::init(argc,argv,"action_client_node");
    int g_count = 0;
    action_server::demoGoal goal;//实例化变量对象
    //
    actionlib::ActionClient<action_server::demoAction>action_client("example_action",true);

    ROS_INFO("waiting for server:");
    bool server_exists = action_client.waitForServer(ros::Duration(5.0));

    if (!server_exists)
    {
        ROS_WARN("can not connect to server;halting");
        return 0;
    }

    ROS_INFO("connected to action server");
    
    while (true)
    {
        /* code */
        g_count++;
        goal.input = g_count;
        action_client.sendGoal(goal, &doneCB);
        
        bool finished_before_timeout = action_client.waitForResult(ros::Duration(5.0));
        //该操作会使得客户端暂停而等待服务器，如果在指定时间内返回，将会触发goalCB函数，此函数接受来自服务器提供的结构消息

        if (!finished_before_timeout)
        {
            /* code */
            ROS_WARN("giving up waiting on result for goal number %d",g_count);
            return 0;
        }else{

        }
        
        return 0;
    }
    
    


}
