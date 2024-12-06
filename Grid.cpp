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

Grid::Grid(const Grid& other) {
    this->height = other.height;
    this->width = other.width;
    this->Gmap = other.Gmap;
}

int Grid::set_height(int nbr) {
    return this->height = nbr;
}

int Grid::set_width(int nbr) {
    return this->width = nbr;
}

void Grid::modify(int x, int y, bool b) {
    if (x >= 0 && x < get_height() && y >= 0 && y < get_width()) {
        Gmap[x][y]->set_alive_next(b);
        std::cout << "Cell (" << x << ", " << y << ") set to " << (b ? "alive" : "dead") << " in next state.\n";
    } else {
        throw std::runtime_error("Erreur : mauvaises coordonnées");
    }
}


void Grid::update() {
    for (size_t i = 0; i < Gmap.size(); ++i) {
        for (size_t j = 0; j < Gmap[i].size(); ++j) {
            Gmap[i][j]->set_alive(Gmap[i][j]->get_next());
            Gmap[i][j]->set_alive_next(false); // Réinitialisation explicite
        }
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

int Grid::detection(Cell c, std::vector<std::vector<Cell*>> copy) {
    int left;
    int right;
    int top;
    int bot;
    int count = 0;

    if (c.get_y()-1 < 0) {left = this->width - (abs(c.get_y()-1) % this->width);}
    else {left = (c.get_y()-1) % this->width;}
    if (c.get_y()+1 < 0) {right = this->width - (abs(c.get_y()+1) % this->width);}
    else {right = (c.get_y()+1) % this->width;}
    if (c.get_x()-1 < 0) {top = this->height - (abs(c.get_x()-1) % this->height);}
    else {top = (c.get_x()-1) % this->height;}
    if (c.get_x()+1 < 0) {bot = this->height - (abs(c.get_x()+1) % this->height);}
    else {bot = (c.get_x()+1) % this->height;}

    if (copy[top][left]->get_alive() == true) {count++;}
    if (copy[top][c.get_y()]->get_alive() == true) {count++;}
    if (copy[top][right]->get_alive() == true) {count++;}

    if (copy[c.get_x()][left]->get_alive() == true) {count++;}
    if (copy[c.get_x()][right]->get_alive() == true) {count++;}

    if (copy[bot][left]->get_alive() == true) {count++;}
    if (copy[bot][c.get_y()]->get_alive() == true) {count++;}
    if (copy[bot][right]->get_alive() == true) {count++;}

    return count;
}

std::vector<std::vector<Cell*>> Grid::behavior(int x, int y) {
    Grid *game_copy = new Grid(*this);
    std::vector<std::vector<Cell*>> copy = this->get_Gmap();
    Cell& c = this->getCell(x, y);
    Cell& c2 = game_copy->getCell(x, y);
    int detec = detection(c, this->Gmap);
    if (c.get_alive() == 1 && detec < 2) {
        game_copy->modify(c2.get_x(), c2.get_y(), false);
    }
    else if (c.get_alive() == 1 && (detec == 2 || detec == 3)) {
        game_copy->modify(c2.get_x(), c2.get_y(), true);
    }
    else if (c.get_alive() == 1  && detec > 3) {
        game_copy->modify(c2.get_x(), c2.get_y(), false);
    }
    else if (c.get_alive() == 0 && detec == 3) {
        game_copy->modify(c2.get_x(), c2.get_y(), true);
    }
    return this->Gmap = game_copy->get_Gmap();
}

// Sauvegarder l'état actuel
void Grid::sauvegarder(const std::string& nom_fichier) {
    // Écriture dans un fichier sans effacer le contenu existant
    std::ofstream fichier(nom_fichier, std::ios::app); // Mode append
    if (!fichier) {
        throw std::runtime_error("Impossible d'ouvrir le fichier de sauvegarde.");
    }

    // Sauvegarde des dimensions de la grille
    fichier << height << " " << width << "\n";

    // Sauvegarde de l'état des cellules
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            fichier << Gmap[i][j]->get_alive() << " ";
        }
        fichier << "\n";
    }
    fichier << "---\n"; // Séparateur pour indiquer un nouvel état
    fichier.close();

    std::cout << "Grille sauvegardee dans le fichier '" << nom_fichier << "'.\n";
}


// Charger la dernière sauvegarde
void Grid::charger(const std::string& nom_fichier) {
    std::ifstream fichier(nom_fichier);
    if (!fichier) {
        throw std::runtime_error("Impossible d'ouvrir le fichier de chargement.");
    }

    std::vector<std::vector<std::string>> all_states;
    std::vector<std::string> current_state;
    std::string line;

    // Lecture de tous les états dans le fichier
    while (std::getline(fichier, line)) {
        if (line == "---") {
            all_states.push_back(current_state); // Sauvegarder l'état
            current_state.clear();              // Réinitialiser pour le prochain
        } else {
            current_state.push_back(line);
        }
    }
    if (!current_state.empty()) {
        all_states.push_back(current_state); // Dernier état
    }
    fichier.close();

    // Si aucun état n'existe
    if (all_states.empty()) {
        std::cerr << "Aucun etat trouve dans le fichier.\n";
        return;
    }

    // Charger le dernier état disponible
    auto last_state = all_states.back();
    all_states.pop_back(); // Supprimer le dernier état pour permettre un retour en arrière
    std::ofstream output(nom_fichier, std::ios::trunc); // Réécrire le fichier sans cet état
    for (const auto& state : all_states) {
        for (const auto& line : state) {
            output << line << "\n";
        }
        output << "---\n";
    }
    output.close();

    // Analyse du dernier état
    std::istringstream iss(last_state[0]); // Première ligne : dimensions
    int new_height, new_width;
    iss >> new_height >> new_width;

    // Nettoyage de la grille actuelle
    for (auto& row : Gmap) {
        for (auto& cell : row) {
            delete cell;
        }
    }
    Gmap.clear();

    // Recréation de la grille
    height = new_height;
    width = new_width;
    Gmap = std::vector<std::vector<Cell*>>(height, std::vector<Cell*>(width, nullptr));

    // Charger les cellules
    for (int i = 0; i < height; ++i) {
        std::istringstream row_stream(last_state[i + 1]); // +1 pour ignorer la ligne dimensions
        for (int j = 0; j < width; ++j) {
            int alive_state;
            row_stream >> alive_state;
            Gmap[i][j] = new Cell(i, j);
            Gmap[i][j]->set_alive(alive_state == 1);
        }
    }

    std::cout << "Grille chargee depuis le fichier '" << nom_fichier << "'.\n";
}
