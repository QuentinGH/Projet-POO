#ifndef CL_WINDOW_H
#define CL_WINDOW_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include "Game.h"

class CL_Window {
private:
    int size_h = 800;
    int size_w = 800;
    int size_cell;
    int size_outline;
    int height;
    int width;

public:
    CL_Window(int h, int w);
    ~CL_Window() = default;

    int get_size_h() {return this->size_h;}
    int get_size_w() {return this->size_w;}
    int get_size_cell() {return this->size_cell;}
    int get_size_outline() {return this->size_outline;}
    int get_height() {return this->height;}
    int get_width() {return this->width;}
    void set_size_h(int setting);
    void set_size_w(int setting);
    void set_size_cell(int h, int w);
    void eternity(Game& jeu);
};

#endif