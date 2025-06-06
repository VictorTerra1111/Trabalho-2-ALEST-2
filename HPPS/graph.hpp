#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <vector>
#include "edge.hpp"

using namespace std;

class Graph
{
private:
    map<pair<int, int>, vector<Edge>> adj;

public:
    void addEdge(pair<int, int> s, pair<int, int> t, double w)
    {
        adj[s].emplace_back(s, t, w);
    }

    const vector<Edge> &getAdj(pair<int, int> v) const
    {
        static const vector<Edge> empty; 
        auto it = adj.find(v);
        if(it != adj.end()) {
            return it->second;
        }
        return empty;
    }

    vector<pair<int, int>> vertices() const
    {
        vector<pair<int, int>> keys;

        for (const auto &coord : adj)
            keys.push_back(coord.first);
        return keys;
    }

};

#endif
