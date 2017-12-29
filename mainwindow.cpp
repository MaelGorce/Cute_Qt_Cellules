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

    CCellule* pCVoisinage[C_NB_VOISINS];
    int pucVoisCorrX[C_NB_VOISINS] = {-1,0,1,-1,1,-1,0,1};
    int pucVoisCorrY[C_NB_VOISINS] = {-1,-1,-1,0,0,1,1,1};

    for (int iI=0; iI < C_LAR_WD/C_LAR_CEL; iI++)
    {
        for (int iJ=0; iJ < C_HAU_WD/C_HAU_CEL; iJ++)
        {
            for(int iV=0; iV < C_NB_VOISINS;iV++)
            {
                (iI+pucVoisCorrX[iV]>=0 && \
                 iI+pucVoisCorrX[iV]<C_LAR_WD/C_LAR_CEL && \
                 iJ+pucVoisCorrY[iV]>=0 && \
                 iJ+pucVoisCorrY[iV]<C_HAU_WD/C_HAU_CEL ) ? \
                 pCVoisinage[iV]=m_pCCelluleMap[iI+pucVoisCorrX[iV]][iJ+pucVoisCorrY[iV]] : \
                 pCVoisinage[iV]=nullptr;
            }
            m_pCCelluleMap[iI][iJ]->fnSetVoisinage(pCVoisinage);
        }
    }
}

MainWindow::~MainWindow()
{
    //delete ui;
}
