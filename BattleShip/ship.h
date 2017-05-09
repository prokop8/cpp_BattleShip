#ifndef SHIP_H
#define SHIP_H

class Ship
{
public:
    Ship(int size);
    ~Ship();
    bool getIsPlaced();
    int getSize();
    int getHealth();
    void setIsPlaced(bool tmp);
    void setSize(int size);
    void setHealth(int health);
    void dealDamage();
    int getXBegin();
    int getYBegin();
    int getXEnd();
    int getYEnd();
    void setXBegin(int);
    void setYBegin(int);
    void setXEnd(int);
    void setYEnd(int);
private:
    bool isPlaced;
    int size;
    int health;
    int xBegin;
    int yBegin;
    int xEnd;
    int yEnd;
};

#endif // SHIP_H
