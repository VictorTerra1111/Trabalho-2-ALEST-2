#include <iostream>
#include "../HPPS/dijkstra.hpp"

using namespace std;

DijkstraSP::DijkstraSP(const map<pair<int, int>, vector<Edge>> &graphInput, pair<int, int> source) : graph(graphInput)
{
    for (const auto &pair : graph)
    {
        distToMap[pair.first] = numeric_limits<double>::infinity();
    }
    distToMap[source] = 0.0;

    pq.push({source, 0.0});

    while (!pq.empty())
    {
        pair<int, int> v = pq.top().vertex;
        pq.pop();

        // Verifica se v está presente no grafo (evita exceção ao usar at)
        if (graph.find(v) != graph.end())
        {
            for (const Edge &e : graph.at(v))
            {
                relax(e);
            }
        }
    }
}

void DijkstraSP::relax(const Edge &e)
{
    pair<int, int> v = e.from;
    pair<int, int> w = e.to;
    double weight = e.weight;

    if (distToMap[w] > distToMap[v] + weight)
    {
        distToMap[w] = distToMap[v] + weight;
        edgeTo[w] = e;
        pq.push({w, distToMap[w]});
    }
}

bool DijkstraSP::hasPathTo(const pair<int, int> &v) const
{
    auto it = distToMap.find(v);
    return it != distToMap.end() && it->second != numeric_limits<double>::infinity();
}

double DijkstraSP::distTo(const pair<int, int> &v) const
{
    return distToMap.at(v);  // ou use .find para mais segurança
}

vector<Edge> DijkstraSP::pathTo(const pair<int, int> &v) const
{
    vector<Edge> path;
    if (!hasPathTo(v))
        return path;

    pair<int, int> current = v;
    while (edgeTo.find(current) != edgeTo.end())
    {
        const Edge &e = edgeTo.at(current);
        path.insert(path.begin(), e);
        current = e.from;
    }
    return path;
}
