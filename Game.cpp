#include "Game.h"
#include <stdexcept>
#include <iostream>

Game::Game(int nbr1, int nbr2) : taille1(nbr1), taille2(nbr2) {
    tab = new Cell*[taille1 * taille2];
    for (int i = 0; i < taille1; i++) {
        for (int j = 0; j < taille2; j++) {
            tab[i * taille2 + j] = new Cell(i, j);
        }
    }
}

Game::~Game() {
    for (int i = 0; i < taille1 * taille2; i++) {
        delete tab[i];
    }
    delete[] tab;
}

int Game::getTaille1() {
    return taille1;
}

int Game::getTaille2() {
    return taille2;
}

Cell& Game::getCell(int i, int j) {
    if (i < 0 || i >= taille1 || j < 0 || j >= taille2) {
        throw std::out_of_range("Index hors limites");
    }
    return *tab[i * taille2 + j];
}

void Game::modify(int x, int y, bool b) {
    if (x >= 0 && x < get_height() && y >= 0 && y < get_width()) {
        get_Gmap()[x][y] = b; // Modify the value at position (x, y)
        Cell& cell = getCell(x, y);
        cell.set_alive(b);
    }
    else {
        throw std::runtime_error("Erreur : mauvaises coordonées");
    }
}

void Game::afficherCell(int i, int j) {
    try {
        Cell& cell = getCell(i, j);
        std::cout << "Cell (" << cell.get_x() << ", " << cell.get_y() << ")";
        std::cout << " - Alive: " << (cell.get_alive() ? "Yes" : "No") << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}