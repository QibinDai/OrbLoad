//
// Created by qibin on 19-3-5.
//

#ifndef MAPLOAD_CARPARAMETERSETTING_H
#define MAPLOAD_CARPARAMETERSETTING_H

#include <opencv2/opencv.hpp>
using namespace std;
class CarParameterSetting {

public:
    CarParameterSetting(const std::string &strSettingPath);

    float width;
    float height;
    float fx;
    float fy;
    float cx;
    float cy;
    float invfx;
    float invfy;
    float bf;
    float b;
    float fps;
    cv::Mat K;
    cv::Mat DistCoef;
    bool initialized;

    //Camera RGB parameters
    int nRGB;

    //ORB feature parameters
    int nFeatures;
    float fScaleFactor;
    int nLevels;
    float fIniThFAST;
    float fMinThFAST;

    //other parameters
    float ThDepth = -1;
    float DepthMapFactor = -1;

};


#endif //MAPLOAD_CARPARAMETERSETTING_H
