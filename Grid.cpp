#include "Grid.h"
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <stdexcept>
#include <sstream>

Grid::Grid() {
    this->height = 0;
    this->width = 0;
    this->Gmap = std::vector<std::vector<bool>>(this->height, std::vector<bool>(this->width, false));
}

Grid::Grid(int nbrheight,int nbrwidth) {
    this->height = nbrheight;
    this->width = nbrwidth;
    this->Gmap.resize(height, std::vector<bool>(width, 0));
}

int Grid::set_height(int nbr) {
    return this->height = nbr;
}

int Grid::set_width(int nbr) {
    return this->width = nbr;
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

// Sauvegarder l'état actuel
void Grid::sauvegarder(const std::string& nom_fichier) {
    // Sauvegarder l'état actuel dans la pile
    sauvegardes.push(Gmap);

    // Ouvrir le fichier en mode append
    std::ofstream fichier(nom_fichier, std::ios::app);
    if (!fichier) {
        throw std::runtime_error("Impossible d'ouvrir le fichier de sauvegarde.");
    }

    // Sauvegarder les dimensions
    fichier << "Height: " << height << " Width: " << width << "\n";

    // Sauvegarder la grille
    for (const auto& ligne : Gmap) {
        for (bool cell : ligne) {
            fichier << cell << " ";
        }
        fichier << "\n";
    }
    fichier << "END\n"; // Indicateur de fin d'une sauvegarde
    fichier.close();
}

// Charger la dernière sauvegarde
void Grid::charger(const std::string& nom_fichier) {
    // Vérification si la pile de sauvegardes est vide
    if (sauvegardes.empty()) {
        throw std::runtime_error("Aucune sauvegarde disponible pour le chargement.");
    }

    // Charger le dernier état de la pile
    Gmap = sauvegardes.top(); // Récupérer le dernier état
    sauvegardes.pop(); // Supprimer cet état de la pile

    // Mettre à jour les dimensions
    height = Gmap.size();
    width = height > 0 ? Gmap[0].size() : 0;

    // Supprimer la dernière sauvegarde dans le fichier
    std::ifstream fichier_in(nom_fichier);
    if (!fichier_in) {
        throw std::runtime_error("Impossible d'ouvrir le fichier de sauvegarde pour lecture.");
    }

    std::ofstream fichier_temp("temp_sauvegarde.txt");
    if (!fichier_temp) {
        throw std::runtime_error("Impossible de créer le fichier temporaire.");
    }

    // Copie des sauvegardes restantes dans un fichier temporaire
    std::string ligne;
    int compteur_sauvegardes = 0;
    while (std::getline(fichier_in, ligne)) {
        if (ligne == "END") {
            compteur_sauvegardes++;
            if (compteur_sauvegardes == static_cast<int>(sauvegardes.size() + 1)) {
                break; // Arrêter de copier après la dernière sauvegarde valide
            }
        }
        fichier_temp << ligne << "\n";
    }

    fichier_in.close();
    fichier_temp.close();

    // Remplacement du fichier de sauvegarde par le fichier temporaire
    std::remove(nom_fichier.c_str());
    std::rename("temp_sauvegarde.txt", nom_fichier.c_str());
}
