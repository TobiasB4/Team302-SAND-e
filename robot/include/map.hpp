#pragma once
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace Autonomous {

class Map {
   private:
    enum argCodes {
        _I,
        _O
    };

   public:
    // Define the latitude, longitude, and altitude of a given coordinate
    struct Coordinates {
        long double latitude;
        long double longitude;
        long double altitude;

        Coordinates() = default;
        Coordinates(long double latitude, long double longitude, long double altitude) {
            this->latitude = latitude;
            this->longitude = longitude;
            this->altitude = altitude;
        }
    };

    // Define the linear equation of a line along with min and max y-values
    struct Lines {
        long double slope;
        long double y_intercept;
        long double y_min;
        long double y_max;

        Lines() = default;

        // slope: m in "y = mx + b", slope of the line
        // y_intercept: b in "y = mx + b", y-intercept of the line
        // y_min: minimum y value where this line applicable
        // y_max: maximum y value where this line is applicable
        Lines(long double slope, long double y_intercept, long double y_min, long double y_max) {
            this->slope = slope;
            this->y_intercept = y_intercept;
            this->y_min = y_min;
            this->y_max = y_max;
        }

        // Creates a linear equation between two coordinates
        // start: Any coordinate defined with longitude and latitude
        // end: Any other coordinate defined with longitude and latitude
        Lines(Autonomous::Map::Coordinates start, Autonomous::Map::Coordinates end) {
            long double x1 = start.latitude;
            long double x2 = end.latitude;
            long double y1 = start.longitude;
            long double y2 = end.longitude;

            this->slope = (y2 - y1) / (x2 - x1);
            this->y_intercept = y2 - x2 * this->slope;
            this->y_min = y2 <= y1 ? y2 : y1;
            this->y_max = y2 >= y1 ? y2 : y1;
        }
    };

    // Converts arguments passed to the program to enum argCodes
    // s: argument
    // return: hashed argument
    static int QuickHash(string s);

    // Reads all arguments provided when starting program
    // return: A vector of all allowed arguments
    static vector<string> ReadArgs(int numArgs, char *argVars[]);

    // Splits string into substrings separated by delimiter
    // s: string to be split
    // arr: array to hold coordinates
    // del: delimiter to separate strings
    // return: Array of split substrings
    static void Tokenize(string s, long double (&arr)[2], string del = " ");

    // Extracts coordinates from txt file
    // pathName: path to file to be extracted
    // return: Tuple of all x-coordinates and y-coordinates [x,y]
    static vector<Autonomous::Map::Coordinates> ExtractFile(string pathName);

    // Find the minimum latitude or longitude
    // list: Vector of coordinates to serach through
    // sortVal: Either "lat"(latitude) or "long"(longitude)
    // return: the minimum sortVal value in the vector
    static long double Minimum(vector<Autonomous::Map::Coordinates> list);

    // Find the maximum latitude or longitude
    // list: vector of coordinates to search through
    // sortVal: Either "lat"(latitude) or "long"(longitude)
    // return: the minimum sortVal value in the vector
    static long double Maximum(vector<Autonomous::Map::Coordinates> list);
};
};  // namespace Autonomous