#include "CL_Window.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>

CL_Window::CL_Window(int h, int w) {
    this->height = h;
    this->width = w;
    set_size_cell(this->height, this->width);
}

void CL_Window::set_size_h(int setting) {
    this->height = setting;
}

void CL_Window::set_size_w(int setting) {
    this->width = setting;
}

void CL_Window::set_size_cell(int h, int w) {
    if (h <= 0 || w <= 0) {
        std::cerr << "Invalid grid dimensions: height and width must be positive." << std::endl;
        return;
    }
    if (h > w) {
        this->size_cell = this->size_h / h;
        this->size_w -= (this->size_cell * h - this->size_cell * w);
    }
    else {
        this->size_cell = this->size_w / w;
        this->size_h -= (this->size_cell * w - this->size_cell * h);
    }
    this->size_outline = this->size_cell / 16;
}

void CL_Window::eternity(Grid& jeu) {
    sf::RenderWindow wind(sf::VideoMode(this->size_w, this->size_h), "Life's Game");
    int counter = 1;
    while (wind.isOpen())
    {
        wind.setFramerateLimit(60);
        sf::Event event;
        while (wind.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                wind.close();
        }

        sf::RectangleShape square(sf::Vector2f((this->height * this->size_cell) / this->height, (this->width * this->size_cell) / this->width));
        square.setOutlineColor(sf::Color::Black);
        square.setOutlineThickness(this->size_outline);

        wind.clear();
        for (int count_1 = 0; count_1 < this->height; count_1++) {
            for (int count_2 = 0; count_2 < this->width; count_2++) {
                square.setPosition(this->size_cell * count_2, this->size_cell * count_1);

                if (jeu.get_Gmap()[count_1][count_2]->get_alive() == true) {
                    square.setFillColor(sf::Color::Black);
                }
                else {
                    square.setFillColor(sf::Color::White);
                }
                wind.draw(square);
                jeu.behavior(count_1, count_2);
            }
        }
        wind.display();
        jeu.Affichemap();
        std::cout << counter++ << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
