#include <ros/ros.h>
#include <iostream>
#include <list>
#include <std_msgs/Float64.h>
#include <robot_arm_message/pathlist.h>
using namespace std;

float x[100] ={0.0, 0.0006000112768178879, 0.0046874328050191, 0.015203550901943952, 0.03407499381919043, 0.06188946594912501, 0.097762139048402, 0.1394122707981449, 0.1834400413669897, 0.22576541291907906, 0.26216798485165205, 0.2888525468714728, 0.30296132845817164, 0.30296132845817164, 0.2888525468714729, 0.2621679848516522, 0.22576541291907923, 0.18344004136698988, 0.13941227079814494, 0.09776213904840196, 0.0618894659491249, 0.034074993819190325, 0.015203550901943868, 0.004687432805019053, 0.0006000112768178728, -5.3964057497138536e-46, -0.0006000112768179075, -0.004687432805019185, -0.01520355090194415, -0.03407499381919077, -0.06188946594912554, -0.09776213904840272, -0.1394122707981456, -0.1834400413669905, -0.2257654129190798, -0.2621679848516527, -0.28885254687147327, -0.30296132845817186, -0.3029613284581714, -0.28885254687147227, -0.2621679848516512, -0.22576541291907798, -0.18344004136698847, -0.13941227079814364, -0.09776213904840077, -0.06188946594912393, -0.0340749938191896, -0.015203550901943422, -0.004687432805018841, -0.0006000112768178178, -0.42857142857142855, -0.3885714285714285, -0.34857142857142853, -0.30857142857142855, -0.2685714285714285, -0.22857142857142854, -0.18857142857142853, -0.14857142857142855, -0.10857142857142854, -0.0685714285714285, -0.02857142857142847, 0.011428571428571566, 0.0514285714285716, 0.09142857142857164, 0.13142857142857167, 0.1714285714285717, 0.21142857142857174, 0.2514285714285718, 0.2914285714285718, 0.33142857142857185, 0.3714285714285719, 0.4114285714285719, 0.45142857142857196, 0.491428571428572, 0.531428571428572, 0.42857142857142855, 0.446476176223472, 0.4640985553092649, 0.4811606503835254, 0.4973933820145307, 0.5125407503274961, 0.5263638722755268, 0.5386447489679699, 0.5491897036431449, 0.5578324360665742, 0.5644366451850219, 0.5688981786755269, 0.5711466754897531, 0.5711466754897531, 0.5688981786755269, 0.5644366451850219, 0.5578324360665742, 0.549189703643145, 0.5386447489679699, 0.526363872275527, 0.5125407503274961, 0.49739338201453076, 0.48116065038352546, 0.464098555309265, 0.44647617622347213} ;
float z[100] ={0.09523809523809523, 0.10130886970713696, 0.11840540275487745, 0.14338861098629999, 0.1716771641558417, 0.1980797512023699, 0.2177067093265455, 0.22677730067881083, 0.22316758447485646, 0.20660568335109292, 0.17850138844045724, 0.14147665679223356, 0.09872437578088164, 0.05335144690269034, 0.007853392808522703, -0.03617498929760785, -0.07805325427188625, -0.11778394837679725, -0.15566556510483465, -0.191871962520149, -0.22612043605950485, -0.2575192473303146, -0.28463179790578097, -0.30573341019100386, -0.3191840120190234, -0.32380952380952377, -0.31918401201902324, -0.30573341019100353, -0.28463179790578047, -0.257519247330314, -0.22612043605950424, -0.19187196252014824, -0.15566556510483404, -0.11778394837679665, -0.0780532542718856, -0.03617498929760721, 0.00785339280852347, 0.05335144690269126, 0.09872437578088263, 0.14147665679223445, 0.17850138844045804, 0.20660568335109358, 0.22316758447485677, 0.22677730067881077, 0.21770670932654507, 0.1980797512023691, 0.17167716415584064, 0.14338861098629907, 0.11840540275487663, 0.10130886970713644, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.14285714285714285, 0.14173067161635397, 0.13836902301837586, 0.1328252122697502, 0.1251866685776948, 0.11557385633927822, 0.10413837534591594, 0.09106056996409856, 0.07654668499699956, 0.060825613080724705, 0.044145284910706815, 0.026768759226532133, 0.008970074218473382, -0.008970074218473295, -0.02676875922653205, -0.04414528491070674, -0.06082561308072462, -0.07654668499699947, -0.09106056996409848, -0.10413837534591588, -0.11557385633927815, -0.12518666857769475, -0.13282521226975016, -0.13836902301837584, -0.14173067161635397} ;
float y[100] ={2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0} ;

// list<float> x = {0.0, 0.01592017311657953, 0.12546207596059317, 0.41293484142614145, 0.9448637638349007, 1.7631265168342183, 2.880319157227644, 4.277774780256797, 5.906420368589667, 7.690403394594479, 9.533171785455286, 11.325471097310217, 12.954550804786123, 14.31376286174221, 15.311699849515877, 15.880060309909043, 15.979541671841423, 15.60323645474055, 14.777229520762285, 13.558343222639515, 12.029231114703876, 10.291256797849076, 8.45579139178156, 6.63470348856783, 4.930886711217185, 3.42966582214851, 2.19184308035914, 1.2489993194256055, 0.6014621695177305, 0.21911503023905346, 0.04496615575137913, 0.0011502551712372004, -0.003182596239039216, -0.06280475461769829, -0.26699447394780945, -0.6906156923887675, -1.3865003992722789, -2.379823338085984, -3.664980588653955, -5.205259574531588, -6.935338271693431, -8.766398167309747, -10.593401457847627, -12.303888997544242, -13.787518945503088, -14.945499118187646, -15.69907472137799, -15.99631664576088, -15.816606412227204, -15.172418676063739, -14.108242656586153, -12.696738480455272, -11.03247047783966, -9.22377498119011, -7.383485905078039, -5.619342537368272, -4.024931520141895, -2.671966490845133, -1.6045886310825972, -0.8361901787981304, -0.34903699130042515, -0.0967156927582269, -0.009178186863471861};
// float y = 0.5;
// list<float> z = {5.0, 5.2029872871540315, 5.788182602755194, 6.687118593066485, 7.794743388649621, 8.981734208445882, 10.10937212636987, 11.045027270065518, 11.676267039896839, 11.921842761352345, 11.73829277308603, 11.121547574605385, 10.103637235131831, 8.745276476064275, 7.125640325217571, 5.330967416893555, 3.4436972034199202, 1.53365956127969, -0.34757221575692887, -2.1686112219140465, -3.9165313102869184, -5.592123871744802, -7.20322234428281, -8.757432220809005, -10.255627992503817, -11.687377036019882, -13.029063733996283, -14.24498401200806, -15.291147376829196, -16.121050070224456, -16.692347324020766, -16.973209090042378, -16.94721353323193, -16.61590162099761, -15.998536643680852, -15.129111568712705, -14.051138815880739, -12.811156620883905, -11.452124217483362, -10.007912109538974, -8.49991533932546, -6.936454275244445, -5.3151379904362965, -3.6278308820274847, -1.8673739096113144, -0.03485211804061539, 1.8539653285822388, 3.764323458989577, 5.641340429414061, 7.412574840549962, 8.994259820308429, 10.300549632901626, 11.2545865902463, 11.799821368866386, 11.909873675169518, 11.59533351724621, 10.906267326894108, 9.929759889617477, 8.782512164936742, 7.599225812350802, 6.5181315089671905, 5.665464812422532, 5.140890849881259};
// list<float>::iterator plx;
int num = 100;

int main(int argc, char **argv)
{
    ros::init(argc,argv,"path_pub");
    ros::NodeHandle n;
    ros::Publisher PathList = n.advertise<robot_arm_message::pathlist>("path",1);
    robot_arm_message::pathlist pathlistdata;
    ros::Rate naptime(1);
    //频率f  每次发送的周期T=1/f  点数据发布时间间隔要长于订阅者，保证数据全部被收到
    //订阅者进行解算角度，并且发布到gazebo和舵机中，舵机执行程序的订阅时间间隔要短于发布者，保证发布者每个信息被收到
    //f：1 3 10
    while (ros::ok())
    {
        cout<<"send path list started!"<<endl;
        for(int i = 0;i<num;i++){
            pathlistdata.pathlistdata[0] = x[i]*1.2;
            pathlistdata.pathlistdata[1] = y[i]*1.2;
            pathlistdata.pathlistdata[2] = (z[i]+5/14)*1.2;
            cout<<"num is "<<i<<endl;
            cout<<"px-data:"<<x[i]<<endl;
            cout<<"py-data:"<<y[i]<<endl;
            cout<<"pz-data:"<<z[i]<<endl;
            PathList.publish(pathlistdata);
            naptime.sleep();
        }
        
    }
    
}