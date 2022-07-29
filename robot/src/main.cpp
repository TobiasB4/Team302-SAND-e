#include "../include/robot.hpp"
#include "../include/map.hpp"
#include "../include/pathfinding.hpp"

int main(int argc, char *argv[])
{
    vector<string> arguments = Autonomous::Map::ReadArgs(argc - 1, argv + 1);
    vector<Autonomous::Map::Coordinates> gps = Autonomous::Map::ExtractFile(arguments[0] + "\\coordinates.txt");
    std::ofstream file;
    file.open(arguments[0] + "\\" + arguments[1]);
    Autonomous::PathFinding::DrawMap(gps, 1.L, file);
    file.close();
    return 0;
}