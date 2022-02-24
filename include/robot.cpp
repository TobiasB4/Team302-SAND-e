#include "robot.hpp"

void Map::Tokenize(string s,long double (&arr)[2] , string del){
    int start = 0;
    int end = s.find(del);
    int count = 0;
    while (end != -1) {
        arr[count] = std::stold(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
        count++;
    }
    arr[count] = std::stold(s.substr(start, end - start));
}

vector<Map::Coordinates> Map::ExtractFile(string pathName){
    vector<Map::Coordinates> gps;
    std::fstream f;
    f.open(pathName, std::ios::in);
    string delimiter = ",";
    long double tempArr[2] = {0,0};
    if(f.is_open()){
        string tmp;
        string removeableChar = "[ ]\n";
        while (std::getline(f,tmp)){
            for(char c: removeableChar){
                tmp.erase(remove(tmp.begin() , tmp.end() , c), tmp.end());
            }
            Tokenize(tmp, tempArr, delimiter);
            gps.push_back(Map::Coordinates(tempArr[0], tempArr[1], 0.L));
        }
        f.close();
    }
    return gps;
}

void MainRobot::Robot::UpdateCurrentGPS(Map::Coordinates newGPS){
    this->GPSCurr = newGPS;
}

void MainRobot::Robot::UpdateNextGPS(Map::Coordinates newGPS){
    this->GPSNext = newGPS;
}

Map::Coordinates MainRobot::Robot::GetCurrentGPS(){
    return this->GPSCurr;
}

Map::Coordinates MainRobot::Robot::GetNextGPS(){
    return this->GPSNext;
}


long double Autonomous::PathFinding::CalcDistance(Map::Coordinates gps1, Map::Coordinates gps2){
    long double lat1 = ToRadian(gps1.latitude);
    long double long1 = ToRadian(gps1.longitude);
    long double lat2 = ToRadian(gps2.latitude);
    long double long2 = ToRadian(gps2.longitude);

    // Calculates the distance between point 1 and point 2 using Haversine Formula
    long double distance_long = long2 - long1;
    long double distance_lat = lat2 - lat1;

    long double distance = pow(sin(distance_lat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(distance_long / 2), 2);

    distance = 2 * asin(sqrt(std::min((long double)1,distance)));
    distance *= EARTH_RADIUS;

    // Convert to meters
    distance *= 1000;

    return abs(distance);
}

Map::Coordinates Autonomous::PathFinding::CalcPosition(Map::Coordinates source, long double range, long double bearing)
{
    long double latA = Autonomous::PathFinding::ToRadian(source.latitude);
    long double lonA = Autonomous::PathFinding::ToRadian(source.longitude);
    long double angularDistance = range / EARTH_RADIUS / 1000;
    long double trueCourse = Autonomous::PathFinding::ToRadian(bearing);

    long double lat = asin(
        sin(latA) * cos(angularDistance) + 
        cos(latA) * sin(angularDistance) * cos(trueCourse));

    long double lon = lonA + atan2(
        sin(trueCourse) * sin(angularDistance) * cos(latA), 
        cos(angularDistance) - sin(latA) * sin(lat));

    //Not using this seems to fix any problems with bearing not sure why...
    //long double lon = (std::fmod((lonA + dlon + (long double)M_PI),(long double)(2.*M_PI)))- (long double)M_PI;

    return Map::Coordinates(
        Autonomous::PathFinding::ToDegree(lat) , 
        Autonomous::PathFinding::ToDegree(lon), 
        source.altitude);
}

long double Autonomous::PathFinding::CalcBearing(Map::Coordinates source, Map::Coordinates destination){
    long double theta1 = ToRadian(source.latitude);
    long double theta2 = ToRadian(destination.latitude);
    long double delta1 = ToRadian(destination.latitude-source.latitude);
    long double delta2 = ToRadian(destination.longitude-source.longitude);

    long double y = sin(delta2) * cos(theta2);
    long double x = cos(theta1)*sin(theta2) - sin(theta1)*cos(theta2)*cos(delta2);
    long double bearing = atan2(y,x);
    bearing = ToDegree(bearing);
    bearing = std::fmod((bearing + 360),360.L);

    return bearing;
}

void Autonomous::PathFinding::LineEquation(Map::Coordinates gps1, Map::Coordinates gps2, long double (&returnArr)[2]){
    // slope value
    returnArr[0] = (gps2.latitude-gps1.latitude)/(gps2.longitude-gps1.longitude);
    // y-intercept value
    returnArr[1] = (-returnArr[0])*gps1.latitude+gps1.longitude;
}

int Autonomous::PathFinding::FindPeak(vector<long double> height, bool reverse){

    long double max = -(__LDBL_MAX__-1);
    if(reverse){
        int count = height.size();
        for(vector<long double>::reverse_iterator it = height.rbegin(); it != height.rend(); it++){
            if(*it < max){
            return count;
            }
            max = *it;
            count--;
        }
    }else{
        int count = -1;
        for(long double h : height){
        if(h < max){
            return count;
        }
        max = h;
        count++;
        }
    }

    return -1;
}

Map::XY_Pair Autonomous::PathFinding::SubDivideLine(Map::Coordinates gps1, Map::Coordinates gps2, long double const SUBDIVISION){
int const SLOPE = 0;
int const INTERCEPT = 1;
long double slopeIntercept[2] = {0,0};

Autonomous::PathFinding::LineEquation(gps1,gps2,slopeIntercept);
Map::XY_Pair result = Map::XY_Pair({gps1}, slopeIntercept[0], slopeIntercept[1]);

long double const bearing = Autonomous::PathFinding::CalcBearing(gps1, gps2);
int count = 0;
for (long double distance = Autonomous::PathFinding::CalcDistance(gps1, gps2); distance > 0; distance-=SUBDIVISION, count++){
    Map::Coordinates newCoord = Autonomous::PathFinding::CalcPosition(Map::Coordinates(result.gps[count].latitude, result.gps[count].longitude, 0), SUBDIVISION, bearing);
    result.gps.push_back(newCoord);
}

return result;
}