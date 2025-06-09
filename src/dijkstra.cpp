#include <iostream>
#include "../HPPS/dijkstra.hpp"
#include "../HPPS/graph.hpp"

using namespace std;

Dijkstra::Dijkstra(const Graph &vgraph, pair<int, int> source)  
{
    for (const auto &v : vgraph.vertices())
    {
        distToMap[v] = numeric_limits<double>::infinity();
    }
    distToMap[source] = 0.0;

    pq.push({source, 0.0});

    while (!pq.empty())
    {
        pair<int, int> v = pq.top().vertex;
        pq.pop();

        for (const Edge &e : vgraph.getAdj(v))
        {
            relax(e);
        }
    }
}

void Dijkstra::relax(const Edge &e)
{
    pair<int, int> v = e.from;
    pair<int, int> w = e.to;
    double weight = e.weight;

    if (distToMap[w] > distToMap[v] + weight)
    {
        distToMap[w] = distToMap[v] + weight;
        edgeToMap[w] = e;
        pq.push({w, distToMap[w]});
    }
}

bool Dijkstra::hasPathTo(const pair<int, int> &v) const
{
    auto it = distToMap.find(v);
    return it != distToMap.end() && it->second != numeric_limits<double>::infinity();
}

double Dijkstra::distTo(const pair<int, int> &v) const
{
    return distToMap.at(v);
}

vector<Edge> Dijkstra::pathTo(const pair<int, int> &v) const
{
    vector<Edge> path;
    if (!hasPathTo(v))
        return path;

    pair<int, int> current = v;
    while (edgeToMap.find(current) != edgeToMap.end())
    {
        const Edge &e = edgeToMap.at(current);
        path.insert(path.begin(), e);
        current = e.from;
    }
    return path;
}
