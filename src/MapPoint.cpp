//
// Created by qibin on 19-3-5.
//

#include "../include/MapPoint.h"

MapPoint::MapPoint(const cv::Mat &Pos, const cv::Mat &Descriptor){
    Pos.copyTo(mWorldPos);
    Descriptor.copyTo(mDescriptor);
}
cv::Mat MapPoint::GetDescriptor()
{
    return mDescriptor.clone();
}

cv::Mat MapPoint::GetWorldPos()
{
    return mWorldPos.clone();
}