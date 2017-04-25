#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"

class Player
{
public:
    Player();
    ~Player();
private:
    Ship *playerShips[10];
    int shipsLeft;
    int shipsPlaced;
};

#endif // PLAYER_H
