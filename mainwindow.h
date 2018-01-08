#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "ccellule.h"
#include "traces.h"
#include "cconfiguration.h"

#define FORALLCELLS(X) \
    for (int iI=0; iI < C_LAR_WD/C_SIZE_CEL; iI++)              \
    {                                                           \
        for (int iJ=0; iJ < C_HAU_WD/C_SIZE_CEL; iJ++)          \
        {                                                       \
            X                                                   \
        }                                                       \
    }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    stConfigBehave m_stCfgBhv;

private:

    // Membres de la classe MainWindow
    CCellule* m_pCCelluleMap[(C_LAR_WD/C_SIZE_CEL)][(C_HAU_WD/C_SIZE_CEL)];
    QTimer* m_pQTickerCompute;
    QTimer* m_pQTickerActualize;
    CConfiguration* m_poCfgTab[C_NB_CFG];
};

#endif // MAINWINDOW_H
