#include "../include/robot.hpp"

int main(int argc, char *argv[]){
    list<long double> resX,resY;
    std::tie(resX,resY)= Map::ExtractFile("T:\\Project SAND-e\\include\\coordinates.txt");
    std::cout.precision(20);
    for (long double x: resX){
        std::cout << x << std::endl;
    }
    return 0;
}