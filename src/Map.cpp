//
// Created by qibin on 19-3-5.
//

#include "../include/Map.h"

void Map::AddMapPoint(MapPoint *pMP)
{
    mspMapPoints.insert(pMP);
}

void Map::Load(const std::string &filename) {
    cerr << "Map reading from:"<<filename<<endl;
    ifstream f;
    f.open( filename.c_str() );

    //按照保存的顺序，先读取MapPoints的数目；
    unsigned long int nMapPoints;
    f.read((char *) &nMapPoints, sizeof(nMapPoints));
    //依次读取每一个MapPoints，并将其加入到地图中
    cerr << "The number of MapPoints:" << nMapPoints << endl;
    for (unsigned int i = 0; i < nMapPoints; i++) {
        MapPoint *mp = LoadMapPoint(f);
        AddMapPoint(mp);
    }

}

MapPoint* Map::LoadMapPoint( ifstream &f ) {
    //主要包括MapPoints的位姿和ID；
    cv::Mat Position(3,1,CV_32F);
    long unsigned int id; f.read((char*)&id, sizeof(id));
    f.read((char*)&Position.at<float>(0), sizeof(float));
    f.read((char*)&Position.at<float>(1), sizeof(float));
    f.read((char*)&Position.at<float>(2), sizeof(float));

    cv::Mat Descriptors(1, 32, CV_8UC1);
    for ( int i = 0; i < 32; i ++ )
        f.read((char*)&Descriptors.at<unsigned char>(0,i),sizeof(char));

    //初始化一个MapPoint，并设置其ID和Position；
    MapPoint* mp = new MapPoint(Position, Descriptors );
    return mp;
}

vector<MapPoint*> Map::GetAllMapPoints() {
    return vector<MapPoint*>(mspMapPoints.begin(),mspMapPoints.end());
}

void Map::WritePoint(){
    for(MapPoint* mapPoint:mspMapPoints){
        //cout<<mapPoint->GetWorldPos()<<endl;
        auto pos = mapPoint->GetWorldPos();
        cout << pos.at<float>(0, 0) << " " << pos.at<float>(1, 0) << " " << pos.at<float>(2, 0) << " 0 1 0" << endl;
    }
}
