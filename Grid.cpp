#include "Grid.h"
#include <iostream>

Grid::Grid() {
    this->height = 0;
    this->width = 0;
    this->map = std::vector<std::vector<bool>>(this->height, std::vector<bool>(this->width, false));
}

Grid::Grid(int nbrheight,int nbrwidth) {
    this->height = nbrheight;
    this->width = nbrwidth;
    this->map = std::vector<std::vector<bool>>(this->height, std::vector<bool>(this->width, false));
}

int Grid::set_height(int nbr) { 
    this->height = nbr;
    return height; 
}

int Grid::set_width(int nbr) { 
    this->width = nbr;
    return width; 
}

void Grid::Affichemap() {
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            std::cout << map[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}
