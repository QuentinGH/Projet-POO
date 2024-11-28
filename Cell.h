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

    int get_x() { return x; }
    int get_y() { return y; }
    int set_x(int nbr);
    int set_y(int nbr);
    bool get_alive();

};



#endif //CELL_H
