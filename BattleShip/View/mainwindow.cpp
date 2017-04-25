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
    ui->pushButton_5->hide();
    game = new Game();
    ui->graphicsView->setSceneRect(0,0,500,500);
    game->scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(game->scene);
    DrawLayout();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DrawLayout()
{
    for (int n = 0, x = 0; n < 10; ++n, x += 50)
    {
        for (int m = 0, y = 0; m < 10; ++m, y += 50)
        {
            game->field[n][m] = game->scene->addRect(x, y, 50, 50);
        }
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    battleWindow = new BattleWindow(this);
    battleWindow->show();
    hide();
}

void MainWindow::on_actionAs_Server_triggered()
{
    this->setWindowTitle("Server");
    ui->graphicsView->show();
    ui->tabWidget->show();
    ui->pushButton_5->show();
    ui->actionAs_Client->setEnabled(false);
    ui->actionAs_Server->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
}

void MainWindow::on_actionAs_Client_triggered()
{
    this->setWindowTitle("Client");
    ui->graphicsView->show();
    ui->tabWidget->show();
    ui->pushButton_5->show();
    ui->actionAs_Client->setEnabled(false);
    ui->actionAs_Server->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
