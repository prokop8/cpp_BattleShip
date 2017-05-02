#include "battlewindow.h"
#include "ui_battlewindow.h"

BattleWindow::BattleWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BattleWindow)
{
    ui->setupUi(this);
    game = new Game();
    ui->graphicsView->setSceneRect(0,0,500,500);
    game->scene1=new QGraphicsScene(this);
    ui->graphicsView->setScene(game->scene1);
    ui->graphicsView->show();
    DrawPlayerBoard();

    ui->graphicsView_2->setSceneRect(0,0,500,500);
    game->scene2=new QGraphicsScene(this);
    ui->graphicsView_2->setScene(game->scene2);
    ui->graphicsView_2->show();
    DrawOpponentBoard();
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

void BattleWindow::DrawPlayerBoard()
{
    for (int n = 0, x = 0; n < 10; ++n, x += 50)
    {
        for (int m = 0, y = 0; m < 10; ++m, y += 50)
        {
            game->playerField[n][m] = game->scene1->addRect(0, 0, 50, 50);
            game->playerField[n][m]->setPos(x,y);
        }
    }
}

void BattleWindow::DrawOpponentBoard()
{
    for (int n = 0, x = 0; n < 10; ++n, x += 50)
    {
        for (int m = 0, y = 0; m < 10; ++m, y += 50)
        {
            game->opponentField[n][m] = game->scene2->addRect(0, 0, 50, 50);
            game->opponentField[n][m]->setPos(x,y);
        }
    }
}
