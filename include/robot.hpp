#pragma once
#include <math.h>


namespace MainRobot{

        struct Coordinates{
        long double latitude;
        long double longitude;
        long double altitude;
        long double cartesian_x;
        long double cartesian_y;
        long double cartesian_z;

        Coordinates(long double latitude, long double longitude, long double altitude){
            this->latitude = latitude;
            this->longitude = longitude;
            this->altitude = altitude;

            this->cartesian_x = ToCartesianX();
            this->cartesian_y = ToCartesianY();
            this->cartesian_z = ToCartesianZ();
        }

        private:
            inline long double ToCartesianX(){return Autonomous::EARTH_RADIUS * cos(this->latitude) * cos(this->latitude);}
            inline long double ToCartesianY(){return Autonomous::EARTH_RADIUS * cos(this->latitude) * sin(this->longitude);}
            inline long double ToCartesianZ(){return Autonomous::EARTH_RADIUS * sin(this->latitude);}

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