#pragma once


namespace MainRobot{

        struct Coordinates{
        double latitude;
        double longitude;
        double altitude;

        Coordinates(double latitude, double longitude, double altitude){
            this->latitude = latitude;
            this->longitude = longitude;
            this->altitude = altitude;
        }
    };
    
    class Robot{
        private:
        public:
            float width;
            float length;
            Coordinates GPSCurr;
            Coordinates GPSNext;
    };


};