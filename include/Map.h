//
// Created by qibin on 19-3-5.
//

#ifndef MAPLOAD_MAP_H
#define MAPLOAD_MAP_H

#include <set>
#include <fstream>
#include "MapPoint.h"

class Map {
public:
    void AddMapPoint(MapPoint* pMP);
    void Load(const std::string& filename);
    MapPoint* LoadMapPoint( ifstream &f );
    vector<MapPoint*> GetAllMapPoints();
    void WritePoint();
private:
    std::set<MapPoint*> mspMapPoints;
};


#endif //MAPLOAD_MAP_H
