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

Cell& Game::getCell(int i, int j) {/*
    if (i < 0 || i >= taille1 || j < 0 || j >= taille2) {
        throw std::out_of_range("Index hors limites");
    }*/
    return *tab[i * taille2 + j];
}

void Game::modify(int x, int y, bool b) {
    int toric_x = toricX(x);
    int toric_y = toricY(y);
    if (toric_x >= 0 && toric_x < get_height() && toric_y >= 0 && toric_y < get_width()) {
        get_Gmap()[toric_x][toric_y] = b;  // Modifier la valeur dans la grille
        Cell& cell = getCell(toric_x, toric_y);  // Obtenir la cellule correspondante
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
    int toric_x = toricX(c.get_x());
    int toric_y = toricY(c.get_y());
    int count = 0;
    for (int y = toric_x-1; y <= toric_x+1; y++) {
        for (int x = toric_y-1; x <= toric_y+1; x++) {
            Cell& cell = getCell(toric_x, toric_y);
            if (cell.get_alive() && cell.get_x() != c.get_x() && cell.get_y() != c.get_y()) {
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

int Game::toricX(int x) {
    int toric_x = (x + this->taille2) % this->taille2;
    return toric_x;
}

int Game::toricY(int y) {
    int toric_y = (y + this->taille1) % this->taille1;
    return toric_y;
}
