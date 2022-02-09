#include "robot.hpp"


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

// Calculates the distance between two Coordinates
long double Autonomous::PathFinding::CalcDistance(MainRobot::Coordinates gps1, MainRobot::Coordinates gps2){
    long double lat1 = ToRadian(gps1.latitude);
    long double long1 = ToRadian(gps1.longitude);
    long double lat2 = ToRadian(gps2.latitude);
    long double long2 = ToRadian(gps2.longitude);

    // Calculates the distance between point 1 and point 2 using Haversine Formula
    long double distance_long = long2 - long1;
    long double distance_lat = lat2 - lat1;

    long double distance = pow(sin(distance_lat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(distance_long / 2), 2);

    distance = 2 * asin(sqrt(distance));
    distance *= EARTH_RADIUS;

    // Convert to meters
    distance *= 1000;

    return abs(distance);
}


