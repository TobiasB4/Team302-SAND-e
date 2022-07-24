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

long double Map::Minimum(vector<Map::Coordinates> list, string sortVal){
    long double result = __LDBL_MAX__;
    for(Map::Coordinates coordinate : list){
        if(sortVal == "lat"){
            if(coordinate.latitude < result){
                result = coordinate.latitude;
            }
        }else if (sortVal == "long"){
            if(coordinate.longitude < result){
                result = coordinate.longitude;
            }
        }else{
            return -1;
        }
    }
    return result;
}

long double Map::Maximum(vector<Map::Coordinates> list, string sortVal){
    long double result = -(__LDBL_MAX__-10);
    for(Map::Coordinates coordinate : list){
        if(sortVal == "lat"){
            if(coordinate.latitude > result){
                result = coordinate.latitude;
            }
        }else if (sortVal == "long"){
            if(coordinate.longitude > result){
                result = coordinate.longitude;
            }
        }else{
            return -1;
        }
    }
    return result;
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

void Autonomous::PathFinding::DrawMap(vector<Map::Coordinates> coordinateList, long double const SUBDIVISION, std::ofstream& file){
    // Setup necessary storage and vars
    vector<Map::Coordinates> *result = new vector<Map::Coordinates>{coordinateList[0]};
    long double y_min = Map::Minimum(coordinateList, "long");
    long double y_max = Map::Maximum(coordinateList, "long");
    Map::Coordinates bottom = Map::Coordinates(coordinateList[0].latitude, y_min, 0);
    Map::Coordinates top = Map::Coordinates(coordinateList[0].latitude, y_max, 0);
    long double distance = Autonomous::PathFinding::CalcDistance(bottom,top);
    int intervals = distance / SUBDIVISION;
    // Change in y every subdivision
    long double dy = abs((y_max - y_min) / intervals);
    vector<Map::Lines> *line_equations = new vector<Map::Lines>{Map::Lines(coordinateList[0],coordinateList[coordinateList.size()-1])};
    std::stack<Map::Coordinates> *temp = new std::stack<Map::Coordinates>();

    // Calculate all the line equations
    for (int i = 0; i < coordinateList.size()-1; i++){
        line_equations->push_back(Map::Lines(coordinateList[i], coordinateList[i + 1]));
    }

    for (int i = 1; i <= intervals;i++){
        long double y_current = y_min + dy * i;
        int count = 0;
        for(Map::Lines line : *line_equations){
            if(y_current>=line.y_min && y_current<=line.y_max){
                if(count%4<2){
                    result->push_back(Map::Coordinates((y_current-line.y_intercept)/line.slope,y_current,0));
                }else{
                    temp->push(Map::Coordinates((y_current - line.y_intercept) / line.slope, y_current, 0));
                }
                count++;
            }
        }
    }

    *result = Concatenate(*result, *temp);

    for (Map::Coordinates coordinate : *result)
    {
        if (!(coordinate.latitude < 48.L || coordinate.latitude > 50.L || coordinate.latitude == NULL) && !(coordinate.longitude < -125.L || coordinate.longitude > -122.L || coordinate.longitude == NULL))
        {
            file << std::setprecision(16) << "[" << coordinate.latitude << ", " << coordinate.longitude << "]\n";
        }
    }

    delete temp;
    delete line_equations;
    delete result;
}