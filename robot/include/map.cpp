#include "map.hpp"

int Autonomous::Map::QuickHash(string s)
{
    if (s == "-I")
    {
        return _I;
    }
    else if (s == "-O")
    {
        return _O;
    }
    else
    {
        return -1;
    }
}

vector<string> Autonomous::Map::ReadArgs(int numArgs, char *argVars[])
{
    std::vector<std::string> result;
    for (int i = 0; i < numArgs; i += 2)
    {
        int temp = Autonomous::Map::QuickHash(argVars[i]);
        switch (temp)
        {
        case _I:
            result.insert(result.begin() + _I, argVars[i + 1]);
            break;
        case _O:
            result.insert(result.begin() + _O, argVars[i + 1]);
            break;
        default:
            break;
        }
    }
    return result;
}

void Autonomous::Map::Tokenize(string s, long double (&arr)[2], string del)
{
    int start = 0;
    int end = s.find(del);
    int count = 0;
    while (end != -1)
    {
        arr[count] = std::stold(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
        count++;
    }
    arr[count] = std::stold(s.substr(start, end - start));
}

vector<Autonomous::Map::Coordinates> Autonomous::Map::ExtractFile(string pathName)
{
    vector<Autonomous::Map::Coordinates> gps;
    std::fstream f;
    f.open(pathName, std::ios::in);
    string delimiter = ",";
    long double tempArr[2] = {0, 0};
    if (f.is_open())
    {
        string tmp;
        string removeableChar = "[ ]\n";
        while (std::getline(f, tmp))
        {
            for (char c : removeableChar)
            {
                tmp.erase(remove(tmp.begin(), tmp.end(), c), tmp.end());
            }
            Tokenize(tmp, tempArr, delimiter);
            gps.push_back(Autonomous::Map::Coordinates(tempArr[0], tempArr[1], 0.L));
        }
        f.close();
    }
    return gps;
}

long double Autonomous::Map::Minimum(vector<Autonomous::Map::Coordinates> list)
{
    long double result = __LDBL_MAX__;
    for (Autonomous::Map::Coordinates coordinate : list)
    {
        if (coordinate.longitude < result)
        {
            result = coordinate.longitude;
        }
    }
    return result;
}

long double Autonomous::Map::Maximum(vector<Autonomous::Map::Coordinates> list)
{
    long double result = -(__LDBL_MAX__ - 10);
    for (Autonomous::Map::Coordinates coordinate : list)
    {
        if (coordinate.longitude > result)
        {
            result = coordinate.longitude;
        }
    }
    return result;
}