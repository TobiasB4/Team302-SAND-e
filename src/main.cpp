#include "../include/robot.hpp"

int main(){
    list<string> res;
    res = Map::ExtractFile("T:\\Project SAND-e\\include\\coordinates.txt");
    for (string s: res){
        std::cout << s << std::endl;
    }
        return 0;
}