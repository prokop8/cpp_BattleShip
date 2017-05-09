#ifndef BATTLEWINDOW_H
#define BATTLEWINDOW_H

#include <QMainWindow>
#include "game.h"

namespace Ui {
class BattleWindow;
}

class BattleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BattleWindow(QWidget *parent = 0, Game* game = new Game());
    ~BattleWindow();
    void setOpponentShips();
    bool isCorrect(int, int, int, int);
    void attackPlayerField();
signals:
    void shipHere(int x, int y, int color);
    void completedAttack(int x, int y, int color);
    void opponentAttack(int x, int y, int color);
    void opponentShipHere(int x, int y, int color);
private slots:
    void attackOpponentField(int first, int second);
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::BattleWindow *ui;
    Game *game;
    void DrawPlayerBoard();
    void DrawOpponentBoard();
};

#endif // BATTLEWINDOW_H
