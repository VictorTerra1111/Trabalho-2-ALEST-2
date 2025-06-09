#include <iostream>
#include "../HPPS/graphAssem.hpp"

using namespace std;

map<pair<int, int>, vector<Edge>> assembleDirGraph(const Map &vmap){
    map<pair<int, int>, vector<Edge>> graph;

    const auto& matrix = vmap.getMatrix();
    int lines = vmap.getLines();
    int columns = vmap.getColumns();

    vector <pair<int, int>> sealing = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    for(int i = 0; i < lines; ++i){
        for(int j = 0; j < columns; ++j){
            char current = matrix[i][j];
            
            if(current == '*' || current == ' ') continue;
            pair<int, int> source = {i, j};

            for(auto [x, y] : sealing){
                int numi = i + x;
                int numj = j + y;
                if(numi < 0 || numj < 0 || numi >= lines || numj >= columns)continue;

                char target = matrix[numi][numj];
                if(target == '*' || target == ' ') continue;
                pair<int, int> destiny = {numi, numj};
                double weight = 1.0;
                
                graph[source].push_back(Edge(source, destiny, weight));
            }
        }
    }
    return graph;
}
