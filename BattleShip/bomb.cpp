#include "bomb.h"

Bomb::Bomb()
{
    isPlaced=false;
}

int Bomb::getX()
{
    return this->x;
}

int Bomb::getY()
{
    return this->y;
}

bool Bomb::getIsPlaced()
{
    return this->isPlaced;
}

void Bomb::setX(int x)
{
    this->x=x;
}

void Bomb::setY(int y)
{
    this->y=y;
}

void Bomb::setIsPlaced(bool isPlaced)
{
    this->isPlaced=isPlaced;
}
