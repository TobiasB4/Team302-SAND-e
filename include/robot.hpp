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

            long double CalcDistance(Coordinates gps1, Coordinates gps2);
    };


};