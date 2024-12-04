#ifndef GAME_H
#ifndef GAME_H
#define GAME_H

#include "Cell.h"
#include "Grid.h"

class Game : public Grid {
private:
    int taille1;
    int taille2;
    std::vector<Cell*> tab;

public:
    Game(int nbr1, int nbr2);
    ~Game();

    int getTaille1();
    int getTaille2();
    Cell& getCell(int i, int j);
    void modify(int x, int y, bool b);
    void afficherCell(int i, int j);
    void syncGmapWithTab();
    void syncTabWithGmap();
    void sauvegarder(const std::string& nom_fichier);
    void charger(const std::string& nom_fichier);
    int detection(Cell &c);
    void behavior(int x, int y);
    int toricX(int x);
    int toricY(int y);
};

#endif // GAME_H
