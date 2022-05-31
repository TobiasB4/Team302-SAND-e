#include "../include/robot.hpp"

int main(int argc, char *argv[]){
    vector<Map::Coordinates> gps = Map::ExtractFile("C:\\Users\\TobiB\\Documents\\Project_SAND-e\\Software\\robot\\include\\coordinates.txt");
    std::ofstream file;
    file.open("C:\\Users\\TobiB\\Documents\\Project_SAND-e\\Software\\robot\\include\\newCoordinates.txt");
    Autonomous::PathFinding::DrawMap(gps,2.5L,file);
    file.close();
    return 0;
}