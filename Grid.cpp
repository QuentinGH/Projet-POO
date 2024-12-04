#include "Grid.h"
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <stdexcept>
#include <sstream>

Grid::Grid() : height(0), width(0) {
    Gmap = std::vector<std::vector<Cell*>>();
}


Grid::Grid(int nbrheight, int nbrwidth) : height(nbrheight), width(nbrwidth) {
    // Initialisation de Gmap avec des pointeurs
    Gmap = std::vector<std::vector<Cell*>>(height, std::vector<Cell*>(width, nullptr));

    // Création dynamique des Cellules
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Gmap[i][j] = new Cell(i, j); // Allouer une cellule avec ses coordonnées
        }
    }
}

Grid::~Grid() {
    for (auto& row : Gmap) {
        for (auto& cell : row) {
            delete cell; // Libère chaque pointeur
        }
        row.clear(); // Vide chaque ligne
    }
    Gmap.clear(); // Vide le vecteur principal
    while (!sauvegardes.empty()) {
        sauvegardes.pop();
    }
}


int Grid::set_height(int nbr) {
    return this->height = nbr;
}

int Grid::set_width(int nbr) {
    return this->width = nbr;
}

void Grid::modify(int x, int y, bool b) {
    if (x >= 0 && x < get_height() && y >= 0 && y < get_width()) {
        Gmap[x][y]->set_alive(b);  // Appel de la méthode sur l'objet Cell
    } else {
        throw std::runtime_error("Erreur : mauvaises coordonnées");
    }
}


void Grid::Affichemap() {
    for (size_t i = 0; i < Gmap.size(); i++) {
        for (size_t j = 0; j < Gmap[i].size(); j++) {
            std::cout << (Gmap[i][j]->get_alive() ? "1" : "0") << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}


Cell& Grid::getCell(int i, int j) {
    if (i < 0 || i >= height || j < 0 || j >= width) {
        throw std::out_of_range("Index hors limites");
    }

    return *(Gmap[i][j]);
}


void Grid::afficherCell(int i, int j) {
    try {
        Cell& cell = getCell(i, j);
        std::cout << "Cell (" << cell.get_x() << ", " << cell.get_y() << ")";
        std::cout << " - Alive: " << (cell.get_alive() ? "Yes" : "No") << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}

// Sauvegarder l'état actuel
void Grid::sauvegarder(const std::string& nom_fichier) {
    // Créer une copie profonde de Gmap
    std::vector<std::vector<Cell>> copie;
    for (const auto& ligne : Gmap) {
        std::vector<Cell> nouvelle_ligne;
        for (const auto& cell : ligne) {
            if (cell) {
                nouvelle_ligne.push_back(*cell); // Copier l'objet Cell pointé
            } else {
                throw std::runtime_error("Cellule non initialisée dans la grille.");
            }
        }
        copie.push_back(nouvelle_ligne);
    }

    sauvegardes.push(copie);  // Pousser la copie dans la pile

    // Sauvegarder dans un fichier (comme avant)
    std::ofstream fichier(nom_fichier, std::ios::app);
    if (!fichier) {
        throw std::runtime_error("Impossible d'ouvrir le fichier de sauvegarde.");
    }

    fichier << "Height: " << height << " Width: " << width << "\n";
    for (const auto& ligne : copie) {
        for (const auto& cell : ligne) {
            fichier << cell.get_alive() << " ";  // Sauvegarder seulement l'état de vie
        }
        fichier << "\n";
    }
    fichier << "END\n";
    fichier.close();
}


// Charger la dernière sauvegarde
void Grid::charger(const std::string& nom_fichier) {
    if (sauvegardes.empty()) {
        throw std::runtime_error("Aucune sauvegarde disponible pour le chargement.");
    }

    // Récupérer l'état sauvegardé
    auto copie = sauvegardes.top();
    sauvegardes.pop();

    // Nettoyer Gmap actuel
    for (auto& row : Gmap) {
        for (auto& cell : row) {
            delete cell;
        }
        row.clear();
    }
    Gmap.clear();

    // Recréer Gmap à partir de la copie
    height = copie.size();
    width = height > 0 ? copie[0].size() : 0;
    Gmap = std::vector<std::vector<Cell*>>(height, std::vector<Cell*>(width, nullptr));

    for (size_t i = 0; i < copie.size(); ++i) {
        for (size_t j = 0; j < copie[i].size(); ++j) {
            Gmap[i][j] = new Cell(copie[i][j]); // Copier chaque cellule
        }
    }
}




