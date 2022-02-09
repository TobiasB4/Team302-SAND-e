#pragma once


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

    long double CalcDistance(MainRobot::Coordinates gps1, MainRobot::Coordinates gps2);
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