#include <iostream>
#include "../HPPS/functions.hpp"

Direction whatDir(pair<int, int> s, pair<int, int> t)
{
    int x = t.first - s.first;
    int y = t.second - s.second;
    if (x == -1 && y == 0)
        return Direction::North;
    if (x == 1 && y == 0)
        return Direction::South;
    if (x == 0 && y == 1)
        return Direction::East;
    if (x == 0 && y == -1)
        return Direction::West;

    return Direction::Null;
}

int changedDir(Direction bef, Direction now)
{
    if (bef == Direction::Null || bef == now)
    {
        return 0;
    }
    return 3;
}

constexpr double COST_BASE = 1.0; // Fator para ampliar o custo base
constexpr double TURN_PENALTY = 3.0; // Penalidade por mudança de direção

double calcPathCostWithPenalty(const std::vector<Edge> &path) {
    if (path.empty()) return 0.0;

    double cost = 0.0;
    Direction prevDir = Direction::Null;

    for (const auto &edge : path) {
        Direction currDir = whatDir(edge.from, edge.to);
        
        // Aplica fator de custo base
        cost += edge.weight * COST_BASE;

        // Aplica penalidade se mudou de direção
        if (prevDir != Direction::Null && prevDir != currDir) {
            cost += TURN_PENALTY;
        }

        prevDir = currDir;
    }

    return cost;
}


Graph buildHarborGraph(const Map& map, const map<char, pair<int,int>>& harbors) {
    Graph harborGraph;
    auto cellGraph = assembleDirGraph(map);  // Grafo de todas as células navegáveis

    for (const auto& [fromLabel, fromPos] : harbors) {
        Dijkstra dijkstra(cellGraph, fromPos);

        for (const auto& [toLabel, toPos] : harbors) {
            if (fromLabel == toLabel) continue;
            if (dijkstra.hasPathTo(toPos)) {
                vector<Edge> path = dijkstra.pathTo(toPos);

                // Agora usamos a função com penalidade de curvas
                double cost = calcPathCostWithPenalty(path);

                harborGraph.addEdge(fromPos, toPos, cost);
            }
        }
    }

    return harborGraph;
}
