#include "robot.hpp"
#include "definition.hpp"

void MainRobot::Robot::UpdateCurrentGPS(Coordinates newGPS){
    this->GPSCurr = newGPS;
}

void MainRobot::Robot::UpdateNextGPS(Coordinates newGPS){
    this->GPSNext = newGPS;
}

MainRobot::Coordinates MainRobot::Robot::GetCurrentGPS(){
    return this->GPSCurr;
}

MainRobot::Coordinates MainRobot::Robot::GetNextGPS(){
    return this->GPSNext;
}

long double MainRobot::Robot::CalcDistance(Coordinates gps1, Coordinates gps2){
    long double lat1 = gps1.latitude / (180/M_PI);
    long double long1 = gps1.longitude / (180/M_PI);
    long double lat2 = gps2.latitude / (180/M_PI);
    long double long2 = gps2.longitude / (180/M_PI);

    // Calculates the distance between point 1 and point 2 using Haversine Formula
    long double distance_long = long2 - long1;
    long double distance_lat = lat2 - lat1;

    long double distance = pow(sin(distance_long / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(distance_long / 2), 2);

    distance *= EARTH_RADIUS;

    return distance;
}