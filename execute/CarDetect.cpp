#include <librealsense/rs.hpp>

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

void LoadImages(const string &strAssociationFilename, vector<string> &vstrImageFilenamesRGB,
                vector<string> &vstrImageFilenamesD, bool &bColorVideo);

int main(int argc, char **argv) {
    string carParamterFile = "MYPARAM.yaml";
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
    rs::context ctx;
    printf("There are %d connected RealSense devices.\n", ctx.get_device_count());
    if (ctx.get_device_count() == 0) return EXIT_FAILURE;

    // This tutorial will access only a single device, but it is trivial to extend to multiple devices
    rs::device *dev = ctx.get_device(0);
    printf("\nUsing device 0, an %s\n", dev->get_name());
    printf("    Serial number: %s\n", dev->get_serial());
    printf("    Firmware version: %s\n", dev->get_firmware_version());

    // Configure all streams to run at VGA resolution at 60 frames per second
    dev->enable_stream(rs::stream::color, 640, 480, rs::format::rgb8, 60);
    dev->start();
    //char key = 0;
    while (true) {
        cv::Mat imRGB(480, 640, CV_8UC3);
        //cv::imshow("ok",imRGB);
        dev->wait_for_frames();
        memcpy(imRGB.data, dev->get_frame_data(rs::stream::color), 480 * 640 * sizeof(uint8_t) * 3);
        car->LoadPhoto(imRGB);
        if (cv::waitKey(200) == 'q') {
            break;
        }
    }

    return 0;
}


void LoadImages(const string &strAssociationFilename, vector<string> &vstrImageFilenamesRGB,
                vector<string> &vstrImageFilenamesD, bool &bColorVideo) {
    ifstream fAssociation;
    fAssociation.open(strAssociationFilename.c_str());
    string s;
    getline(fAssociation, s);
    bColorVideo = (s[0] == '1');
    while (!fAssociation.eof()) {
        getline(fAssociation, s);
        if (!s.empty()) {
            stringstream ss;
            ss << s;
            string sRGB, sD;
            if (!bColorVideo) {
                ss >> sRGB;
                vstrImageFilenamesRGB.push_back(sRGB);
            }
            ss >> sD;
            vstrImageFilenamesD.push_back(sD);
        }
    }
}
