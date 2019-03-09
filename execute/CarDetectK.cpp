#include "ros/ros.h"
#include "wali/RGBD_Image.h" // py has built
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp> // ros opencv 3.3.1
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>


#include "../include/Car.h"

#define isPrint  true
#define isWait false
#define orbRun false
using namespace std;

int main(int argc, char **argv) {
    string carParamterFile = "xiaoche.yaml";
    string mapLoadFile  = "../MapPointandKeyFrame.bin";
    //待标定相机照相txt
    //string photo_url = "../default/xiaoche.yaml";
    //string poseFittingText = "../default/poseFittingText.txt";
    if (argc == 3) {
        carParamterFile = argv[1];
        mapLoadFile = argv[2];
    }
    Map* map = new Map();
    map->Load(mapLoadFile);
    CarParameterSetting *setting = new CarParameterSetting(carParamterFile);
    Car *car = new Car(setting,map);
    if(isWait) {
        cout<< "ready,press c to continue"<<endl;
        char key = 0;
        do {
            cin >> key;
        } while (key != 'c');
    }


    //SLAM.SaveTrajectoryTUM("/home/qibin/桌面/b.txt");
    //计算小车的位置
    ros::init(argc, argv, "rgbd_cpp_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<wali::RGBD_Image>("get_rgbd_image");
    wali::RGBD_Image srv;
    srv.request.start = true;

    cv_bridge::CvImagePtr cv_ptr_rgb;

    while (ros::ok()) {
        if (client.call(srv)) {
            //ROS_INFO("I got it!");
            // cvt ros::sensor_msgs/Image to cv::Mat
            // in the beginning, not get both rgb and depth, just wait a moment
            cv_ptr_rgb = cv_bridge::toCvCopy(srv.response.rgb);

            if (cv_ptr_rgb->image.rows > 0) { // both have rgb and depth
                //cv::imshow("rgb", cv_ptr_rgb->image); // rgb
                //cv::waitKey(0);
                car->LoadPhoto(cv_ptr_rgb->image);
                // your code here

                //char c = 0;
                //cin>>c;
                if (cv::waitKey(200) == 'q') {
                    break;
                }
            }
        } else {
            ROS_ERROR("Failed to call service get_rgbd_image");
            return 1;
        }
    }

    return 0;
}