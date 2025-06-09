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

double calcPathCostWithPenalty(const std::vector<Edge> &path) {
    if (path.empty()) return 0.0;

    double cost = 0.0;
    Direction prevDir = Direction::Null;

    for (const auto &edge : path) {
        Direction currDir = whatDir(edge.from, edge.to);
        cost += edge.weight; // normalmente 1.0
        cost += changedDir(prevDir, currDir);
        prevDir = currDir;
    }

    return cost;
}