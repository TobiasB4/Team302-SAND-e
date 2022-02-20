#include "../include/robot.hpp"
#include <iostream>

int main(){
    Map::Coordinates gps1 = Map::Coordinates(49.28451838370452, -123.14407949644797, 0);
    Map::Coordinates gps2 = Map::Coordinates(49.28521200925398, -123.14392994177165, 0);
    long double res = Autonomous::PathFinding::CalcDistance(gps1, gps2);
    std::cout << res << std::endl;
    return 0;
}