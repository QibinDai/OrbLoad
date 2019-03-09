cmake_minimum_required(VERSION 3.6.3)
project(MapLoad)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV 3.0 QUIET)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/execute)
add_executable(MapLoad execute/main.cpp src/MapPoint.cpp src/Map.cpp src/ORBmatcher.cpp src/CarParameterSetting.cpp src/Car.cpp src/ORBextractor.cpp)
target_link_libraries(MapLoad ${OpenCV_LIBS})
#find_package(catkin REQUIRED COMPONENTS
#        roscpp
#        std_msgs
#        sensor_msgs
#        wali
#        cv_bridge
#        )
#include_directories(
#        include
#        ${catkin_INCLUDE_DIRS}
#        ${OpenCV_INCLUDE_DIRS}
#)
add_executable(CarDetect execute/CarDetectK.cpp src/MapPoint.cpp src/Map.cpp src/ORBmatcher.cpp src/CarParameterSetting.cpp src/Car.cpp src/ORBextractor.cpp)
#add_dependencies(CarDetect ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(CarDetect ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )
