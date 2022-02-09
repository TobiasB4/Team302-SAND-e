#include "robot.hpp"

void MainRobot::Robot::UpdateCurrentGPS(MainRobot::Coordinates newGPS){
    this->GPSCurr = newGPS;
}

void MainRobot::Robot::UpdateNextGPS(MainRobot::Coordinates newGPS){
    this->GPSNext = newGPS;
}

MainRobot::Coordinates MainRobot::Robot::GetCurrentGPS(){
    return this->GPSCurr;
}

MainRobot::Coordinates MainRobot::Robot::GetNextGPS(){
    return this->GPSNext;
}