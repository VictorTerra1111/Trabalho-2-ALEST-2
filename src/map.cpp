#include <iostream>
#include <fstream>
#include <string> 
#include "../HPPS/map.hpp"

using namespace std;

Map::Map(const string &filePath)
{
    load(filePath);
    findHarbors();
}

void Map::load(const string &filePath)
{
    string line; 
    ifstream file(filePath);
    if (!file.is_open())
    {
        cerr << "ERROR: " << filePath << endl;
        return;
    }

    file >> lines >> columns;
    file.ignore();

    while (getline(file, line))
    {
        if (!line.empty())
        {
            matrix.push_back(line);
        }
    }
    file.close();
}

void Map::findHarbors()
{
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[i].size(); ++j)
        {
            char c = matrix[i][j];
            if (c >= '1' && c <= '9')
            {
                harbors[c] = {i, j};
            }
        }
    }
}

const vector<string> &Map::getMatrix() const { return matrix; }

int Map::getLines() const { return lines; }

int Map::getColumns() const { return columns; }

map<char, pair<int, int>> Map::getHarbor() const { return harbors; }