//
// Created by qibin on 19-3-5.
//

#ifndef MAPLOAD_ORBMATCHER_H
#define MAPLOAD_ORBMATCHER_H

#include<vector>
#include <opencv2/opencv.hpp>

#include"MapPoint.h"
class ORBmatcher {
public:

    ORBmatcher(float nnratio=0.6, bool checkOri=true);

    // Computes the Hamming distance between two ORB descriptors
    static int DescriptorDistance(const cv::Mat &a, const cv::Mat &b);

protected:

    float mfNNratio;
    bool mbCheckOrientation;
};


#endif //MAPLOAD_ORBMATCHER_H
