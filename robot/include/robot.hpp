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
            Coordinates GPSCurr;
            Coordinates GPSNext;
            const float width;
            const float length;
        public:

            Robot(float width, float length,Coordinates gps1, Coordinates gps2):
            GPSCurr{gps1}
            ,GPSNext{gps2}
            ,width{width}
            ,length{length}{}


            void UpdateCurrentGPS(Coordinates newGPS);
            void UpdateNextGPS(Coordinates newGPS);
            Coordinates GetCurrentGPS();
            Coordinates GetNextGPS();
    };


};