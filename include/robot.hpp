#pragma once
#include <math.h>
#include <vector>

namespace MainRobot{

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
        inline long double ToCartesianX(long double latitude, long double longitude){return Autonomous::EARTH_RADIUS * cos(latitude) * cos(longitude);}
        inline long double ToCartesianY(long double latitude, long double longitude){return Autonomous::EARTH_RADIUS * cos(latitude) * sin(longitude);}
        inline long double ToCartesianZ(long double latitude){return Autonomous::EARTH_RADIUS * sin(latitude);}
    };
    
    class Robot{
        private:
            Coordinates GPSCurr;
            Coordinates GPSNext;
            const float WIDTH;
            const float LENGTH;
        public:

            Robot(float width, float length,Coordinates gps1, Coordinates gps2):
            GPSCurr{gps1}
            ,GPSNext{gps2}
            ,WIDTH{width}
            ,LENGTH{length}{}


            void UpdateCurrentGPS(Coordinates newGPS);
            void UpdateNextGPS(Coordinates newGPS);
            Coordinates GetCurrentGPS();
            Coordinates GetNextGPS();
    };


};

namespace Autonomous{

const double EARTH_RADIUS = 6378.8;

class PathFinding{
    private:
    public:

    static inline long double ToRadian(long double num){return num * M_PI / 180;}
    static long double CalcDistance(MainRobot::Coordinates gps1, MainRobot::Coordinates gps2);
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