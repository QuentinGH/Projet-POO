#include <SFML/Graphics.hpp>
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
    Game jeu(values.first, values.second);

    jeu.modify(0, 0, 1);
    jeu.modify(1, 1, 1);
    jeu.modify(2, 1, 1);
    jeu.modify(1, 3, 1);
    jeu.modify(-1, 0,1);
    jeu.modify(1, 0, 1);
    jeu.Affichemap();

// à mettre dans une classe à part : problème avec Game::behavior & Game::detection
    int size_value_h = 800;
    int size_value_w = 800;
    int size_cell;
    if (values.first > values.second) {
        size_cell = size_value_h / values.first;
        size_value_w -= (size_cell * values.first - size_cell * values.second);
    }
    else {
        size_cell = size_value_w / values.second;
        size_value_h -= (size_cell * values.second - size_cell * values.first);
    }
    int size_outline = size_cell / 16;

    sf::RenderWindow window(sf::VideoMode(size_value_w, size_value_h), "Life's Game");

    while (window.isOpen())
    {
        window.setFramerateLimit(1);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int count_1 = 0; count_1 < values.first; count_1++) {
            for (int count_2 = 0; count_2 < values.second; count_2++) {
                sf::RectangleShape square(sf::Vector2f((values.first * size_cell) / values.first, (values.second * size_cell) / values.second));
                square.setOutlineColor(sf::Color::Black);
                square.setOutlineThickness(size_outline);
                square.setPosition(size_cell * count_2, size_cell * count_1);

                if (jeu.get_Gmap()[count_2][count_1] == true) {
                    square.setFillColor(sf::Color::Black);
                }
                else if (jeu.get_Gmap()[count_2][count_1] == false) {
                    square.setFillColor(sf::Color::White);
                }
                window.draw(square);
                jeu.behavior(count_2, count_1);
            }
        }
        window.display();
        jeu.Affichemap();
    }

    return 0;
}
