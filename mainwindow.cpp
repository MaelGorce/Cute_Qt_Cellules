#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    trace_debug("Construction de MainWindow");

    trace_info("Taille de la fenêtre = " << C_LAR_WD << "x" << C_HAU_CFG + C_HAU_WD );
    setFixedSize(C_LAR_WD, C_HAU_CFG + C_HAU_WD);

    stConfigBehave stCfgBhv;
    stCfgBhv.ucGrowthRate               = 20;
    stCfgBhv.ucRandomization            = 40;
    stCfgBhv.ucOverPopulateThreshold    = 60;
    stCfgBhv.ucOverPopulateRate         = 40;
    stCfgBhv.ucUnderPopulateThreshold   = 20;
    stCfgBhv.ucUnderPopulateRate        = 20;
    trace_info("Config initiale : ");
    stCfgBhv.fnDumpCfgBhv();

    trace_debug("Début de la création des Cellules");
    FORALLCELLS
    (
        m_pCCelluleMap[iI][iJ]=new CCellule(iI,iJ,&stCfgBhv,this);
        if (m_pCCelluleMap[iI][iJ] == nullptr) trace_error("Erreur à la création de la Cellule ["<< iI << "]["<< iJ << "]");
    )
    trace_debug("Fin de la création des Cellules");

    CCellule* pCVoisinage[C_NB_VOISINS];
    int pucVoisCorrX[C_NB_VOISINS] = {-1,0,1,-1,1,-1,0,1};
    int pucVoisCorrY[C_NB_VOISINS] = {-1,-1,-1,0,0,1,1,1};

    trace_debug("Début de l'association du voisinage");
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
    trace_debug("Fin de l'association du voisinage");

    trace_debug("Création des deux timers");
    m_pQTickerCompute   = new QTimer(this);
    m_pQTickerActualize = new QTimer(this);

    trace_debug("Début de la connection des timers avec les Cellules");
    FORALLCELLS
    (
       connect(m_pQTickerCompute  , SIGNAL(timeout()), m_pCCelluleMap[iI][iJ], SLOT(fnCompute()));
       connect(m_pQTickerActualize, SIGNAL(timeout()), m_pCCelluleMap[iI][iJ], SLOT(fnActualize()));
    )
    trace_debug("Fin de la connection des timers avec les Cellules");

    trace_debug("Lancement du timer Actualize");
    m_pQTickerActualize->start(100);
    trace_debug("Lancement du timer Compute");
    m_pQTickerCompute->start(100);

    trace_debug("Fin de construction de MainWindow");
}

MainWindow::~MainWindow()
{
    trace_debug("Destruction de MainWindow");
    FORALLCELLS
    (
           delete m_pCCelluleMap[iI][iJ];
    )
    trace_debug("Fin de destruction de MainWindow");
}
