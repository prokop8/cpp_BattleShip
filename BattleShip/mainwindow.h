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
    bool isCorrect(int firstX, int firstY, int secondX, int secondY);
signals:
    void successfullyPlaced(int x, int y, int color);
private slots:
    void onStartGame();

    void createServer();

    void createClient();

    void exitGame();

    void setActiveShip_4();

    void setActiveShip_3();

    void setActiveShip_2();

    void setActiveShip_1();

    void placeShip(int, int);

    void changeCounter(int);

    void setRandomShips();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
private:
    Ui::MainWindow *ui;
    BattleWindow *battleWindow;
    Game *game;
    void DrawPlayerBoard();
};

#endif // MAINWINDOW_H
