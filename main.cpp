#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>

#include "CL_Window.h"
#include "Grid.h"

int main() {
    Grid grille;
    std::pair<int, int> values;

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
    jeu.modify(0, 0, 1);
    jeu.sauvegarder("grille_out");
    jeu.modify(1, 1, 1);
    jeu.sauvegarder("grille_out");
    jeu.modify(2, 1, 1);
    jeu.sauvegarder("grille_out");
    jeu.modify(1, 3, 1);
    jeu.sauvegarder("grille_out");
    jeu.modify(-1, 0,1);
    jeu.sauvegarder("grille_out");
    jeu.modify(1, 0, 1);
    jeu.sauvegarder("grille_out");
    jeu.Affichemap();
*/
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
    jeu.Affichemap();

    CL_Window wind(values.first, values.second);
    wind.eternity(jeu);

    return 0;
}
