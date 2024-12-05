#include "Cell.h"

Cell::Cell() {
    this->x = 0;
    this->y = 0;
    this->alive = 0;
    this->next = 0;
}

Cell::Cell(int nbrx,int nbry) {
    this->x = nbrx;
    this->y = nbry;
    this->alive = 0;
    this->next = 0;
}

void Cell::set_x(int nbr) {
    x = nbr;
}

void Cell::set_y(int nbr) {
    y = nbr;
}

void Cell::set_alive(bool b) {
    this->alive = b;
}

void Cell::set_alive_next(bool b) {
    this->next = b;
}
