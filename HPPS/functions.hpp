#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include "edge.hpp"
#include "graph.hpp" 
#include <map>
#include "graphAssem.hpp"
#include "dijkstra.hpp"
#include "map.hpp" 

using namespace std;

enum class Direction{
    North,
    South,
    East, 
    West,
    Null
};

Direction whatDir(pair<int, int> s, pair<int, int> t);

int changedDir(Direction bef, Direction now);

double calcPathCostWithPenalty(const vector<Edge> &path);

Graph buildHarborGraph(const Map& map, const std::map<char, std::pair<int,int>>& harbors);

#endif
