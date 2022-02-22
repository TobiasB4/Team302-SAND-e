#pragma once
#include <iostream>
#include <math.h>
#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include <tuple>
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

    // Splits string into substrings separated by delimiter
    // return: Array of split substrings
    void Tokenize(string s,long double (&arr)[2] , string del = " ");

    // Extracts coordinates from txt file
    // return: Tuple of all x-coordinates and y-coordinates [x,y]
    std::tuple<list<long double>,list<long double>> ExtractFile(string pathName);
};

namespace Autonomous{

class PathFinding{
    private:
    public:

    // Converts degrees to radians
    // return: Radian representation of angle
    static inline long double ToRadian(long double num){return num * M_PI / 180;}
    
    // Calculates the distance between two points using the Haversine Formula
    // return: Absolute value of the distance between two points in meters
    static long double CalcDistance(Map::Coordinates gps1, Map::Coordinates gps2);

    // Calculates the equation of the line between two points
    // return: Array: y=mx+b => {m,b}
    static void LineEquation(Map::Coordinates gps1, Map::Coordinates gps2, long double (&returnArr)[2]);

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