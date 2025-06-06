#include <iostream>
#include "../HPPS/dijkstra.hpp"

DijkstraSP::DijkstraSP(const std::map<std::pair<int, int>, std::vector<Edge>> &graphInput, std::pair<int, int> source) : graph(graphInput)
{

    for (const auto &pair : graph)
    {
        distTo[pair.first] = std::numeric_limits<double>::infinity();
    }
    distTo[source] = 0.0;

    pq.push({source, 0.0});

    while (!pq.empty())
    {
        std::pair<int, int> v = pq.top().vertex;
        pq.pop();

        for (const Edge &e : graph.at(v))
        {
            relax(e);
        }
    }
}

void DijkstraSP::relax(const Edge &e)
{
    std::pair<int, int> v = e.from;
    std::pair<int, int> w = e.to;
    double weight = e.weight;

    if (distTo[w] > distTo[v] + weight)
    {
        distTo[w] = distTo[v] + weight;
        edgeTo[w] = e;
        pq.push({w, distTo[w]});
    }
}

bool DijkstraSP::hasPathTo(const std::pair<int, int> &v) const
{
    return distTo.at(v) != std::numeric_limits<double>::infinity();
}

double DijkstraSP::distTo(const std::pair<int, int> &v) const
{
    if (!hasPathTo(v))
    {
        std::cerr << "Sem caminho para (" << v.first << ", " << v.second << ")!" << std::endl;
        return -1;
    }
    return distTo.at(v);
}

std::vector<Edge> DijkstraSP::pathTo(const std::pair<int, int> &v) const
{
    std::vector<Edge> path;
    if (!hasPathTo(v))
        return path;

    std::pair<int, int> current = v;
    while (edgeTo.find(current) != edgeTo.end())
    {
        const Edge &e = edgeTo.at(current);
        path.insert(path.begin(), e);
        current = e.from;
    }
    return path;
}
