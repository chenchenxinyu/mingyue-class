#include <ros/ros.h>
#include <actionlib/server/action_server.h> //依赖的库，其中包含一些关键字和函数
#include <action_server/demoAction.h>

int g_count = 0;
bool g_count_failure = false;
//声明类
class ActionServer
{
private:
    /* data */
    ros::NodeHandle nh_;
    //动作服务器自己的类
    actionlib::ActionServer<action_server::demoAction> as_;  //对类的定义，其中包含的库中ActionServer类的对象，并且简写为as_
    action_server::demoGoal goal_; //类ActionServer的原型也包含了三个消息对象，这里声明
    action_server::demoResult result_;//声明的名称为result_，类型为demoResult的变量，随后可以引用  38行
    action_server::demoFeedback feedback_;

public:
    ActionServer();//类中的构造函数，其中包含回调函数executeCB
    ~ActionServer(void){
        };
    void executeCB(const actionlib::ActionServer<action_server::demoAction>::GoalConstPtr& goal);
    /*
    该回调函数和ActionServer的as_相关联，参数是指向目标消息的指针
    目标消息的声明是actionlib库、模板化的类ActionServer、action_server::demoAction(进一步具有自动生成类型的GoalConstPtr)引用的消息类型
    */
};


//构造函数
ActionServer::ActionServer():
    as_(nh_,"example_action",boost::bind(&ActionServer::executeCB,this,_1),false)
    /* 
    服务器名称应该修改为更合适的名称
    构造函数的第一行负责初始化对象as_，ROS将会知道新的动作服务器，同时指定了我们希望使用的成员类函数executeCB
    boost::bind中，在类ActionServer的命名空间中定义了回调函数executeCB，this表示这个是当前对象的一个成员，
    _1表示回调函数采用一个参数
    false表示目前我们还不希望启动新的动作服务器
    */
{
    ROS_INFO("in constructor of example action server...");
    as_.start();//启动新的动作服务器
}

//回调函数
//服务器的核心在于回调函数，通过修改回调函数实现更多的功能和需求，以及消息的传递
void ActionServer::executeCB(const actionlib::ActionServer<action_server::demoAction>::GoalConstPtr& goal){
    g_count++;
    result_.output = g_count;
    result_.goal_stamp = goal->input;//目标消息的input字段输入到goal_stamp字段
    if (g_count != goal->input)
    {
        ROS_WARN("hey--mismatch");
        ROS_INFO("g_count=%d;goal_stamp = %d",g_count,result_.goal_stamp);
        g_count_failure = true;
        ROS_WARN("informing client of aborted goal");
        as_.setAborted(result_);//结束回调函数
    }
    else{
        as_.setSucceeded(result_);//另一种结束的方法
        //客户端只接受result_的字段内容
    }
    
}

//主程序
int main(int argc, char** argv)
{
    ros::init(argc,argv,"action_serve_node");//节点名称应该修改为更有助益记忆的名称
    ROS_INFO("get into the action server");
    ActionServer as_object;//实例化类对象

    ROS_INFO("going into spin");
    while (!g_count_failure && ros::ok())
    {
        ros::spinOnce();
    }

    return 0;
    
}