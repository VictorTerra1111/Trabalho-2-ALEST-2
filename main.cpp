#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <limits>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

enum Dir
{
    NONE = -1,
    N,
    S,
    E,
    W
};

struct Pos
{
    int r, c;
    bool operator<(const Pos &other) const
    {
        return tie(r, c) < tie(other.r, other.c);
    }
    bool operator==(const Pos &other) const
    {
        return r == other.r && c == other.c;
    }
};

class Map
{
    vector<string> grid;
    map<int, Pos> ports;
    int rows, cols;

public:
    Map(int r, int c) : rows(r), cols(c)
    {
        grid.resize(r);
    }

    void load(ifstream &in)
    {
        for (int i = 0; i < rows; ++i)
        {
            getline(in, grid[i]);
            for (int j = 0; j < cols; ++j)
            {
                if (isdigit(grid[i][j]))
                {
                    int portNum = grid[i][j] - '0';
                    ports[portNum] = {i, j};
                }
            }
        }
    }

    char at(Pos p) const
    {
        return grid[p.r][p.c];
    }

    bool isInside(Pos p) const
    {
        return p.r >= 0 && p.r < rows && p.c >= 0 && p.c < cols;
    }

    bool isNavigable(Pos p) const
    {
        if (!isInside(p))
            return false;
        char ch = at(p);
        return ch == '.' || isdigit(ch);
    }

    Pos move(Pos p, Dir d) const
    {
        switch (d)
        {
        case N:
            return {p.r - 1, p.c};
        case S:
            return {p.r + 1, p.c};
        case E:
            return {p.r, p.c + 1};
        case W:
            return {p.r, p.c - 1};
        default:
            return p;
        }
    }

    const map<int, Pos> &getPorts() const
    {
        return ports;
    }

    Pos getPort(int id) const
    {
        return ports.at(id);
    }

    bool hasPort(int id) const
    {
        return ports.find(id) != ports.end();
    }
};

struct State
{
    Pos pos;
    int cost;
    Dir dir;

    bool operator>(const State &other) const
    {
        return cost > other.cost;
    }
};

class Navigator
{
    const Map &mapa;

public:
    Navigator(const Map &m) : mapa(m) {}

    int dijkstra(Pos start, Pos goal)
    {
        priority_queue<State, vector<State>, greater<State>> pq;
        map<pair<Pos, Dir>, int> dist;
        pq.push({start, 0, NONE});
        dist[{start, NONE}] = 0;

        while (!pq.empty())
        {
            State s = pq.top();
            pq.pop();

            if (s.pos == goal)
                return s.cost;

            for (int d = 0; d < 4; ++d)
            {
                Dir dir = static_cast<Dir>(d);
                Pos next = mapa.move(s.pos, dir);
                if (!mapa.isNavigable(next))
                    continue;

                int turnCost = (s.dir == NONE || s.dir == dir) ? 1 : 3;
                int newCost = s.cost + turnCost;

                auto key = make_pair(next, dir);
                if (!dist.count(key) || newCost < dist[key])
                {
                    dist[key] = newCost;
                    pq.push({next, newCost, dir});
                }
            }
        }

        return -1; // unreachable
    }
};

int main()
{
    ifstream file("TXTS/mapateste-80.txt");
    if (!file)
    {
        cerr << "Erro ao abrir mapateste-80.txt\n";
        return 1;
    }

    int rows, cols;
    file >> rows >> cols;
    file.ignore();

    Map mapa(rows, cols);
    mapa.load(file);

    Navigator nav(mapa);

    int totalFuel = 0;
    vector<int> inaccessiveis;
    map<int, int> trechoFuel;

    vector<int> rota = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1};

    size_t i = 0;
    while (i < rota.size() - 1)
    {
        int p1 = rota[i];
        int j = i + 1;

        while (j < rota.size())
        {
            int p2 = rota[j];

            if (!mapa.hasPort(p1))
            {
                inaccessiveis.push_back(p1);
                i = j;
                break;
            }

            if (!mapa.hasPort(p2))
            {
                inaccessiveis.push_back(p2);
                ++j;
                continue;
            }

            int cost = nav.dijkstra(mapa.getPort(p1), mapa.getPort(p2));
            if (cost == -1)
            {
                inaccessiveis.push_back(p2);
                ++j;
                continue;
            }

            trechoFuel[p1] = cost;
            totalFuel += cost;
            i = j;
            break;
        }

        if (j >= rota.size())
            break;
    }

    cout << "Mapa 100 – Combustível mínimo: " << totalFuel << "\n";

    for (size_t k = 0; k < rota.size() - 1; ++k)
    {
        int p1 = rota[k];
        int p2 = rota[k + 1];

        if (!mapa.hasPort(p1) || !mapa.hasPort(p2) ||
            find(inaccessiveis.begin(), inaccessiveis.end(), p1) != inaccessiveis.end() ||
            find(inaccessiveis.begin(), inaccessiveis.end(), p2) != inaccessiveis.end() ||
            trechoFuel.find(p1) == trechoFuel.end())
        {

            if (find(inaccessiveis.begin(), inaccessiveis.end(), p2) != inaccessiveis.end())
            {
                cout << "Porto " << p2 << " inacessível – ignorado)\n";
            }
            continue;
        }

        cout << "Trecho " << p1 << " -> " << p2 << ": " << trechoFuel[p1] << "\n";
    }

    return 0;
}