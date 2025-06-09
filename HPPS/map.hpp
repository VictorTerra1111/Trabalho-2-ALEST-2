#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include <map>
#include <utility>

class Map
{
public:
    Map(const std::string &filePath);

    const std::vector<std::string> &getMatrix() const;
    int getLines() const;
    int getColumns() const;
    std::map<char, std::pair<int, int>> getHarbor() const;

private:
    std::vector<std::string> matrix; 
    int lines; 
    int columns;
    std::map<char, std::pair<int, int>> harbors;

    void load(const std::string &filePath);
    void findHarbors();
};

#endif
