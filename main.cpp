    #include <iostream>
    #include <sstream>
    #include <iomanip>
    #include <utility>
    #include "Grid.h"
    #include <bits/stdc++.h>

void test() {
    std::cout << "=== TESTS UNITAIRES ===" << std::endl;

    // Test Cell
    Cell c1;
    c1.set_x(1);
    c1.set_y(2);
    c1.set_alive(true);

    std::cout << "Cell Test 1: ";
    if (c1.get_x() == 1 && c1.get_y() == 2 && c1.get_alive()) {
        std::cout << "Pass" << std::endl;
    } else {
        std::cout << "Fail" << std::endl;
    }

    // Test Grid initialisation
    Grid g(3, 3);
    std::cout << "Grid Test 1 (Dimensions): ";
    if (g.get_height() == 3 && g.get_width() == 3) {
        std::cout << "Pass" << std::endl;
    } else {
        std::cout << "Fail" << std::endl;
    }

    std::cout << "Grid Test 2 (Initial state): ";
    bool all_dead = true;
    for (int i = 0; i < g.get_height(); ++i) {
        for (int j = 0; j < g.get_width(); ++j) {
            if (g.getCell(i, j).get_alive()) {
                all_dead = false;
                break;
            }
        }
    }
    if (all_dead) {
        std::cout << "Pass" << std::endl;
    } else {
        std::cout << "Fail" << std::endl;
    }

    // Test modification
    g.modify(1, 1, true);
    g.update();
    std::cout << "Grid Test 3 (Modification): ";
    if (g.getCell(1, 1).get_alive()) {
        std::cout << "Pass" << std::endl;
    } else {
        std::cout << "Fail" << std::endl;
    }

    // Test sauvegarder et charger
    std::string test_file = "test_grid_out.txt";
    g.sauvegarder(test_file);

    Grid g2;
    g2.charger(test_file);
    std::cout << "Grid Test 4 (Sauvegarder/Charger): ";
    if (g2.get_height() == g.get_height() &&
        g2.get_width() == g.get_width() &&
        g2.getCell(1, 1).get_alive()) {
        std::cout << "Pass" << std::endl;
        } else {
            std::cout << "Fail" << std::endl;
        }

    std::cout << "=== TESTS TERMINEES ===" << std::endl;
}

int main() {

    test();

    
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

/*
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

    */

    jeu.charger("C:/Users/quent/Documents/GitHub/Projet-POO/grille_in");
    jeu.Affichemap();
    return 0;
}
