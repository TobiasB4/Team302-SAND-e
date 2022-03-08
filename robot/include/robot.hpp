#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include "template.hpp"
#include <string>
#include <fstream>
#include <algorithm>
#include <tuple>
using std::vector;
using std::string;
#define EARTH_RADIUS 6378.8 // in km

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

    struct XY_Pair{
        vector<Map::Coordinates> gps = {};
        long double slopeIntercept[2];

        XY_Pair(vector<Map::Coordinates> coordinates, long double slope = 0.L, long double y_intercept = 0.L){
            this->gps = coordinates;
            this->slopeIntercept[0] = slope;
            this->slopeIntercept[1] = y_intercept;
        }
    };

    // Splits string into substrings separated by delimiter
    // return: Array of split substrings
    void Tokenize(string s,long double (&arr)[2] , string del = " ");

    // Extracts coordinates from txt file
    // return: Tuple of all x-coordinates and y-coordinates [x,y]
    vector<Map::Coordinates> ExtractFile(string pathName);
};

namespace Autonomous{

class PathFinding{
    private:
    public:

    // Converts degrees to radians
    // return: Radian representation of angle
    static inline long double ToRadian(long double num){return num * M_PI / 180;}
    static inline long double ToDegree(long double num){return num * 180 / M_PI;}
    static inline long double Round_12(long double num){return floor(num*1e12+0.5)/1e12;}
    
    // Calculates the distance between two points using the Haversine Formula
    // return: Absolute value of the distance between two points in meters
    static long double CalcDistance(Map::Coordinates gps1, Map::Coordinates gps2);

    // Calculates new longitude value from projected gps coordinate and a point
    // return: new coordinates for the new position
    static Map::Coordinates CalcPosition(Map::Coordinates source, long double range, long double bearing);

    // Calculates bearing between two points
    // return: Bearing from source to destination in degrees
    static long double CalcBearing(Map::Coordinates source, Map::Coordinates destination);

    // Calculates the equation of the line between two points
    // return: Array: y=mx+b => {m,b}
    static void LineEquation(Map::Coordinates gps1, Map::Coordinates gps2, long double (&returnArr)[2]);

    // Finds the highest point along coast line and beach line
    // return: The index of the peak and -1 if not found
    static int FindPeak(vector<long double> height, bool reverse = false);

    // Divide line into subsections of length X meters apart 
    // return: list of (x,y) pairs along the line
    static Map::XY_Pair SubDivideLine(Map::Coordinates gps1, Map::Coordinates gps2, long double x);

    // Create more points inside polygon bounded by polygon's edges
    // return: List of all new points created within the boundary of the polygon with no slope value
    static Map::XY_Pair CreatePoints(Map::Coordinates source, Map::Coordinates boundary1 , Map::Coordinates boundary2, long double const SUBDIVISION);

    static void DrawMap(Map::XY_Pair coordinateList, long double const SUBDIVISION);
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