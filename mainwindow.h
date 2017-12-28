#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ccellule.h"

#define C_LAR_WD 300
#define C_HAU_WD 300


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CCellule* m_pCCelluleMap[(C_LAR_WD/C_LAR_CEL)][(C_HAU_WD/C_HAU_CEL)];
};

#endif // MAINWINDOW_H
