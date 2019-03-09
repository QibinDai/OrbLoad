//
// Created by qibin on 19-3-5.
//

#ifndef MAPLOAD_MAPPOINT_H
#define MAPLOAD_MAPPOINT_H

#include <opencv2/opencv.hpp>
using namespace std;
class MapPoint {
public:
    MapPoint(const cv::Mat &Pos, const cv::Mat &Descriptor);
    cv::Mat GetDescriptor();
    cv::Mat GetWorldPos();

private:
    cv::Mat mDescriptor;
    cv::Mat mWorldPos;
};


#endif //MAPLOAD_MAPPOINT_H
