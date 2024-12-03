#ifndef GRID_H
#define GRID_H
#include <vector>
#include <string>


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
    std::vector<std::vector<bool>>& get_Gmap() { return Gmap;}
    int set_height(int nbr);
    int set_width(int nbr);
    void Affichemap();
};



#endif //GRID_H
