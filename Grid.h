#ifndef GRID_H
#define GRID_H
#include <vector>


class Grid {
private:
    int height;
    int width;
    std::vector<std::vector<bool>> Gmap;

public:

    Grid();
    Grid(int nbrheight, int nbrwidth);

    int get_height() { return height; }
    int get_width() { return width; }
    int set_height(int nbr);
    int set_width(int nbr);
    std::vector<std::vector<bool>> modify(int x, int y, bool b);
    void Affichemap();
};



#endif //GRID_H
