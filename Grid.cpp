#include "Grid.h"

Grid::Grid() {
    this->height = 0;
    this->width = 0;
}

Grid::Grid(int nbrheight,int nbrwidth) {
    this->height = nbrheight;
    this->width = nbrwidth;
}

int Grid::get_height() { 
    return this->height; 
}    

int Grid::get_width() { 
    return this->width; 
}

int Grid::set_height(int nbr) { 
    this->height = nbr;
    return height; 
}

int Grid::set_width(int nbr) { 
    this->width = nbr;
    return width; 
}
