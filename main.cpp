#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>
#include "Grid.h"
#include "Game.h"


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

    Grid g(values.first,values.second);
    g.Affichemap();
    Game jeu(values.first,values.second);
    jeu.afficherCell(5,1);

    jeu.modify(1, 1, 1);
    jeu.Affichemap();

    jeu.modify(2, 1, 1);
    jeu.Affichemap();

    jeu.modify(1, 3, 1);
    jeu.Affichemap();


    return 0;
}
