#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "ccellule.h"

#define C_LAR_WD 800
#define C_HAU_WD 500


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
    CCellule* m_pCCelluleMap[(C_LAR_WD/C_SIZE_CEL)][(C_HAU_WD/C_SIZE_CEL)];
    QTimer* m_pQTickerCompute;
    QTimer* m_pQTickerActualize;
};

#endif // MAINWINDOW_H
