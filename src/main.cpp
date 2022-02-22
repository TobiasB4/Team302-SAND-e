#include "../include/robot.hpp"

int main(int argc, char *argv[]){
    list<long double> resX,resY;
    std::tie(resX,resY)= Map::ExtractFile("T:\\Project SAND-e\\include\\coordinates.txt");
    std::cout.precision(20);
    std::cout << Autonomous::PathFinding::FindPeak(resY) << std::endl;
    std::cout << Autonomous::PathFinding::FindPeak(resY, true) << std::endl;
    return 0;
}