#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>
#include "Grid.h"
#include <bits/stdc++.h>


int main() {
    Grid grille;
    std::pair<int, int> values;

    // Vider le fichier "grille_out" au démarrage
    std::ofstream fichier("C:/Users/quent/Documents/GitHub/Projet-POO/grille_out", std::ios::trunc);
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
    jeu.Affichemap();
    jeu.update();
    jeu.sauvegarder("C:/Users/quent/Documents/GitHub/Projet-POO/grille_out");

    jeu.modify(4, 1, 1);
    jeu.modify(2, 5, 1);
    jeu.update();
    jeu.Affichemap();
    jeu.sauvegarder("C:/Users/quent/Documents/GitHub/Projet-POO/grille_out");

    jeu.modify(1, 1, 1);
    jeu.modify(2, 1, 1);
    jeu.update();
    jeu.Affichemap();
    jeu.sauvegarder("C:/Users/quent/Documents/GitHub/Projet-POO/grille_out");

    jeu.modify(1, 3, 1);
    jeu.update();
    jeu.Affichemap();

    jeu.charger("C:/Users/quent/Documents/GitHub/Projet-POO/grille_out");
    jeu.Affichemap();
    jeu.charger("C:/Users/quent/Documents/GitHub/Projet-POO/grille_out");
    jeu.Affichemap();

    return 0;
}
