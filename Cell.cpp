#include "Cell.h"

Cell::Cell() {
    this->x = 0;
    this->y = 0;
    this->alive = 0;
}

Cell::Cell(int nbrx,int nbry) {
    this->x = nbrx;
    this->y = nbry;
    this->alive = 0;
}

int Cell::set_x(int nbr) {
    return this->x = nbr;
}

int Cell::set_y(int nbr) { 
    return this->y = nbr;
}

bool Cell::set_alive(bool b) {
    return this->alive = b;
}
