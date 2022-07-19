#include "../include/robot.hpp"

int main(int argc, char *argv[]){
    vector<Map::Coordinates> gps = Map::ExtractFile("T:\\Project SAND-e\\Team302-SAND-e\\robot\\include\\coordinates.txt");
    std::ofstream file;
    file.open("T:\\Project SAND-e\\Team302-SAND-e\\robot\\include\\newCoordinates.txt");
    Autonomous::PathFinding::DrawMap(gps,1.L,file);
    file.close();
    return 0;
}