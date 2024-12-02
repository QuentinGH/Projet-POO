#include "Grid.h"
#include <iostream>

Grid::Grid() {
    this->height = 0;
    this->width = 0;
    this->Gmap = std::vector<std::vector<bool>>(this->height, std::vector<bool>(this->width, false));
}

Grid::Grid(int nbrheight,int nbrwidth) {
    this->height = nbrheight;
    this->width = nbrwidth;
    this->Gmap = std::vector<std::vector<bool>>(this->height, std::vector<bool>(this->width, false));
}

int Grid::set_height(int nbr) {
    return this->height = nbr;
}

int Grid::set_width(int nbr) {
    return this->width = nbr;
}

std::vector<std::vector<bool>> Grid::modify(int x, int y, bool b) {
    if (x >= 0 && x < height && y >= 0 && y < width) {
        this->Gmap[x][y] = b; // Modify the value at position (x, y)
    }
    else {
        throw std::runtime_error("Erreur : mauvaises coordonées");
    }
    return Gmap;
}

void Grid::Affichemap() {
    for (size_t i = 0; i < Gmap.size(); i++) {
        for (size_t j = 0; j < Gmap[i].size(); j++) {
            std::cout << Gmap[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}
