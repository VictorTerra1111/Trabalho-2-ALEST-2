#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <map>
#include <string>
#include <iostream>

struct Edge
{
    std::pair<int, int> from;
    std::pair<int, int> to;
    double weight;

    Edge(std::pair<int, int> v, std::pair<int, int> w, double wt)
        : from(v), to(w), weight(wt) {}
};

class DijkstraSP
{
public:
    DijkstraSP(const std::map<std::pair<int, int>, std::vector<Edge>> &graph,
               std::pair<int, int> source);

    bool hasPathTo(const std::pair<int, int> &v) const;
    double distTo(const std::pair<int, int> &v) const;
    std::vector<Edge> pathTo(const std::pair<int, int> &v) const;

private:
    void relax(const Edge &e);

    std::map<std::pair<int, int>, Edge> edgeTo;
    double distTo(const std::pair<int, int>& v) const;

    struct QueueItem
    {
        std::pair<int, int> vertex;
        double priority;
        bool operator>(const QueueItem &other) const
        {
            return priority > other.priority;
        }
    };

    std::priority_queue<QueueItem, std::vector<QueueItem>, std::greater<QueueItem>> pq;
    std::map<std::pair<int, int>, std::vector<Edge>> graph;
};

#endif