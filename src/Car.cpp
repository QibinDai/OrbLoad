//
// Created by qibin on 19-3-5.
//

# include "../include/Car.h"
# define isPrint  true
Car::Car(CarParameterSetting *carParameterSetting,Map *inputMap):parameter(carParameterSetting),map(inputMap) {
    mpIniORBextractor = new ORBextractor(2000, 1.2, 8, 20, 7);
}

void Car::LoadPhoto(cv::Mat &imRGB) {
    vector<cv::KeyPoint> mPhotoKeyPoints;
    cv::Mat mPhotoDescriptors;
    cv::cvtColor(imRGB,imRGB,cv::COLOR_RGB2GRAY);
    (*mpIniORBextractor)(imRGB, cv::Mat(), mPhotoKeyPoints, mPhotoDescriptors);
    //cerr<<"pic load!!"<<mPhotoDescriptors<<endl;
    ORBmatcher matcher(0.6, false);
    vector<cv::Point2f> img_point;
    vector<cv::Point3f> obj_point;
    //cout<<"point::"<<all_map_points.size();
//    cerr <<"point::"<<map->GetAllMapPoints().size();
    for (int i = 0; i < mPhotoKeyPoints.size(); i++) {
        int minDistance = 999;
        cv::Point3f min_obj_point;

        for (auto &mapPoint : map->GetAllMapPoints()) {
            //if(!mapPoint->isBad()) {
                auto pos = mapPoint->GetWorldPos();
                auto des = mapPoint->GetDescriptor();
                int distance = matcher.DescriptorDistance(des, mPhotoDescriptors.row(i));
                if (distance < minDistance) {
                    minDistance = distance;
                    min_obj_point = cv::Point3f(pos.at<float>(0, 0), pos.at<float>(1, 0), pos.at<float>(2, 0));
                }
            //}
        }
        if (minDistance < 30) {
            img_point.push_back(mPhotoKeyPoints[i].pt);
            obj_point.push_back(min_obj_point);
        }
    }
    if(!isPrint)
        cout<<"t "<<img_point.size()<<endl;
    cerr <<"point::"<<img_point.size()<<endl;
    if (img_point.size() > 3) {
        cv::Mat r, t;
        vector<int> inliers;
        cv::solvePnPRansac(obj_point, img_point, parameter->K, parameter->DistCoef, r, t, false, 1000, 8.0, 0.99, inliers);
        //if(inliers.size()>img_point.size()*0.7)
        {
            cv::Mat R;
            cv::Rodrigues(r, R);
            cv::Mat Tcw = cv::Mat::eye(4, 4, R.type());
            R.copyTo(Tcw.rowRange(0, 3).colRange(0, 3));
            t.copyTo(Tcw.rowRange(0, 3).col(3));
            cv::Mat ow = -R.inv() * t;
            //cout << "\ncamera pose:\n" << invrt;
            //R的第i行 表示摄像机坐标系中的第i个坐标轴方向的单位向量在世界坐标系里的坐标
            //2、R的第i列 表示世界坐标系中的第i个坐标轴方向的单位向量在摄像机坐标系里的坐标
            //3、t 表示世界坐标系的原点在摄像机坐标系的坐标
            //4、-R的转置 * t 表示摄像机坐标系的原点在世界坐标系的坐标
            if(isPrint){
                cerr << ow.at<double>(0, 0) << " " << ow.at<double>(1, 0) << " "
                     << ow.at<double>(2, 0)
                     << " 1 0 0"
                     << endl;
            }
        }
    }
}
