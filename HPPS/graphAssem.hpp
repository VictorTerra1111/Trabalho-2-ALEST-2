#ifndef GRAPH_ASSEM_HPP
#define GRAPH_ASSEM_HPP

#include <map>
#include <vector>
#include <utility>
#include "edge.hpp"
#include "map.hpp"

std::map<std::pair<int, int>, std::vector<Edge>> assembleDirGraph(const Map &vmap);

#endif 
