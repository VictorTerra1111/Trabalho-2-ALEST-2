#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include <map>

using namespace std;

class Map
{
    public:
        Map(const string &filePath);

        const vector<string> &getMatrix() const;
        int getLines() const;
        int getColumns() const;
        map<char, pair<int, int>> getHarbor() const;

    private:
        vector<string> matrix; 
        int lines; 
        int columns;
        map<char, pair<int, int>> harbors;

        void load(const string &filePath);
        void findHarbors();
};

#endif
