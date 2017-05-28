#include "player.h"

Player::Player()
{
    shipsPlaced=0;
    shipsLeft=10;
    isPlacingShip=false;
    playerBomb[0]=new Bomb();
    playerBomb[1]=new Bomb();
    playerBomb[2]=new Bomb();
    playerBomb[3]=new Bomb();
    playerShips[0] = new Ship(4);
    playerShips[1] = new Ship(3);
    playerShips[2] = new Ship(3);
    playerShips[3] = new Ship(2);
    playerShips[4] = new Ship(2);
    playerShips[5] = new Ship(2);
    playerShips[6] = new Ship(1);
    playerShips[7] = new Ship(1);
    playerShips[8] = new Ship(1);
    playerShips[9] = new Ship(1);
    for(int i = 0; i<10; i++)
        for(int j = 0; j<10; j++)
        {
            shipPlacement[i][j] = new Ship(-1);
        }
}

Player::~Player()
{

}

void Player::setActiveShip(Ship *ship)
{
    this->activeShip=ship;
    for(int i=0;i<10;i++)
    {
        if(playerShips[i]->getSize()==ship->getSize() && !playerShips[i]->getIsPlaced())
            emit changedActiveShip(ship->getSize());
    }
}

Ship* Player::getShipPlacement(int x, int y)
{
    return shipPlacement[x][y];
}

bool Player::getIsPlacingShip()
{
    return isPlacingShip;
}

int Player::getBeginX()
{
    return beginX;
}

int Player::getBeginY()
{
    return beginY;
}

void Player::setBeginX(int x)
{
    this->beginX=x;
}

void Player::setBeginY(int y)
{
    this->beginY=y;
}

void Player::setIsPlacingShip(bool tmp)
{
    this->isPlacingShip=tmp;
}

Ship* Player::getActiveShip()
{
    return activeShip;
}

Ship* Player::getPlayerShip(int number)
{
    return playerShips[number];
}

void Player::incShipsPlaced()
{
    shipsPlaced++;
}

int Player::getShipsPlaced()
{
    return shipsPlaced;
}

bool Player::getTurn()
{
    return checkTurn;
}

void Player::setTurn(bool tmp)
{
    this->checkTurn = tmp;
}

int Player::getShipsLeft()
{
    return shipsLeft;
}

void Player::decShipsLeft()
{
    shipsLeft--;
}

bool Player::getHits(int x, int y)
{
    return hits[x][y];
}

void Player::setHits(bool tmp, int x, int y)
{
    hits[x][y] = &tmp;
}

bool Player::isGameOver()
{
    if(shipsLeft==0)
        return true;
    else
        return false;
}

Bomb* Player::getPlayerBomb(int number)
{
    return playerBomb[number];
}
