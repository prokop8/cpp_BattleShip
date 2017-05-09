#include "ship.h"
#include "QDebug"

Ship::Ship(int size)
{
    isPlaced=false;
    this->size=size;
    health=size;
}

Ship::~Ship()
{

}

bool Ship::getIsPlaced()
{
    return isPlaced;
}

int Ship::getSize()
{
    return size;
}

void Ship::setIsPlaced(bool tmp)
{
    this->isPlaced=tmp;
}

void Ship::setSize(int size)
{
    this->size=size;
}

int Ship::getHealth()
{
    return health;
}

void Ship::setHealth(int health)
{
    this->health=health;
}

void Ship::dealDamage()
{
    this->health--;
}

int Ship::getXBegin()
{
    return xBegin;
}

void Ship::setXBegin(int xBegin)
{
    this->xBegin=xBegin;
}

int Ship::getYBegin()
{
    return yBegin;
}

void Ship::setYBegin(int yBegin)
{
    this->yBegin=yBegin;
}

int Ship::getXEnd()
{
    return xEnd;
}

void Ship::setXEnd(int xEnd)
{
    this->xEnd=xEnd;
}

int Ship::getYEnd()
{
    return yEnd;
}

void Ship::setYEnd(int yEnd)
{
    this->yEnd=yEnd;
}
