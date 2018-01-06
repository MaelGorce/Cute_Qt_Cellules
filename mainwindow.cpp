#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setFixedSize(C_LAR_WD, C_HAU_WD);


    FORALLCELLS
    (
        m_pCCelluleMap[iI][iJ]=new CCellule(iI,iJ,this);
    )


    CCellule* pCVoisinage[C_NB_VOISINS];
    int pucVoisCorrX[C_NB_VOISINS] = {-1,0,1,-1,1,-1,0,1};
    int pucVoisCorrY[C_NB_VOISINS] = {-1,-1,-1,0,0,1,1,1};

    FORALLCELLS
    (
        for(int iV=0; iV < C_NB_VOISINS;iV++)                                               \
            {                                                                               \
                (iI+pucVoisCorrX[iV]>=0 &&                                                  \
                 iI+pucVoisCorrX[iV]<C_LAR_WD/C_SIZE_CEL &&                                 \
                 iJ+pucVoisCorrY[iV]>=0 &&                                                  \
                 iJ+pucVoisCorrY[iV]<C_HAU_WD/C_SIZE_CEL ) ?                                \
                 pCVoisinage[iV]=m_pCCelluleMap[iI+pucVoisCorrX[iV]][iJ+pucVoisCorrY[iV]] : \
                 pCVoisinage[iV]=nullptr;                                                   \
            }                                                                               \
        m_pCCelluleMap[iI][iJ]->fnSetVoisinage(pCVoisinage);                                \
    )

    // Création du Timer et
    m_pQTickerCompute   = new QTimer(this);
    m_pQTickerActualize = new QTimer(this);

    FORALLCELLS
    (
       connect(m_pQTickerCompute  , SIGNAL(timeout()), m_pCCelluleMap[iI][iJ], SLOT(fnCompute()));
       connect(m_pQTickerActualize, SIGNAL(timeout()), m_pCCelluleMap[iI][iJ], SLOT(fnActualize()));
    )

    m_pQTickerActualize->start(100);
    m_pQTickerCompute->start(100);
}

MainWindow::~MainWindow()
{
    //delete ui;
}
