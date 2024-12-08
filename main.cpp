#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <bits/stdc++.h>
#include "CL_Window.h"
#include "Grid.h"

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

    // Test constructeur
    std::cout << "CL_Window Test 1 (Constructeur): ";
    CL_Window window(10, 10);
    if (window.get_height() == 10 && window.get_width() == 10 &&
        window.get_size_h() == 800 && window.get_size_w() == 800) {
        std::cout << "Pass" << std::endl;
        } else {
            std::cout << "Fail" << std::endl;
        }

    // Test setters
    std::cout << "CL_Window Test 2 (Setters): ";
    window.set_size_h(700);
    window.set_size_w(700);
    if (window.get_size_h() == 700 && window.get_size_w() == 700) {
        std::cout << "Pass" << std::endl;
    } else {
        std::cout << "Fail" << std::endl;
    }

    // Test méthode set_size_cell
    std::cout << "CL_Window Test 3 (set_size_cell): ";
    window.set_size_cell(20, 20);  // Exemple de configuration
    if (window.get_size_cell() == 35) {  // Supposons que cette méthode configure correctement
        std::cout << "Pass" << std::endl;
    } else {
        std::cout << "Fail" << std::endl;
    }

    // Test méthode eternity
    std::cout << "CL_Window Test 4 (eternity avec Grid): ";
    Grid grid(10, 10);
    grid.modify(5, 5, true);
    grid.modify(5, 6, true);
    grid.modify(5, 7, true);  // Exemple d'initialisation pour un motif

    try {
        window.eternity(grid);  // On vérifie que cette méthode peut fonctionner
        std::cout << "Pass" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Fail: Exception attrapée - " << e.what() << std::endl;
    }

    std::cout << "=== TESTS TERMINEES ===" << std::endl;
}

int main() {

    test();

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
            std::cout << "\nEntrez 1 ou 0" << std::endl;
        }
    }
    jeu.charger("C:/Users/guerr/CLionProjects/SFML_test/grille_in");
    jeu.Affichemap();

    CL_Window wind(values.first, values.second);
    wind.eternity(jeu);

    jeu.sauvegarder("C:/Users/guerr/CLionProjects/SFML_test/grille_in");

    return 0;
}
