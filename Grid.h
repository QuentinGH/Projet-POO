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

public:
    Grid();
    Grid(int nbrheight, int nbrwidth);
    ~Grid();

    bool bool_toric;
    Grid(const Grid& other);
    int get_height() const { return height; }
    int get_width() const { return width; }
    std::vector<std::vector<Cell*>>& get_Gmap() { return Gmap;}

    int set_height(int nbr);
    int set_width(int nbr);
    void Affichemap();
    void modify(int x, int y, bool b);
    void update();
    Cell& getCell(int i, int j);
    void afficherCell(int i, int j);

    int detection(Cell c, std::vector<std::vector<Cell*>> copy);
    std::vector<std::vector<Cell*>> behavior(int x, int y);

    void sauvegarder(const std::string& nom_fichier);
    void charger(const std::string& nom_fichier);
};



#endif //GRID_H
