#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include "template.hpp"
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
using std::vector;
using std::string;
#define EARTH_RADIUS 6378.8 // in km

namespace Map{

    struct Coordinates{
        long double latitude;
        long double longitude;
        long double altitude;

        Coordinates() = default;
        Coordinates(long double latitude, long double longitude, long double altitude){
            this->latitude = latitude;
            this->longitude = longitude;
            this->altitude = altitude;
        }

    };


    // Splits string into substrings separated by delimiter
    // s: string to be split
    // arr: array to hold coordinates
    // del: delimiter to separate strings
    // return: Array of split substrings
    void Tokenize(string s,long double (&arr)[2] , string del = " ");

    // Extracts coordinates from txt file
    // pathName: path to file to be extracted
    // return: Tuple of all x-coordinates and y-coordinates [x,y]
    vector<Map::Coordinates> ExtractFile(string pathName);
};

namespace Autonomous{

class PathFinding{
    private:
    public:

    // Converts degrees to radians
    // num: Number in degrees
    // return: Radian representation of angle
    static inline long double ToRadian(long double num){return num * M_PI / 180;}

    // Converts radians to degerees
    // num: Number in radians
    // return: Degree representation of angle
    static inline long double ToDegree(long double num){return num * 180 / M_PI;}

    // Rounds number to 12 degree precision
    // num: Number to be rouhnded
    // return: Number rounded to 12 degrees
    static inline long double Round_12(long double num){return floor(num*1e12+0.5)/1e12;}
    
    // Calculates the distance between two points using the Haversine Formula
    // gps1: First coordinate
    // gps2: Second Coordinate
    // return: Absolute value of the distance between two points in meters
    static long double CalcDistance(Map::Coordinates gps1, Map::Coordinates gps2);

    // Calculates new longitude value from projected gps coordinate and a point
    // source: Source coordinate
    // range: Distance away from source coordinate
    // bearing: Direction pointing away from source coordinate
    // return: new coordinates for the new position
    static Map::Coordinates CalcPosition(Map::Coordinates source, long double range, long double bearing);

    // Calculates bearing between two points
    // source: First coordinate
    // destination: Second coordinate 
    // return: Bearing from source to destination in degrees
    static long double CalcBearing(Map::Coordinates source, Map::Coordinates destination);

    // Finds the highest point along coast line and beach line
    // return: The index of the peak and -1 if not found
    static int FindPeak(vector<long double> height, bool reverse = false);

    // Divide line into subsections of length X meters apart from coordinate 1 to 2
    // gps1: First Coordinate
    // gps2: Second Coordinate
    // x: Specified interval lengths of each subsection. (Must be a divisor of the distance between gps1 and gps2)
    // return: list of (x,y) pairs along the line
    static vector<Map::Coordinates> SubDivideLine(Map::Coordinates gps1, Map::Coordinates gps2, long double x);

    // Create more points inside polygon bounded by polygon's edges
    // source: Starting gps location
    // boundary1: Bounding gps coordinate of upper location
    // boundary2: Bounding gps coordinate of lower location
    // SUBDIVISION: Length of subdivisions
    // return: List of all new points created within the boundary of the polygon with no slope value
    static vector<Map::Coordinates> CreatePoints(Map::Coordinates source, Map::Coordinates boundary1 , Map::Coordinates boundary2, long double const SUBDIVISION);

    // Draw the whole map with marked gps locations from origin to endpoint
    // coordinateList: Bounding coordinates
    // SUBDIVISION: Length of subdivisions
    // file: File to write to
    // Return: Writes list of all generated coordinates to file "newCoordinates.txt" 
    static void DrawMap(vector<Map::Coordinates> coordinateList, long double const SUBDIVISION, std::ofstream& file);
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