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
    explicit BattleWindow(QWidget *parent = 0);
    ~BattleWindow();
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::BattleWindow *ui;
    Game *game;
    void DrawPlayerBoard();
    void DrawOpponentBoard();
};

#endif // BATTLEWINDOW_H
