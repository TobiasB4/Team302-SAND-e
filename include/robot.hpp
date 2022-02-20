#pragma once
#include <iostream>
#include <math.h>
#include <list>
#include <string>
#include <fstream>
#include <algorithm>
using std::list;
using std::string;
#define EARTH_RADIUS 6378.8

namespace Map{

    struct Coordinates{
        long double latitude;
        long double longitude;
        long double altitude;


        Coordinates(long double latitude, long double longitude, long double altitude){
            this->latitude = latitude;
            this->longitude = longitude;
            this->altitude = altitude;
        }

    };

    struct Cartesian{
        long double x;
        long double y;
        long double z;

        Cartesian(Coordinates coordinate){
            this->x = ToCartesianX(coordinate.latitude, coordinate.longitude);
            this->y = ToCartesianY(coordinate.latitude, coordinate.longitude);
            this->z = ToCartesianZ(coordinate.latitude);
        }
        inline long double ToCartesianX(long double latitude, long double longitude){return EARTH_RADIUS * cos(latitude) * cos(longitude);}
        inline long double ToCartesianY(long double latitude, long double longitude){return EARTH_RADIUS * cos(latitude) * sin(longitude);}
        inline long double ToCartesianZ(long double latitude){return EARTH_RADIUS * sin(latitude);}
    };

    list<string> ExtractFile(string pathName);
};

namespace Autonomous{

class PathFinding{
    private:
    public:

    static inline long double ToRadian(long double num){return num * M_PI / 180;}
    static long double CalcDistance(Map::Coordinates gps1, Map::Coordinates gps2);
};

class ObstacleDetection{
    private:
    public:
};

class MotorControl{
    private:
    public:
};

};

namespace MainRobot{
    
    class Robot{

    private:
        Map::Coordinates GPSCurr;
        Map::Coordinates GPSNext;
        const float WIDTH;
        const float LENGTH;

    public:
        Robot(float width, float length, Map::Coordinates gps1, Map::Coordinates gps2) : GPSCurr{gps1}, GPSNext{gps2}, WIDTH{width}, LENGTH{length} {}

        void UpdateCurrentGPS(Map::Coordinates newGPS);
        void UpdateNextGPS(Map::Coordinates newGPS);
        Map::Coordinates GetCurrentGPS();
        Map::Coordinates GetNextGPS();
    };

};