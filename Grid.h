#ifndef GRID_H
#define GRID_H



class Grid {
private:
    int height;
    int width;

public:

    Grid();
    Grid(int nbrheight, int nbrwidth);

    int get_height() { return height; }
    int get_width() { return width; }
    int set_height(int nbr) { return height; }
    int set_width(int nbr) { return width; }
};



#endif //GRID_H
