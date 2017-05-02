#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsRectItem>
#include "player.h"

class Game : public QObject
{
    Q_OBJECT

public:
    Game();
    ~Game();
    QGraphicsScene *scene1;
    QGraphicsScene *scene2;
    QGraphicsRectItem *playerField[10][10];
    QGraphicsRectItem *opponentField[10][10];
    Player *server;
    Player *client;
};

#endif // GAME_H
