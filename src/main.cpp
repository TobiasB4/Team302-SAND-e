#include "../include/robot.hpp"

int main(int argc, char *argv[]){
    Map::XY_Pair gps = Map::XY_Pair(Map::ExtractFile("C:\\Users\\TobiB\\Documents\\Project_SAND-e\\Software\\include\\coordinates.txt"));
    std::cout.precision(12);
    long double slopeIntercept[2] = {0,0};
    Map::Coordinates gps1 = Map::Coordinates(gps.gps[0].latitude, gps.gps[0].longitude,0);
    Map::Coordinates gps2 = Map::Coordinates(gps.gps[gps.gps.size()-1].latitude,gps.gps[gps.gps.size()-1].longitude,0);
    Map::Coordinates projected_gps2 = Autonomous::PathFinding::CalcPosition(gps1,5.L,0.L);
    std::cout << Autonomous::PathFinding::CalcBearing(gps1,projected_gps2) << std::endl;
    return 0;
}