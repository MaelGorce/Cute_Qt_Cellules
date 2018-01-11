#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMenuBar>
#include <QAction>
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

private slots:
    void SfnSave();
    void SfnLoad();
    void SfnReset();
    void SfnHelp();

private:
    void fnCreatActions();
    void fnCreateMenus();

    stConfigBehave m_stCfgBhv;
    stConfigBehave m_stCfgBhvInit;
    QMenu * m_pQMenuFile;
    QMenu * m_pQMenuHelp;
    QAction * m_pQActionSave;
    QAction * m_pQActionLoad;
    QAction * m_pQActionReset;
    QAction * m_pQActionHelp;
    // Membres de la classe MainWindow
    CCellule* m_pCCelluleMap[(C_LAR_WD/C_SIZE_CEL)][(C_HAU_WD/C_SIZE_CEL)];
    QTimer* m_pQTickerCompute;
    QTimer* m_pQTickerActualize;
    CConfiguration* m_poCfgTab[C_NB_CFG];
};

#endif // MAINWINDOW_H
