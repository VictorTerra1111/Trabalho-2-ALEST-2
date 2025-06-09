#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <vector>
#include <map>
#include <queue>
#include <utility>
#include "../HPPS/graph.hpp"
#include "../HPPS/functions.hpp" // Para Direction, whatDir()

struct State {
    std::pair<int, int> vertex;
    Direction dir; // direção de chegada até vertex

    bool operator<(const State &other) const = delete; // Não usar comparação padrão
};

struct PQElement {
    State state;
    double cost;

    bool operator<(const PQElement &other) const {
        return cost > other.cost; // min-heap
    }
};

class Dijkstra {
public:
    Dijkstra(const Graph &graph, std::pair<int, int> source);

    bool hasPathTo(const std::pair<int, int> &v) const;

    double distTo(const std::pair<int, int> &v) const;

    std::vector<Edge> pathTo(const std::pair<int, int> &v) const;

private:
    void relax(const State &state, const Edge &edge);

    const Graph &graph;

    // distToMap indexed by (vertex, direction)
    std::map<std::pair<std::pair<int, int>, Direction>, double> distToMap;
    std::map<std::pair<std::pair<int, int>, Direction>, Edge> edgeToMap;

    std::priority_queue<PQElement> pq;

    std::map<std::pair<int, int>, double> bestDistVertex;
};

#endif // DIJKSTRA_HPP
