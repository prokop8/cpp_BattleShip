#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "battlewindow.h"
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_5_clicked();

    void on_actionAs_Server_triggered();

    void on_actionAs_Client_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    BattleWindow *battleWindow;
    Game *game;
    void DrawLayout();
};

#endif // MAINWINDOW_H
