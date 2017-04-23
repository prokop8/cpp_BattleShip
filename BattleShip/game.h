#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsRectItem>

class Game : public QObject
{
    Q_OBJECT

public:
    Game();
    ~Game();
    QGraphicsScene *scene;
    //QGraphicsScene *scene2;
    QGraphicsRectItem *field[10][10];
};

#endif // GAME_H
