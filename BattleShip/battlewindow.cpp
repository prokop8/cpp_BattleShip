#include "battlewindow.h"
#include "ui_battlewindow.h"
#include <QDebug>
#include <QMessageBox>
#include "game.h"
#include "math.h"
#include "board.h"
#include <time.h>

BattleWindow::BattleWindow(QWidget *parent, Game* game) :
    QMainWindow(parent),
    ui(new Ui::BattleWindow)
{

    ui->setupUi(this);
    this->game = game;
    setOpponentShips();
    ui->graphicsView->setSceneRect(0,0,500,500);
    this->game->scene1=new QGraphicsScene(this);
    ui->graphicsView->setScene(this->game->scene1);
    ui->graphicsView->show();
    DrawPlayerBoard();

    ui->graphicsView_2->setSceneRect(0,0,500,500);
    this->game->scene2=new QGraphicsScene(this);
    ui->graphicsView_2->setScene(this->game->scene2);
    ui->graphicsView_2->show();
    DrawOpponentBoard();

    game->server->setTurn(true);
}

BattleWindow::~BattleWindow()
{
    delete ui;
}

void BattleWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    ui->graphicsView->fitInView(ui->graphicsView->sceneRect(), Qt::KeepAspectRatio);
    ui->graphicsView_2->fitInView(ui->graphicsView_2->sceneRect(), Qt::KeepAspectRatio);
}

void BattleWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    ui->graphicsView->fitInView(ui->graphicsView->sceneRect(), Qt::KeepAspectRatio);
    ui->graphicsView_2->fitInView(ui->graphicsView_2->sceneRect(), Qt::KeepAspectRatio);
}

void BattleWindow::DrawPlayerBoard()//rysuje pole gracza
{
    for (int n = 0, x = 0; n < 10; ++n, x += 50)
    {
        for (int m = 0, y = 0; m < 10; ++m, y += 50)
        {
            game->playerField[n][m] = new Board(game->scene1, x, y);
            game->playerField[n][m]->setPos(x,y);
            connect(this, SIGNAL(shipHere(int,int,int)), game->playerField[n][m], SLOT(changeColor(int,int,int)));
            if(game->server->getShipPlacement(n, m)->getIsPlaced())
                emit shipHere(x, y, 1);
        }
    }
}

void BattleWindow::DrawOpponentBoard()//rysuje pole komputera
{
    for (int n = 0, x = 0; n < 10; ++n, x += 50)
    {
        for (int m = 0, y = 0; m < 10; ++m, y += 50)
        {
            game->opponentField[n][m] = new Board(game->scene2, x, y);
            game->opponentField[n][m]->setPos(x,y);
            connect(game->opponentField[n][m], SIGNAL(Clicked(int,int)), this, SLOT(attackOpponentField(int,int)));
            connect(this, SIGNAL(completedAttack(int,int,int)), game->opponentField[n][m], SLOT(changeColor(int,int,int)));
            connect(this, SIGNAL(opponentAttack(int,int,int)), game->playerField[n][m], SLOT(changeColor(int,int,int)));


            /*connect(this, SIGNAL(opponentShipHere(int,int,int)), game->opponentField[n][m], SLOT(changeColor(int,int,int)));
            if(game->client->getShipPlacement(n, m)->getIsPlaced())
                emit opponentShipHere(x, y, 2);*/
        }
    }
    for(int i=0;i<4;i++)
    {
        int firstX=0;
        int firstY=0;
        int secondX=0;
        int secondY=0;
        int x_1=0;
        int y_1=0;
        int x_2=0;
        int y_2=0;
        int number=0;
        int x;
        int y;
        if(game->server->getPlayerBomb(i)->getIsPlaced())
        {
            x=game->server->getPlayerBomb(i)->getX();
            y=game->server->getPlayerBomb(i)->getY();
            if(game->client->getShipPlacement(x, y)->getSize()!=-1)
            {
                firstX=game->client->getShipPlacement(x, y)->getXBegin();
                firstY=game->client->getShipPlacement(x, y)->getYBegin();
                secondX=game->client->getShipPlacement(x, y)->getXEnd();
                secondY=game->client->getShipPlacement(x, y)->getYEnd();

                for(int i = 0; i<10; i++)
                {
                    if(game->client->getPlayerShip(i)->getXBegin() == firstX && game->client->getPlayerShip(i)->getYBegin() == firstY &&
                            game->client->getPlayerShip(i)->getXEnd() == secondX && game->client->getPlayerShip(i)->getYEnd() == secondY)
                    {
                        number = i;
                        break;
                    }
                }
                game->client->getPlayerShip(number)->dealDamage();
                emit completedAttack(x*50, y*50, 3);
                if(game->client->getPlayerShip(number)->getHealth() == 0)
                {
                    x_1=(firstX<=secondX)?firstX-1:secondX-1;
                    y_1=(firstY<=secondY)?firstY-1:secondY-1;
                    x_2=(firstX<=secondX)?secondX+1:firstX+1;
                    y_2=(firstY<=secondY)?secondY+1:firstY+1;
                    for(int i = y_1; i<y_2+1;i++)
                        for(int j = x_1; j<x_2+1;j++)
                        {
                            if(i>9 || j>9 || i<0 || j<0 || game->client->getShipPlacement(j, i)->getSize()!=-1)
                                continue;
                            emit completedAttack(j*50, i*50, 4);
                        }
                    game->client->decShipsLeft();
                }
            }
            else
            {
                emit completedAttack(x*50, y*50, 4);
            }
        }
    }
}

void BattleWindow::attackOpponentField(int first, int second)//slot kiedy gracz atakuje opponenta
{
    int x = first/50;
    int y = second/50;
    int firstX=0;
    int firstY=0;
    int secondX=0;
    int secondY=0;
    int x_1=0;
    int y_1=0;
    int x_2=0;
    int y_2=0;
    int number=0;
    if(game->server->getTurn())
    {

        if(game->client->getShipPlacement(x, y)->getSize()!=-1)
        {
            firstX=game->client->getShipPlacement(x, y)->getXBegin();
            firstY=game->client->getShipPlacement(x, y)->getYBegin();
            secondX=game->client->getShipPlacement(x, y)->getXEnd();
            secondY=game->client->getShipPlacement(x, y)->getYEnd();

            for(int i = 0; i<10; i++)
            {
                if(game->client->getPlayerShip(i)->getXBegin() == firstX && game->client->getPlayerShip(i)->getYBegin() == firstY &&
                        game->client->getPlayerShip(i)->getXEnd() == secondX && game->client->getPlayerShip(i)->getYEnd() == secondY)
                {
                    number = i;
                    break;
                }
            }
            game->client->getPlayerShip(number)->dealDamage();
            emit completedAttack(first, second, 3);
            if(game->client->getPlayerShip(number)->getHealth() == 0)
            {
                x_1=(firstX<=secondX)?firstX-1:secondX-1;
                y_1=(firstY<=secondY)?firstY-1:secondY-1;
                x_2=(firstX<=secondX)?secondX+1:firstX+1;
                y_2=(firstY<=secondY)?secondY+1:firstY+1;
                for(int i = y_1; i<y_2+1;i++)
                    for(int j = x_1; j<x_2+1;j++)
                    {
                        if(i>9 || j>9 || i<0 || j<0 || game->client->getShipPlacement(j, i)->getSize()!=-1)
                            continue;
                        emit completedAttack(j*50, i*50, 4);
                    }
                game->client->decShipsLeft();
                if(game->client->isGameOver())
                {
                    QMessageBox::information(
                        this,
                        tr("Game Over"),
                        tr("You win!") );
                    QApplication::quit();
                }
            }
        }
        else
        {
            emit completedAttack(first, second, 4);
            game->server->setTurn(false);
            game->client->setTurn(true);
            attackPlayerField();
        }
    }
}

void BattleWindow::attackPlayerField()//randomowa funkcja zeby opponent atakowal gracza
{
    srand ( time(NULL) );
    int x = 0;
    int y = 0;
    bool check=false;
    while(!check)
    {
        x = rand() % 10;
        y = rand() % 10;
        if(game->client->getHits(x, y)==false)
        {
            check=true;
            game->client->setHits(true, x, y);
        }
    }
    int firstX=0;
    int firstY=0;
    int secondX=0;
    int secondY=0;
    int x_1=0;
    int y_1=0;
    int x_2=0;
    int y_2=0;
    int number=0;
    if(game->client->getTurn())
    {

        if(game->server->getShipPlacement(x, y)->getSize()!=-1)
        {
            firstX=game->server->getShipPlacement(x, y)->getXBegin();
            firstY=game->server->getShipPlacement(x, y)->getYBegin();
            secondX=game->server->getShipPlacement(x, y)->getXEnd();
            secondY=game->server->getShipPlacement(x, y)->getYEnd();

            for(int i = 0; i<10; i++)
            {
                if(game->server->getPlayerShip(i)->getXBegin() == firstX && game->server->getPlayerShip(i)->getYBegin() == firstY &&
                        game->server->getPlayerShip(i)->getXEnd() == secondX && game->server->getPlayerShip(i)->getYEnd() == secondY)
                {
                    number = i;
                    break;
                }
            }
            game->server->getPlayerShip(number)->dealDamage();
            emit opponentAttack(x*50, y*50, 3);
            if(game->server->getPlayerShip(number)->getHealth() == 0)
            {
                x_1=(firstX<=secondX)?firstX-1:secondX-1;
                y_1=(firstY<=secondY)?firstY-1:secondY-1;
                x_2=(firstX<=secondX)?secondX+1:firstX+1;
                y_2=(firstY<=secondY)?secondY+1:firstY+1;
                for(int i = y_1; i<y_2+1;i++)
                    for(int j = x_1; j<x_2+1;j++)
                    {
                        if(i>9 || j>9 || i<0 || j<0 || game->server->getShipPlacement(j, i)->getSize()!=-1)
                            continue;
                        game->client->setHits(true, j, i);
                        emit opponentAttack(j*50, i*50, 4);
                    }
                game->server->decShipsLeft();
                if(game->server->isGameOver())
                {
                    QMessageBox::information(
                        this,
                        tr("Game Over"),
                        tr("You lose!") );
                    QApplication::quit();
                }
            }
            attackPlayerField();
        }
        else
        {
            emit opponentAttack(x*50, y*50, 4);
            game->server->setTurn(true);
            game->client->setTurn(false);

        }
    }
}

void BattleWindow::setOpponentShips()//randomowa funkcja ktora wylicza polozenia statkow opponenta
{
    srand ( time(NULL) );
    int size = 0;
    int x_1 = 0;
    int y_1 = 0;
    int x_2 = 0;
    int y_2 = 0;
    int dir = 0;
    bool check;
    for(int i = 0; i<10; i++)
    {
        game->client->setActiveShip(game->client->getPlayerShip(i));
        check = false;
        while(!check)
        {
            size = game->client->getPlayerShip(i)->getSize();
            x_1 = rand() % 10;
            y_1 = rand() % 10;
            dir = rand() % 2;
            if(dir == 0)//horiz
            {
                x_2 = x_1+size-1;
                y_2 = y_1;
            }
            else//vert
            {
                y_2 = y_1+size-1;
                x_2 = x_1;
            }
            if(x_2>9 || y_2>9 || y_1<0 || x_1<0)
                check = false;
            else
                check = isCorrect(x_1, y_1, x_2, y_2);
        }
        if(dir == 0)
        {
            for(int j = 0;j<size;j++)
            {
                game->client->getPlayerShip(i)->setIsPlaced(true);
                game->client->getPlayerShip(i)->setXBegin(x_1);
                game->client->getPlayerShip(i)->setYBegin(y_1);
                game->client->getPlayerShip(i)->setXEnd(x_2);
                game->client->getPlayerShip(i)->setYEnd(y_2);
                game->client->incShipsPlaced();
                game->client->getShipPlacement(x_1+j, y_1)->setSize(game->client->getPlayerShip(i)->getSize());
                game->client->getShipPlacement(x_1+j, y_1)->setHealth(game->client->getPlayerShip(i)->getHealth());
                game->client->getShipPlacement(x_1+j, y_1)->setIsPlaced(game->client->getPlayerShip(i)->getIsPlaced());
                game->client->getShipPlacement(x_1+j, y_1)->setXBegin(x_1);
                game->client->getShipPlacement(x_1+j, y_1)->setYBegin(y_1);
                game->client->getShipPlacement(x_1+j, y_1)->setXEnd(x_2);
                game->client->getShipPlacement(x_1+j, y_1)->setYEnd(y_2);
            }
        }
        else
        {
            for(int j = 0;j<size;j++)
            {
                game->client->getPlayerShip(i)->setIsPlaced(true);
                game->client->getPlayerShip(i)->setXBegin(x_1);
                game->client->getPlayerShip(i)->setYBegin(y_1);
                game->client->getPlayerShip(i)->setXEnd(x_2);
                game->client->getPlayerShip(i)->setYEnd(y_2);
                game->client->incShipsPlaced();
                game->client->getShipPlacement(x_1, y_1+j)->setSize(game->client->getPlayerShip(i)->getSize());
                game->client->getShipPlacement(x_1, y_1+j)->setHealth(game->client->getPlayerShip(i)->getHealth());
                game->client->getShipPlacement(x_1, y_1+j)->setIsPlaced(game->client->getPlayerShip(i)->getIsPlaced());
                game->client->getShipPlacement(x_1, y_1+j)->setXBegin(x_1);
                game->client->getShipPlacement(x_1, y_1+j)->setYBegin(y_1);
                game->client->getShipPlacement(x_1, y_1+j)->setXEnd(x_2);
                game->client->getShipPlacement(x_1, y_1+j)->setYEnd(y_2);
            }
        }
    }
}

bool BattleWindow::isCorrect(int firstX, int firstY, int secondX, int secondY)//funkcja ktora sprawdza czy randomowe statki sa OK
{
    int x_1=(firstX<=secondX)?firstX-1:secondX-1;
    int y_1=(firstY<=secondY)?firstY-1:secondY-1;
    int x_2=(firstX<=secondX)?secondX+1:firstX+1;
    int y_2=(firstY<=secondY)?secondY+1:firstY+1;
    int size=0;
    bool check=false;
    for(int i = 0; i < 10; i++)
    if(firstX==secondX)
    {
        size = abs(firstY-secondY)+1;
    }
    else if(firstY==secondY)
    {
        size = abs(firstX-secondX)+1;
    }
    for(int i = 0; i < 10; i++)
    {
        if(game->client->getActiveShip()->getSize() == game->client->getPlayerShip(i)->getSize() && game->client->getPlayerShip(i)->getIsPlaced()==false)
        {
            check = true;
        }
    }
    if(!check)
        return false;
    if(size!=game->client->getActiveShip()->getSize() && game->client->getIsPlacingShip()==true)
    {
        return false;
    }
    for(int i = y_1; i<y_2+1;i++)
        for(int j = x_1; j<x_2+1;j++)
        {
            if(i>9 || j>9 || i<0 || j<0)
                continue;
            if(game->client->getShipPlacement(j, i)->getSize()!=-1)
                return false;
        }
    return true;
}
