#include "../include/robot.hpp"

int main(int argc, char *argv[]){
    //Map::XY_Pair gps = Map::XY_Pair(Map::ExtractFile("T:\\Project SAND-e\\Team302-SAND-e\\robot\\include\\coordinates.txt"));
    Map::XY_Pair gps = Map::XY_Pair(Map::ExtractFile("C:\\Users\\TobiB\\Documents\\Project_SAND-e\\Software\\robot\\include\\coordinates.txt"));
    //Map::XY_Pair gps = Map::XY_Pair(Map::ExtractFile(argv[1]));

    std::ofstream file;
    //file.open("T:\\Project SAND-e\\Team302-SAND-e\\robot\\include\\newCoordinates.txt");
    file.open("C:\\Users\\TobiB\\Documents\\Project_SAND-e\\Software\\robot\\include\\newCoordinates.txt");
    //Autonomous::PathFinding::CreatePoints(gps.gps[0],gps.gps[1],gps.gps[gps.gps.size()-1],2.5L,file);
    Autonomous::PathFinding::DrawMap(gps,2.5L,file);
    file.close();
    return 0;
}