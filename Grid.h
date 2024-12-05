#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <Stack>
#include "Cell.h"


class Grid {
private:
    int height;
    int width;
    std::vector<std::vector<Cell*>> Gmap;
    std::stack<std::vector<std::vector<Cell>>> sauvegardes;

    void clearGmap();

public:
    Grid();
    Grid(int nbrheight, int nbrwidth);
    ~Grid();

    Grid(const Grid& other);
    Grid& operator=(const Grid& other);
    int get_height() { return height; }
    int get_width() { return width; }
    std::vector<std::vector<Cell*>>& get_Gmap() { return Gmap;}
    std::vector<std::vector<Cell*>>& set_Gmap(std::vector<std::vector<Cell*>>& g) { return Gmap = g;}

    int set_height(int nbr);
    int set_width(int nbr);
    void modify(int x, int y, bool b);
    void Affichemap();
    Cell& getCell(int i, int j);
    void afficherCell(int i, int j);

    int detection(Cell &c, std::vector<std::vector<Cell*>> &copy);
    std::vector<std::vector<Cell*>> behavior(int x, int y);

    void sauvegarder(const std::string& nom_fichier);
    void charger(const std::string& nom_fichier);
};



#endif //GRID_H
