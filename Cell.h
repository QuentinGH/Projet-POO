#ifndef CELL_H
#define CELL_H

class Cell {
private:
    int x;
    int y;
    bool alive;

public:

    Cell();
    Cell(int nbrx,int nbry);

    int get_x() const { return x; }
    int get_y() const { return y; }
    int set_x(int nbr);
    int set_y(int nbr);
    bool get_alive() const { return alive; };

    bool set_alive(bool b);

};



#endif //CELL_H
