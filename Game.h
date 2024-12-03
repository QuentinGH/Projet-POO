#ifndef GAME_H
#define GAME_H

#include "Cell.h"
#include "Grid.h"

class Game : public Grid {
private:
    int taille1;
    int taille2;
    Cell** tab;

public:
    Game(int nbr1, int nbr2);
    ~Game();

    int getTaille1();
    int getTaille2();
    Cell& getCell(int i, int j);
    void modify(int x, int y, bool b);
    void afficherCell(int i, int j);
};

#endif // GAME_H
