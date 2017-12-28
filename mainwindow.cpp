#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)//,
    //ui(new Ui::MainWindow)
{
    setFixedSize(C_LAR_WD, C_HAU_WD);

    for (int iI=0; iI < C_LAR_WD/C_LAR_CEL; iI++)
    {
        for (int iJ=0; iJ < C_HAU_WD/C_LAR_CEL; iJ++)
        {
            m_pCCelluleMap[iI][iJ]=new CCellule(iI,iJ,this);
        }
    }
}

MainWindow::~MainWindow()
{
    //delete ui;
}
