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
        std::cout << "You may enter the value of the grid's height and width (one after the other with a space between them): " << std::endl;

        std::string line;
        std::getline(std::cin, line); // Lire toute la ligne d'entrée

        std::stringstream ss(line); // Créer un flux de chaîne pour analyser la ligne
        ss >> values.first >> values.second; // Extraire les deux entiers
    }

    std::cout << "\nYour values are :"
         << "\n- Height : " << values.first
         << "\n- Width : " << values.second << std::endl;


    Grid jeu(values.first,values.second);
    /*
    jeu.modify(1, 9, 1);
    jeu.modify(1, 10, 1);
    jeu.modify(1, 11, 1);

    jeu.modify(2, 3, 1);
    jeu.modify(2, 4, 1);
    jeu.modify(2, 5, 1);

    jeu.modify(2, 8, 1);
    jeu.modify(2, 9, 1);
    jeu.modify(2, 10, 1);

    jeu.modify(6, 6, 1);
    jeu.modify(6, 7, 1);
    jeu.modify(7, 6, 1);

    jeu.modify(8, 9, 1);
    jeu.modify(9, 8, 1);
    jeu.modify(9, 9, 1);
    */
    jeu.charger("C:/Users/guerr/CLionProjects/SFML_test/grille_in");
    jeu.Affichemap();

    CL_Window wind(values.first, values.second);
    wind.eternity(jeu);

    jeu.sauvegarder("C:/Users/guerr/CLionProjects/SFML_test/grille_in");

    return 0;
}
