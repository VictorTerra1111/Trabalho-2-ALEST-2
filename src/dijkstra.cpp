#include "../HPPS/dijkstra.hpp"
#include <limits>

Dijkstra::Dijkstra(const Graph &vgraph, std::pair<int, int> source) : graph(vgraph)
{
    distToMap[{source, Direction::Null}] = 0.0;
    bestDistVertex[source] = 0.0;

    pq.push({{source, Direction::Null}, 0.0});

    while (!pq.empty())
    {
        PQElement current = pq.top();
        pq.pop();

        State state = current.state;
        double cost = current.cost;

        // Ignorar se já existe caminho melhor para este estado
        if (distToMap[{state.vertex, state.dir}] < cost)
            continue;

        for (const Edge &e : graph.getAdj(state.vertex))
        {
            relax(state, e);
        }
    }
}

void Dijkstra::relax(const State &state, const Edge &edge)
{
    Direction prevDir = state.dir;
    Direction currDir = whatDir(edge.from, edge.to);

    double penalty = 0.0;
    if (prevDir != Direction::Null && prevDir != currDir)
        penalty = 3.0;

    double newDist = distToMap[{state.vertex, prevDir}] + edge.weight + penalty;

    auto nextState = std::make_pair(edge.to, currDir);

    if (distToMap.find(nextState) == distToMap.end() || distToMap[nextState] > newDist)
    {
        distToMap[nextState] = newDist;
        edgeToMap[nextState] = edge;
        pq.push({{edge.to, currDir}, newDist});

        if (bestDistVertex.find(edge.to) == bestDistVertex.end() || bestDistVertex[edge.to] > newDist)
            bestDistVertex[edge.to] = newDist;
    }
}

bool Dijkstra::hasPathTo(const std::pair<int, int> &v) const
{
    return bestDistVertex.find(v) != bestDistVertex.end();
}

double Dijkstra::distTo(const std::pair<int, int> &v) const
{
    auto it = bestDistVertex.find(v);
    if (it == bestDistVertex.end())
        return std::numeric_limits<double>::infinity();
    return it->second;
}

std::vector<Edge> Dijkstra::pathTo(const std::pair<int, int> &v) const
{
    std::vector<Edge> bestPath;
    double bestCost = std::numeric_limits<double>::infinity();
    Direction bestDir = Direction::Null;

    for (const auto &[key, cost] : distToMap)
    {
        if (key.first == v && cost < bestCost)
        {
            bestCost = cost;
            bestDir = key.second;
        }
    }

    if (bestCost == std::numeric_limits<double>::infinity())
        return bestPath;

    std::pair<std::pair<int, int>, Direction> current = {v, bestDir};

    while (edgeToMap.find(current) != edgeToMap.end())
    {
        const Edge &e = edgeToMap.at(current);
        bestPath.insert(bestPath.begin(), e);
        Direction prevDir = whatDir(e.from, e.to);
        current = {e.from, prevDir};
    }

    return bestPath;
}
