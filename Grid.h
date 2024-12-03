#ifndef GRID_H
#define GRID_H
#include <vector>
#include <string>
#include <stack>

class Grid {
private:
    int height;
    int width;
    std::vector<std::vector<bool>> Gmap;
    std::stack<std::vector<std::vector<bool>>> sauvegardes; // Pile pour sauvegardes successives

public:
    Grid();
    Grid(int nbrheight, int nbrwidth);

    int get_height() { return height; }
    int get_width() { return width; }
    std::vector<std::vector<bool>>& get_Gmap() { return Gmap; }
    int set_height(int nbr);
    int set_width(int nbr);
    void Affichemap();

    // Sauvegarde et chargement
    void sauvegarder(const std::string& nom_fichier);
    void charger(const std::string& nom_fichier);
};

#endif //GRID_H
