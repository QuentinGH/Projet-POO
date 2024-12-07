#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>
#include "Grid.h"
#include "Game.h"


int main() {
@@ -24,34 +23,32 @@
         << "\n- Height : " << values.first
         << "\n- Width : " << values.second << std::endl;

    Grid g(values.first,values.second);
    g.Affichemap();

    Game jeu(values.first,values.second);
    Grid jeu(values.first,values.second);
    jeu.Affichemap();
    jeu.afficherCell(5,1);
    jeu.sauvegarder("grille_out");

    jeu.modify(1, 1, 1);
    jeu.Affichemap();
    jeu.sauvegarder("grille_out");

    jeu.modify(2, 1, 1);
    jeu.Affichemap();
    jeu.sauvegarder("grille_out");

    jeu.modify(1, 3, 1);
    jeu.Affichemap();

    jeu.charger("grille_out");
    jeu.Affichemap();

    jeu.charger("grille_out");
    jeu.Affichemap();

    jeu.charger("grille_out");
    jeu.Affichemap();


    return 0;
}
