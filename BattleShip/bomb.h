#ifndef BOMB_H
#define BOMB_H


class Bomb
{
public:
    Bomb();
    int getX();
    int getY();
    bool getIsPlaced();
    void setX(int);
    void setY(int);
    void setIsPlaced(bool);
private:
    int x;
    int y;
    bool isPlaced;
};

#endif // BOMB_H
