//
// Created by qibin on 19-3-5.
//

#ifndef MAPLOAD_CAR_H
#define MAPLOAD_CAR_H


#include "CarParameterSetting.h"
#include "../include/ORBextractor.h"
#include "../include/ORBmatcher.h"
#include "../include/Map.h"
class Car {
public:
    Car(CarParameterSetting* carParameterSetting,Map *inputMap);
    void LoadPhoto(cv::Mat &imRGB);

protected:
    CarParameterSetting *parameter;
    ORBextractor* mpIniORBextractor;
    Map* map;
};


#endif //MAPLOAD_CAR_H
