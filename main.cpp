#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <bits/stdc++.h>
#include "CL_Window.h"
#include "Grid.h"

int main() {
    Grid grille;
    std::pair<int, int> values;

    // Vider le fichier "grille_out" au démarrage
    std::ofstream fichier("C:/Users/guerr/CLionProjects/SFML_test/grille_out", std::ios::trunc);
    if (!fichier) {
        std::cerr << "Erreur : Impossible de vider le fichier de sauvegarde.\n";
    }
    fichier.close();

    while (values.first <=0 && values.second <= 0) {
        std::cout << "Vous pouvez saisir la valeur de la hauteur et de la largeur de la grille (l'une apres l'autre avec un espace entre elles): " << std::endl;

        std::string line;
        std::getline(std::cin, line); // Lire toute la ligne d'entrée

        std::stringstream ss(line); // Créer un flux de chaîne pour analyser la ligne
        ss >> values.first >> values.second; // Extraire les deux entiers
    }

    std::cout << "\nYour values are :"
         << "\n- Height : " << values.first
         << "\n- Width : " << values.second << std::endl;


    Grid jeu(values.first,values.second);

    std::cout << "Veuillez indiquer si vous souhaitez une grille torique ou non torique (1 = torique, 0 = non torique):" << std::endl;
    std::string commande;
    while (std::getline(std::cin, commande)) {
        if (commande == "1") {
            jeu.bool_toric = 1;
            std::cout << "Vous avez choisi : torique." << std::endl;
            break;
        }
        else if (commande == "0") {
            jeu.bool_toric = 0;
            std::cout << "Vous avez choisi : non torique." << std::endl;
            break;
        }
        else {
            std::cout << "\nEntrez oui ou non" << std::endl;
        }
    }
    jeu.charger("C:/Users/guerr/CLionProjects/SFML_test/grille_in");
    jeu.Affichemap();

    CL_Window wind(values.first, values.second);
    wind.eternity(jeu);

    jeu.sauvegarder("C:/Users/guerr/CLionProjects/SFML_test/grille_in");

    return 0;
}
