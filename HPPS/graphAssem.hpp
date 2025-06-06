#ifndef GRAPHASSEMBLER_HPP
#define GRAPHASSEMBLER_HPP

#include <map>
#include <vector>

#include "functions.hpp"
#include "dijkstra.hpp"
#include "map.hpp"

using namespace std;

map<pair<int, int>, vector<Edge>> assembleDirGraph(const Map &vmap);

#endif