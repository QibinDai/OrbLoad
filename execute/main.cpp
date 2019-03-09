#include <iostream>
#include "../include/Map.h"
int main() {
    string carParamterFile = "";
    string mapLoadFile  = "../MapPointandKeyFrame.bin";


    Map* map = new Map();
    map->Load(mapLoadFile);
    map->WritePoint();
    return 0;
}