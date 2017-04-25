#ifndef BATTLEWINDOW_H
#define BATTLEWINDOW_H

#include <QMainWindow>

namespace Ui {
class BattleWindow;
}

class BattleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BattleWindow(QWidget *parent = 0);
    ~BattleWindow();

private:
    Ui::BattleWindow *ui;
};

#endif // BATTLEWINDOW_H
