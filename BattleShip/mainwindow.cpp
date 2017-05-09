#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "battlewindow.h"
#include "game.h"
#include "math.h"
#include "board.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->hide();
    ui->tabWidget->hide();
    ui->startGameButton->hide();
    game = new Game();
    ui->graphicsView->setSceneRect(0,0,500,500);
    game->scene1=new QGraphicsScene(this);
    ui->graphicsView->setScene(game->scene1);
    DrawPlayerBoard();

    connect(ui->startGameButton, SIGNAL(clicked(bool)), this, SLOT(onStartGame()));
    connect(ui->actionAs_Server, SIGNAL(triggered(bool)), this, SLOT(createServer()));
    connect(ui->actionAs_Client, SIGNAL(triggered(bool)), this, SLOT(createClient()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(exitGame()));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(setActiveShip_4()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(setActiveShip_3()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(setActiveShip_2()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(setActiveShip_1()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    ui->graphicsView->fitInView(ui->graphicsView->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::DrawPlayerBoard()
{
    for (int n = 0, x = 0; n < 10; ++n, x += 50)
    {
        for (int m = 0, y = 0; m < 10; ++m, y += 50)
        {
            game->playerField[n][m] = new Board(game->scene1, x, y);
            game->playerField[n][m]->setPos(x,y);
            connect(game->playerField[n][m], SIGNAL(Clicked(int,int)), this, SLOT(placeShip(int,int)));
            connect(this, SIGNAL(successfullyPlaced(int,int,int)), game->playerField[n][m], SLOT(changeColor(int,int,int)));
            connect(game->playerField[n][m], SIGNAL(changeNumberOfShips(int)), this, SLOT(changeCounter(int)));
        }
    }
}

void MainWindow::onStartGame()
{
    battleWindow = new BattleWindow(this, this->game);
    //battleWindow->setData(this->game);
    battleWindow->show();
    hide();
}

void MainWindow::createServer()
{
    this->setWindowTitle("Server");
    ui->graphicsView->show();
    ui->tabWidget->show();
    ui->startGameButton->show();
    ui->actionAs_Client->setEnabled(false);
    ui->actionAs_Server->setEnabled(false);
    ui->startGameButton->setEnabled(false);
}

void MainWindow::createClient()
{
    this->setWindowTitle("Client");
    ui->graphicsView->show();
    ui->tabWidget->show();
    ui->startGameButton->show();
    ui->actionAs_Client->setEnabled(false);
    ui->actionAs_Server->setEnabled(false);
    ui->startGameButton->setEnabled(false);
}

void MainWindow::exitGame()
{
    QApplication::quit();
}

void MainWindow::setActiveShip_4()
{
    game->server->setActiveShip(new Ship(4));
}

void MainWindow::setActiveShip_3()
{
    game->server->setActiveShip(new Ship(3));
}

void MainWindow::setActiveShip_2()
{
    game->server->setActiveShip(new Ship(2));
}

void MainWindow::setActiveShip_1()
{
    game->server->setActiveShip(new Ship(1));
}

bool MainWindow::isCorrect(int firstX, int firstY, int secondX, int secondY)
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
        if(game->server->getActiveShip()->getSize() == game->server->getPlayerShip(i)->getSize() && game->server->getPlayerShip(i)->getIsPlaced()==false)
        {
            check = true;
        }
    }
    if(!check)
        return false;
    if(size!=game->server->getActiveShip()->getSize() && game->server->getIsPlacingShip()==true)
    {
        return false;
    }
    for(int i = y_1; i<y_2+1;i++)
        for(int j = x_1; j<x_2+1;j++)
        {
            if(i>9 || j>9 || i<0 || j<0)
                continue;
            if(game->server->getShipPlacement(j, i)->getSize()!=-1)
                return false;
        }
    return true;
}

void MainWindow::placeShip(int first, int second)
{
    int x = first/50;
    int y = second/50;

    if(!game->server->getIsPlacingShip() && game->server->getActiveShip()->getSize() != 1)
    {
        if(isCorrect(x, y, x, y))
        {
            emit successfullyPlaced(x*50, y*50, 1);
            game->server->setBeginX(x);
            game->server->setBeginY(y);
            game->server->setIsPlacingShip(true);
        }
    }
    else
    {
        if(game->server->getActiveShip()->getSize() == 1)
        {
            game->server->setBeginX(x);
            game->server->setBeginY(y);
            game->server->setIsPlacingShip(true);
        }
        if(isCorrect(game->server->getBeginX(), game->server->getBeginY(), x, y))
        {
            int number=0;
            for(number; number<10; number++)
            {
                if(game->server->getPlayerShip(number)->getSize() == game->server->getActiveShip()->getSize() && game->server->getPlayerShip(number)->getIsPlaced() == false)
                {
                    game->server->getPlayerShip(number)->setIsPlaced(true);
                    game->server->getPlayerShip(number)->setXBegin(game->server->getBeginX());
                    game->server->getPlayerShip(number)->setYBegin(game->server->getBeginY());
                    game->server->getPlayerShip(number)->setXEnd(x);
                    game->server->getPlayerShip(number)->setYEnd(y);
                    game->server->incShipsPlaced();
                    break;
                }
            }
            if(game->server->getBeginX() == x)
            {
                int beginShip = (game->server->getBeginY()<=y)?game->server->getBeginY():y;
                for(int i = 0; i < abs(game->server->getBeginY()-y)+1; i++)
                {
                    emit successfullyPlaced(x*50, (beginShip+i)*50, 1);
                    game->server->setIsPlacingShip(false);
                    game->server->getShipPlacement(x, beginShip+i)->setSize(game->server->getPlayerShip(number)->getSize());
                    game->server->getShipPlacement(x, beginShip+i)->setHealth(game->server->getPlayerShip(number)->getHealth());
                    game->server->getShipPlacement(x, beginShip+i)->setIsPlaced(game->server->getPlayerShip(number)->getIsPlaced());
                    game->server->getShipPlacement(x, beginShip+i)->setXBegin(game->server->getBeginX());
                    game->server->getShipPlacement(x, beginShip+i)->setYBegin(game->server->getBeginY());
                    game->server->getShipPlacement(x, beginShip+i)->setXEnd(x);
                    game->server->getShipPlacement(x, beginShip+i)->setYEnd(y);
                }
            }
            else
            {
                int beginShip = (game->server->getBeginX()<=x)?game->server->getBeginX():x;
                for(int i = 0; i < abs(game->server->getBeginX()-x)+1; i++)
                {
                    emit successfullyPlaced((beginShip+i)*50, y*50, 1);
                    game->server->setIsPlacingShip(false);
                    game->server->getShipPlacement(beginShip+i, y)->setSize(game->server->getPlayerShip(number)->getSize());
                    game->server->getShipPlacement(beginShip+i, y)->setHealth(game->server->getPlayerShip(number)->getHealth());
                    game->server->getShipPlacement(beginShip+i, y)->setIsPlaced(game->server->getPlayerShip(number)->getIsPlaced());
                    game->server->getShipPlacement(beginShip+i, y)->setXBegin(game->server->getBeginX());
                    game->server->getShipPlacement(beginShip+i, y)->setYBegin(game->server->getBeginY());
                    game->server->getShipPlacement(beginShip+i, y)->setXEnd(x);
                    game->server->getShipPlacement(beginShip+i, y)->setYEnd(y);
                }
            }

        }
        else
        {
            emit successfullyPlaced(game->server->getBeginX()*50, game->server->getBeginY()*50, 0);
        }
        if(game->server->getShipsPlaced()==10)
        {
            ui->startGameButton->setEnabled(true);
        }
        for(int i = 0; i < 10; i++)
        {
            if(game->server->getPlayerShip(i)->getIsPlaced()==false)
            {
               game->server->setActiveShip(game->server->getPlayerShip(i));
               break;
            }
        }
        game->server->setIsPlacingShip(false);
        game->server->setBeginX(0);
        game->server->setBeginY(0);
    }
}

void MainWindow::changeCounter(int color)
{
    int size = 0;
    int tmp = 0;
    QString str;
    if(color == 1 && game->server->getIsPlacingShip())
    {
        size = game->server->getActiveShip()->getSize();
        if(size == 4)
        {
            str = ui->label_5->text();
            tmp = str.toInt();
            tmp--;
            str = QString::number(tmp);
            ui->label_5->setText(str);
        }
        else if(size == 3)
        {
            str = ui->label_6->text();
            tmp = str.toInt();
            tmp--;
            str = QString::number(tmp);
            ui->label_6->setText(str);
        }
        else if(size == 2)
        {
            str = ui->label_7->text();
            tmp = str.toInt();
            tmp--;
            str = QString::number(tmp);
            ui->label_7->setText(str);
        }
        else if(size == 1)
        {
            str = ui->label_8->text();
            tmp = str.toInt();
            tmp--;
            str = QString::number(tmp);
            ui->label_8->setText(str);
        }
    }
}
