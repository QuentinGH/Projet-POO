#include "CL_Window.h"

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

void CL_Window::eternity(Game& jeu) {
    sf::RenderWindow wind(sf::VideoMode(size_w, size_h), "Life's Game");
    while (wind.isOpen())
    {
        wind.setFramerateLimit(60);
        sf::Event event;
        while (wind.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                wind.close();
        }

        wind.clear();
        for (int count_1 = 0; count_1 < this->height; count_1++) {
            for (int count_2 = 0; count_2 < this->width; count_2++) {
                sf::RectangleShape square(sf::Vector2f((this->height * size_cell) / this->height, (this->width * size_cell) / this->width));
                square.setOutlineColor(sf::Color::Black);
                square.setOutlineThickness(size_outline);
                square.setPosition(size_cell * count_2, size_cell * count_1);

                if (jeu.get_Gmap()[count_1][count_2] == true) {
                    square.setFillColor(sf::Color::Black);
                }
                else if (jeu.get_Gmap()[count_1][count_2] == false) {
                    square.setFillColor(sf::Color::White);
                }
                wind.draw(square);
            }
        }
        wind.display();
        jeu.behavior(1, 1);
        jeu.Affichemap();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}