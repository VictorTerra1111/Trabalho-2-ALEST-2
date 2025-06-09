#include "../HPPS/graphAssem.hpp"
using namespace std;

map<pair<int, int>, vector<Edge>> assembleDirGraph(const Map &vmap){
    map<pair<int, int>, vector<Edge>> graph;

    const auto& matrix = vmap.getMatrix();
    int lines = vmap.getLines();
    int columns = vmap.getColumns();

    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            char current = matrix[i][j];
            if (current == '*') continue; // intransitável

            pair<int, int> source = {i, j};

            for (auto [dx, dy] : directions) {
                int ni = i + dx;
                int nj = j + dy;

                if (ni < 0 || nj < 0 || ni >= lines || nj >= columns)
                    continue;

                char target = matrix[ni][nj];
                if (target == '*') continue; // não pode transitar

                pair<int, int> destination = {ni, nj};
                double weight = 1.0; // água navegável

                graph[source].push_back(Edge(source, destination, weight));
            }
        }
    }

    return graph;
}
