#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;
//三角函数计算全部采用弧度，只有显示的时候采用角度。
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
    // cout<<"theta0:"<<theta0*Rad_to_deg<<endl;//输出角度
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
    // cout<<"theta2:"<<theta2*Rad_to_deg<<endl;//输出角度  但是值以弧度代入后续计算
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
        return false;
    }
    if (length > MAXL)
    {
        cout << "too far" << endl;
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
        state = false;
        cout << x << "~~~~~~" << x1 << endl;
        cout << "error、try again" << endl;
        alpha = alpha - 0.1;
        // work(x,y,z);
    }
    else
    {
        cout << "right" << endl;
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
            cout << "error、try again" << endl;
            alpha = alpha - 0.1;
            // work(x,y,z);
        }
        else
        {
            cout << "right" << endl;
        }*/
    }
}

int main()
{
    cout << "Hello, the work is started" << endl;
    x = 0;
    y = pow(2, 0.5) + 1;
    z = 1.0;
    alpha = 180; //开始迭代的较大初值  我希望它可控 用state来控制
    state = true;
    work(x, y, z);
    cout << "work over!" << endl;
    return 0;
}

/* 按照弧度制进行计算
int main()
{
    theta0 = 0;
    theta1 = 135/Rad_to_deg;
    theta2 = 135/Rad_to_deg;
    theta3 = 135/Rad_to_deg;
    x,y,z = forward_work(theta0,theta1,theta2,theta3);
    return 0;
}
*/

// 450>1+2+3>360  在这个区间内进行迭代

