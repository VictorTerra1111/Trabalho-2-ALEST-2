#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <vector>
#include "edge.hpp"

class Graph {
private:
    std::map<std::pair<int, int>, std::vector<Edge>> adj;

public:
    void addEdge(const std::pair<int, int>& s, const std::pair<int, int>& t, double w) {
        adj[s].emplace_back(s, t, w);
    }

    const std::vector<Edge>& getAdj(const std::pair<int, int>& v) const {
        static const std::vector<Edge> empty;
        auto it = adj.find(v);
        return (it != adj.end()) ? it->second : empty;
    }

    std::vector<std::pair<int, int>> vertices() const {
        std::vector<std::pair<int, int>> keys;
        for (const auto& [key, _] : adj)
            keys.push_back(key);
        return keys;
    }
};

#endif
