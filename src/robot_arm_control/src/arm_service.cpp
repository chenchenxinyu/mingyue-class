#include <ros/ros.h>
#include <robot_arm_message/robarm_server.h>
#include <std_msgs/Bool.h>
#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
using namespace std;

float x, y, z, L, H, theta0, theta1, theta2, theta3;
float length, height, alpha;
bool valid, state;
const float MAXL = 3.0;
const float MAXH = 4.0;
const float Rad_to_deg = 45.0 / atan(1.0);
const float L1 = 1.0;
const float L2 = 1.0;
const float L3 = 1.0;
const float L4 = 1.0;

float calculate_theta0(float x, float y)
{
    theta0 = atan2(y, x);
    // cout<<"theta0:"<<theta0*Rad_to_deg<<endl;//����Ƕ�
    return theta0;
}

float calculate_theta2(float L, float H)
{
    float test = (L * L + H * H - L2 * L2 - L3 * L3) / 2 * L2 * L3;
    if (test > 1 or test < -1)
    {
        state = false;
    }

    theta2 = acos(test);
    // cout<<"theta2:"<<theta2*Rad_to_deg<<endl;//����Ƕ�  ����ֵ�Ի��ȴ����������
    return theta2;
}

float calculate_theta1(float L, float H, float theta2)
{
    float k1, k2, w;
    k2 = L3 * sin(theta2);
    k1 = L2 + L3 * cos(theta2);
    w = atan2(k2, k1);
    theta1 = atan2(L, H) - w;
    // cout<<"theta1: "<<theta1*Rad_to_deg<<endl;
    return theta1;
}

float calculate_theta3(float theta1, float theta2, float alpha)
{
    theta3 = alpha / Rad_to_deg - theta1 - theta2;
    // cout<<"theta3:"<<theta3*Rad_to_deg<<endl;
    return theta3;
}

bool if_out_range(float height, float length)
{
    if (height > MAXH)
    {
        cout << "too high" << endl;
        state = false;
        //response.state = false;
        return false;
    }
    if (length > MAXL)
    {
        cout << "too far" << endl;
        state = false;
        //response.state = false;
        return false;
    }
    return true;
}
bool if_range_deg(float num, float theta)
{
    float degree;
    degree = theta * Rad_to_deg;
    if (num == 0)
    {
        if (0 <= degree <= 360)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        degree = 90 - degree;
        if (0 <= degree <= 180)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

float get_xyz(float x, float y, float z, float alpha)
{
    valid = false;
    theta0 = calculate_theta0(x, y);
    height = z;
    length = sqrt(x * x + y * y);

    if (if_out_range(height, length) == true and if_range_deg(0, theta0) == true)
    {
        L = length - L4 * sin(alpha / Rad_to_deg);
        H = height - L1 - L4 * cos(alpha / Rad_to_deg);
        theta2 = calculate_theta2(L, H);
        if (if_range_deg(2, theta2) == true)
        {
            theta1 = calculate_theta1(L, H, theta2);
            if (if_range_deg(1, theta1) == true)
            {
                theta3 = calculate_theta3(theta1, theta2, alpha);
                if (if_range_deg(3, theta3) == true)
                {
                    valid = true;
                }
            }
        }
    }
    return valid, theta0, theta1, theta2, theta3;
}

float back_work(float x, float y, float z, float alpha)
{
    cout << "x:" << x << " y:" << y << " z:" << z << " alpha:" << alpha << endl;
    if (z < 0)
    {
        cout << "z is not allow!" << endl;
    }
    if (y < 0)
    {
        cout << "y is not allow" << endl;
    }
    valid = false;
    state = true;
    while (alpha > 90 and valid == false and state == true)
    {
        valid, theta0, theta1, theta2, theta3 = get_xyz(x, y, z, alpha);
        if (valid == false or state == false)
        {
            alpha = alpha - 0.1;
            state = true;
            valid = false;
        }
    }
    cout << "result:" << theta0 * Rad_to_deg << " " << 90 - theta1 * Rad_to_deg << " " << 90 - theta2 * Rad_to_deg << " " << 90 - theta3 * Rad_to_deg << " " << alpha << endl;
    //这个theta输出只是为了变成角度和便于理解，实际运算之中直接利用不变的弧度之计算即可，它的正解是得到验证的
    return valid, theta0, theta1, theta2, theta3;
}

float forward_work(float theta0, float theta1, float theta2, float theta3)
{
    /*theta0 = theta0*Rad_to_deg;
    theta1 = theta1*Rad_to_deg;
    theta2 = theta2*Rad_to_deg;
    theta3 = theta3*Rad_to_deg;*/
    float lent = L2 * sin(theta1) + L3 * sin(theta1 + theta2) + L4 * sin(theta1 + theta2 + theta3);
    float x1, y1, z1;
    x1 = lent * cos(theta0);
    y1 = lent * sin(theta0);
    z1 = L1 + L2 * cos(theta1) + L3 * cos(theta1 + theta2) + L4 * cos(theta1 + theta2 + theta3);
    //cout << x1 << endl;
    //cout << y1 << endl;
    //cout << z1 << endl;
    if (abs(x1 - x) > 0.5 or abs(y1 - y) > 0.5 or abs(z1 - z) > 0.5)
    {
        // state = false;
        // ROS_INFO("dco down");
        if(state = false)
        {
            ROS_INFO("something wrong in the calcuate work!");
        }else{
            ROS_INFO("pass the dco");
            state = true;
        }        
        
    }
    else
    {
        if(state = false)
        {
            ROS_INFO("something wrong in the calcuate work!");
        }else{
            ROS_INFO("pass the dco");
            state = true;
        }


    }
    return x1, y1, z1;
}

void work(float x, float y, float z)
{
    valid, theta0, theta1, theta2, theta3 = back_work(x, y, z, alpha);
    if (valid == true)
    {
        /* code */
        float x1, y1, z1;
        x1, y1, z1 = forward_work(theta0, theta1, theta2, theta3);
        /*if (abs(x1 - x) > 0.5 or abs(y1 - y) > 0.5 or abs(z1 - z) > 0.5)
        {
            state = false;
            cout << x << "~~~~~~" << x1 << endl;
            cout << "error��try again" << endl;
            alpha = alpha - 0.1;
            // work(x,y,z);
        }
        else
        {
            cout << "right" << endl;
        }*/
    }
}

///////////////////////*********************************/////////////////////////////////////

bool callback(robot_arm_message::robarm_serverRequest& request,robot_arm_message::robarm_serverResponse& response)
{    
    ROS_INFO("callback success");
    float x = request.xyz_vector[0];
    float y = request.xyz_vector[1];
    float z = request.xyz_vector[2];

    ROS_INFO("started work");
    alpha = 180;
    state = true;
    response.state = true;
    work(x,y,z);
    if (state==true)
    {
        response.state = true;
    }else{
        response.state = false;
    }
    
    response.theta_vector[0] = theta0;
    response.theta_vector[1] = theta1;
    response.theta_vector[2] = theta2;
    response.theta_vector[3] = theta3;
    //response.time.stamp = ros::Time::now();
    ROS_INFO("get theta,start controller work");
    //至此得到角度，还需要将运动电机的命令添加在回调函数中,发布节点信息即可
    //ROS_INFO("send state to gazebo controller");
    return true;

}

int main(int argc,char **argv)
{
    ros::init(argc,argv,"arm_contorl_node");
    ros::NodeHandle n;//服务相关的通信链条
    //ros::NodeHandle nh;//节点相关的通信链条
    // ros::Publisher ArmGazebo = n.advertise<std_msgs::Bool>("BoolGazebo",1);//发布一个话题为“BoolGazebo”，消息类型bool，进行传参
    // std_msgs::Bool ArmGazeboBool;
    // ArmGazeboBool.data = false;
    //ROS_INFO("init node controller,and start server");
    ros::ServiceServer service = n.advertiseService("control_arm",callback);
    ros::spin();
    return 0;
}