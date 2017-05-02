#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "battlewindow.h"
#include "game.h"

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
            game->playerField[n][m] = game->scene1->addRect(0, 0, 50, 50);
            game->playerField[n][m]->setPos(x,y);
        }
    }
}

void MainWindow::onStartGame()
{
    battleWindow = new BattleWindow(this);
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
    //ui->pushButton_5->setEnabled(false);
}

void MainWindow::createClient()
{
    this->setWindowTitle("Client");
    ui->graphicsView->show();
    ui->tabWidget->show();
    ui->startGameButton->show();
    ui->actionAs_Client->setEnabled(false);
    ui->actionAs_Server->setEnabled(false);
   // ui->pushButton_5->setEnabled(false);
}

void MainWindow::exitGame()
{
    QApplication::quit();
}
