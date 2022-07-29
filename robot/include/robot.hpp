#pragma once
#include "map.hpp"

namespace MainRobot {

class Robot {
   private:
    Autonomous::Map::Coordinates GPSCurr;
    Autonomous::Map::Coordinates GPSNext;
    const float WIDTH;
    const float LENGTH;

   public:
    Robot(float width, float length, Autonomous::Map::Coordinates gps1, Autonomous::Map::Coordinates gps2) : GPSCurr{gps1}, GPSNext{gps2}, WIDTH{width}, LENGTH{length} {}

    void UpdateCurrentGPS(Autonomous::Map::Coordinates newGPS);
    void UpdateNextGPS(Autonomous::Map::Coordinates newGPS);
    Autonomous::Map::Coordinates GetCurrentGPS();
    Autonomous::Map::Coordinates GetNextGPS();
};

};  // namespace MainRobot