#include "../include/robot.hpp"

int main(int argc, char *argv[]){
    list<long double> resX,resY;
    std::tie(resX,resY)= Map::ExtractFile("C:\\Users\\TobiB\\Documents\\Project_SAND-e\\Software\\include\\coordinates.txt");
    std::cout.precision(20);
    for (long double x: resX){
        std::cout << x << std::endl;
    }
    return 0;
}