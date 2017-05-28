#include "board.h"

Board::Board(QGraphicsScene *scene, int x, int y)
{
    this->x = x;
    this->y = y;
    this->color = 0;
    this->scene = scene;
    setFlag(ItemIsSelectable);
    this->scene->addItem(this);
}

QRectF Board::boundingRect() const
{
    return QRectF(0, 0, 50, 50);
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::white);

    if (color == 0)
    {
        brush.setColor(Qt::white);
    }
    else if (color == 1)
    {
        brush.setColor(Qt::yellow);
    }
    else if (color == 2)
    {
        brush.setColor(Qt::blue);
    }
    else if (color == 3)
    {
        brush.setColor(Qt::red);
    }
    else if (color == 4)
    {
        brush.setColor(Qt::gray);
    }
    painter->fillRect(rec,brush);
    painter->drawRect(rec);
}


void Board::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}


void Board::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit Clicked(x, y);
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Board::changeColor(int x, int y, int color)
{
    if(this->x==x && this->y==y)
    {
        if(color!=0)
        {
            //setEnabled(false);
            emit changeNumberOfShips(color);
        }
        /*else
            setEnabled(true);*/
        this->color = color;
        update();
    }
}
