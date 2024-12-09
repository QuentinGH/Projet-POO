#ifndef CELL_H
#define CELL_H

class Cell {
private:
    int x;
    int y;
    bool alive;
    bool next;

public:

    Cell();
    Cell(int nbrx,int nbry);

    int get_x() const { return x; }
    int get_y() const { return y; }
    bool get_alive() const { return alive; }
    bool get_next() const { return next; }
    void set_x(int nbr);
    void set_y(int nbr);
    void set_alive(bool b);
    void set_alive_next(bool b);

};



#endif //CELL_H
