#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <stack>
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
    int get_height() const { return height; }
    int get_width() const { return width; }
    std::vector<std::vector<Cell*>>& get_Gmap() { return Gmap; }

    int set_height(int nbr);
    int set_width(int nbr);
    void modify(int x, int y, bool b);
    void update();
    void Affichemap();
    Cell& getCell(int i, int j);
    void afficherCell(int i, int j);

    void sauvegarder(const std::string& nom_fichier);
    void charger(const std::string& nom_fichier);
};

#endif // GRID_H
