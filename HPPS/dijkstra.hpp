#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <map>
#include <string>

using namespace std;

struct Edge
{
    pair<int, int> from;
    pair<int, int> to;
    double weight;

    Edge(pair<int, int> v, pair<int, int> w, double wt)
        : from(v), to(w), weight(wt) {}
};

struct QueueItem
{
    pair<int, int> vertex;
    double priority;
    
    bool operator>(const QueueItem &other) const
    {
        return priority > other.priority;
    }
};

class DijkstraSP
{
public:
    DijkstraSP(const map<pair<int, int>, vector<Edge>> &graph, pair<int, int> source);

    bool hasPathTo(const pair<int, int> &v) const;

    double distTo(const pair<int, int> &v) const;

    vector<Edge> pathTo(const pair<int, int> &v) const;

private:
    void relax(const Edge &e);

    map<pair<int, int>, Edge> edgeTo;

    map<pair<int, int>, double> distToMap;

    priority_queue<QueueItem, vector<QueueItem>, greater<QueueItem>> pq;

    map<pair<int, int>, vector<Edge>> graph;
};

#endif