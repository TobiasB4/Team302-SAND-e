#include "../include/robot.hpp"

int main(int argc, char *argv[]){
    Map::XY_Pair gps = Map::XY_Pair(Map::ExtractFile("T:\\Project SAND-e\\Team302-SAND-e\\robot\\include\\coordinates.txt"));
    std::cout.precision(12);
    long double slopeIntercept[2] = {0,0};
    Map::Coordinates gps1 = Map::Coordinates(gps.gps[0].latitude, gps.gps[0].longitude,0);
    Map::Coordinates gps2 = Map::Coordinates(gps.gps[gps.gps.size()-1].latitude,gps.gps[gps.gps.size()-1].longitude,0);
    Map::Coordinates gps3 = Map::Coordinates(gps.gps[1].latitude, gps.gps[1].longitude,0);
    Map::Coordinates gps4 = Map::Coordinates(gps.gps[gps.gps.size()-2].latitude,gps.gps[gps.gps.size()-2].longitude,0);
    Map::Coordinates gps5 = Map::Coordinates(gps.gps[gps.gps.size()-3].latitude, gps.gps[gps.gps.size()-3].longitude,0);
    Map::Coordinates gps6 = Map::Coordinates(gps.gps[gps.gps.size()-4].latitude, gps.gps[gps.gps.size()-4].longitude,0);
    //Map::Coordinates projected_gps = Autonomous::PathFinding::CalcPosition(gps1,2.5L,90.L);
    // Map::XY_Pair results = Autonomous::PathFinding::SubDivideLine(gps1,gps2,2.5L);
    // for(Map::Coordinates x : results.gps){
    //     std::cout << "[" << x.latitude << ", " << x.longitude << "]\n";
    // }
    std::ofstream file;
    file.open("T:\\Project SAND-e\\Team302-SAND-e\\robot\\include\\newCoordinates.txt");
    Autonomous::PathFinding::CreatePoints(gps1,gps2,gps3,2.5L,file);
    Autonomous::PathFinding::CreatePoints(gps3,gps2,gps4,2.5L,file);
    Autonomous::PathFinding::CreatePoints(gps3, gps4, gps5, 2.5L, file);
    Autonomous::PathFinding::CreatePoints(gps3, gps5, gps6, 2.5L, file);
    file.close();
    return 0;
}