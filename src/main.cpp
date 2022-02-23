#include "../include/robot.hpp"

int main(int argc, char *argv[]){
    Map::XY_Pair pair = Map::XY_Pair({},{});
    std::tie(pair.x,pair.y)= Map::ExtractFile("C:\\Users\\TobiB\\Documents\\Project_SAND-e\\Software\\include\\coordinates.txt");
    std::cout.precision(20);
    long double slopeIntercept[2] = {0,0};
    Map::Coordinates gps1 = Map::Coordinates(pair.x[0], pair.y[0],0);
    Map::Coordinates gps2 = Map::Coordinates(pair.x[pair.x.size()-1],pair.y[pair.y.size()-1],0);
    Autonomous::PathFinding::LineEquation(gps1,gps2,slopeIntercept);
    Map::Coordinates projected_gps2 = Autonomous::PathFinding::CalcPosition(gps1,(long double)5,(long double)90);
    std::cout << Autonomous::PathFinding::CalcDistance(gps1,projected_gps2) << std::endl;
    return 0;
}