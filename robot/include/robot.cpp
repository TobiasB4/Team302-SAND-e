#include "robot.hpp"

void MainRobot::Robot::UpdateCurrentGPS(Autonomous::Map::Coordinates newGPS) {
    this->GPSCurr = newGPS;
}

void MainRobot::Robot::UpdateNextGPS(Autonomous::Map::Coordinates newGPS) {
    this->GPSNext = newGPS;
}

Autonomous::Map::Coordinates MainRobot::Robot::GetCurrentGPS() {
    return this->GPSCurr;
}

Autonomous::Map::Coordinates MainRobot::Robot::GetNextGPS() {
    return this->GPSNext;
}