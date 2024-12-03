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
    for (auto cell : tab) {
        delete cell; // Supprime chaque cellule
    }
    tab.clear(); // Vide le vecteur pour éviter les références invalides
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
        // Modifier la valeur dans la grille
        get_Gmap()[x][y] = b;

        getCell(x, y).set_alive(b);

        syncTabWithGmap();
    } else {
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

void Game::syncGmapWithTab() {
    for (int i = 0; i < taille1; ++i) {
        for (int j = 0; j < taille2; ++j) {
            get_Gmap()[i][j] = getCell(i, j).get_alive();
        }
    }
}

void Game::syncTabWithGmap() {
    for (int i = 0; i < taille1; ++i) {
        for (int j = 0; j < taille2; ++j) {
            getCell(i, j).set_alive(get_Gmap()[i][j]);
        }
    }
}

void Game::sauvegarder(const std::string& nom_fichier) {
    syncGmapWithTab(); // Synchronisation avant la sauvegarde
    Grid::sauvegarder(nom_fichier); // Appeler la sauvegarde de Grid
}

void Game::charger(const std::string& nom_fichier) {
    Grid::charger(nom_fichier); // Charger via Grid
    syncTabWithGmap(); // Synchronisation après le chargement
}

