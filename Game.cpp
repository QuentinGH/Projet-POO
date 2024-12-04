#include "Game.h"
#include <stdexcept>
#include <iostream>

Game::Game(int nbr1, int nbr2) : Grid(nbr1, nbr2), taille1(nbr1), taille2(nbr2) {
    tab.resize(taille1 * taille2);
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
    delete[] tab.data();  // Utilisation de .data() pour récupérer le pointeur brut
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
        get_Gmap()[x][y] = b;  // Modifier la valeur dans la grille
        Cell& cell = getCell(x, y);  // Obtenir la cellule correspondante
        cell.set_alive(b);  // Mettre à jour l'état de la cellule
    }
    else {
        throw std::runtime_error("Erreur : mauvaises coordonnées");
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

int Game::detection(Cell &c) {
    int count = 0;
    for (int y = c.get_y()-1; y < c.get_y()+2; y++) {
        for (int x = c.get_x()-1; x < c.get_x()+2; x++) {
            Cell& cell = getCell(x, y);
            if (cell.get_alive() == true && cell.get_x() != c.get_x() && cell.get_y() != c.get_y()) {
                count++;
            }
        }
    }
    return count;
}

void Game::behavior(int x, int y) {
    Cell& c = getCell(x, y);
    int detec = detection(c);
    if (c.get_alive() && (detec == 2 || detec == 3)) {
        this->modify(c.get_x(), c.get_y(), true);
    }
    else if (!c.get_alive() && detec == 3) {
        this->modify(c.get_x(), c.get_y(), true);
    }
    else {
        this->modify(c.get_x(), c.get_y(), false);
    }
}
