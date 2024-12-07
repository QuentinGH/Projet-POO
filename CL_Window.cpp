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

    sf::RectangleShape square(sf::Vector2f((this->height * this->size_cell) / this->height, (this->width * this->size_cell) / this->width));
    square.setOutlineColor(sf::Color(200, 200, 200));
    square.setOutlineThickness(this->size_outline);

    int user_x = 0;
    int user_y = 0;
    sf::RectangleShape user(sf::Vector2f(((this->height*0.60) * this->size_cell) / this->height, ((this->width*0.60) * this->size_cell) / this->width));
    user.setFillColor(sf::Color::Green);
    user.setOutlineColor(sf::Color(200, 200, 200));
    user.setOutlineThickness(this->size_outline);
    user.setPosition(this->size_cell * user_x, this->size_cell * user_y);

    int time = 501;
    int counter = 1;
    bool run = false;
    while (wind.isOpen()) {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && user_x > 0) {user_x--;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && user_x < this->width - 1) {user_x++;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && user_y > 0) {user_y--;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && user_y < this->height - 1) {user_y++;}

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            jeu.modify(user_y, user_x-1, 1);
            jeu.modify(user_y+1, user_x, 1);
            jeu.modify(user_y+1, user_x+1, 1);
            jeu.modify(user_y, user_x+1, 1);
            jeu.modify(user_y-1, user_x+1, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            jeu.modify(user_y, user_x, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            time -= 100;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            time += 100;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            run = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            run = false;
        }

        wind.setFramerateLimit(60);
        sf::Event event;
        while (wind.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                wind.close();
        }

        if (run) {
            wind.clear();
            for (int count_1 = 0; count_1 < this->height; count_1++) {
                for (int count_2 = 0; count_2 < this->width; count_2++) {
                    square.setPosition(this->size_cell * count_2, this->size_cell * count_1);

                    if (jeu.get_Gmap()[count_1][count_2]->get_alive() == true) {
                        square.setFillColor(sf::Color::White);
                    }
                    else {
                        square.setFillColor(sf::Color::Black);
                    }
                    wind.draw(square);
                    jeu.behavior(count_1, count_2);
                }
            }
            user.setPosition(this->size_cell * user_x, this->size_cell * user_y);
            wind.draw(user);
            jeu.update();
            jeu.sauvegarder("C:/Users/guerr/CLionProjects/SFML_test/grille_out");
            wind.display();
            jeu.Affichemap();
            std::cout << counter++ << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(time));
        }
    }
}
