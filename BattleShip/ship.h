#ifndef SHIP_H
#define SHIP_H

class Ship
{
public:
    Ship(int size);
    ~Ship();
private:
    bool isPlaced;
    int size;
    int health;
};

#endif // SHIP_H
