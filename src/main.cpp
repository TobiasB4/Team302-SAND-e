#include "../include/robot.hpp"

int main(int argc, char *argv[]){
    list<long double> resX,resY;
    std::tie(resX,resY)= Map::ExtractFile("C:\\Users\\TobiB\\Documents\\Project_SAND-e\\Software\\include\\coordinates.txt");
    std::cout.precision(20);
    std::cout << Autonomous::PathFinding::FindPeak(resY) << std::endl;
    std::cout << Autonomous::PathFinding::FindPeak(resY, true) << std::endl;
    return 0;
}