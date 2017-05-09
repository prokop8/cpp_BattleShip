#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"

class Player
{
public:
    Player();
    ~Player();
    bool checkTurn = false;
    void setActiveShip(Ship *ship);
    Ship* getActiveShip();
    Ship* getShipPlacement(int x, int y);
    Ship* getPlayerShip(int number);
    bool getIsPlacingShip();
    int getBeginX();
    int getBeginY();
    int getShipsPlaced();
    int getShipsLeft();
    void decShipsLeft();
    bool getTurn();
    void setTurn(bool tmp);
    void setIsPlacingShip(bool tmp);
    void setBeginX(int x);
    void setBeginY(int y);
    void incShipsPlaced();
    void setHits(bool, int, int);
    bool getHits(int, int);
    bool isGameOver();
private:
    Ship *playerShips[10];
    bool hits[10][10] = {0};
    Ship *shipPlacement[10][10];
    int shipsLeft;
    int shipsPlaced;
    Ship *activeShip=new Ship(4);
    bool isPlacingShip;
    int beginX=0;
    int beginY=0;
};

#endif // PLAYER_H
