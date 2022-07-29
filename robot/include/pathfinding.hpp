#pragma once
#include <float.h>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include "map.hpp"
#include "template.hpp"
using std::string;
using std::vector;
#define EARTH_RADIUS 6378.8  // in km

namespace Autonomous {

class PathFinding {
   private:
   public:
    // Converts degrees to radians
    // num: Number in degrees
    // return: Radian representation of angle
    static inline long double ToRadian(long double num) { return num * M_PI / 180; }

    // Converts radians to degerees
    // num: Number in radians
    // return: Degree representation of angle
    static inline long double ToDegree(long double num) { return num * 180 / M_PI; }

    // Rounds number to 12 degree precision
    // num: Number to be rouhnded
    // return: Number rounded to 12 degrees
    static inline long double Round_12(long double num) { return floor(num * 1e12 + 0.5) / 1e12; }

    // Calculates the distance between two points using the Haversine Formula
    // gps1: First coordinate
    // gps2: Second Coordinate
    // return: Absolute value of the distance between two points in meters
    static long double CalcDistance(Autonomous::Map::Coordinates gps1, Autonomous::Map::Coordinates gps2);

    // Calculates new longitude value from projected gps coordinate and a point
    // source: Source coordinate
    // range: Distance away from source coordinate
    // bearing: Direction pointing away from source coordinate
    // return: new coordinates for the new position
    static Autonomous::Map::Coordinates CalcPosition(Autonomous::Map::Coordinates source, long double range, long double bearing);

    // Calculates bearing between two points
    // source: First coordinate
    // destination: Second coordinate
    // return: Bearing from source to destination in degrees
    static long double CalcBearing(Autonomous::Map::Coordinates source, Autonomous::Map::Coordinates destination);

    // Draw the whole map with marked gps locations from origin to endpoint
    // coordinateList: Bounding coordinates
    // INTERVAL_DISTANCE: Length of distance between intervals
    // file: File to write to
    // Return: Writes list of all generated coordinates to file "newCoordinates.txt"
    static void DrawMap(vector<Autonomous::Map::Coordinates> coordinateList, long double const INTERVAL_DISTANCE, std::ofstream &file);
};

};  // namespace Autonomous