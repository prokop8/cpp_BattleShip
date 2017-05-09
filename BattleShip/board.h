#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>

class Board : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Board(QGraphicsScene *scene, int x, int y);
    QGraphicsScene *scene;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
private:
    int x;
    int y;
    int color;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

signals:
    void Clicked(int x, int y);
    void changeNumberOfShips(int color);

private slots:
     void changeColor(int x, int y, int color);

};

#endif // BOARD_H
