#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    trace_debug("Construction de MainWindow");

    trace_info("Taille de la fenêtre = " << C_LAR_WD << "x" << C_HAU_CFG + C_HAU_WD );
    setFixedSize(C_LAR_WD, C_HAU_BAR + C_HAU_CFG + C_HAU_WD);

    fnCreatActions();
    fnCreateMenus();

    m_stCfgBhvInit.ucGrowthRate               = 20;
    m_stCfgBhvInit.ucRandomization            = 0;
    m_stCfgBhvInit.ucOverPopulateThreshold    = 60;
    m_stCfgBhvInit.ucOverPopulateRate         = 40;
    m_stCfgBhvInit.ucUnderPopulateThreshold   = 20;
    m_stCfgBhvInit.ucUnderPopulateRate        = 20;

    m_stCfgBhv = m_stCfgBhvInit;

    trace_debug("Début de la création des Cellules");
    FORALLCELLS
    (
        m_pCCelluleMap[iI][iJ]=new CCellule(iI,iJ,&m_stCfgBhv,this);
        if (m_pCCelluleMap[iI][iJ] == nullptr) trace_error("Erreur à la création de la Cellule ["<< iI << "]["<< iJ << "]");
    )
    trace_info("Fin de la création des " << C_LAR_WD/C_SIZE_CEL * C_HAU_WD/C_SIZE_CEL <<" Cellules");

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


    m_poCfgTab[0] = new CConfiguration(&m_stCfgBhv.ucRandomization,"Randomization",0,this);
    m_poCfgTab[1] = new CConfiguration(&m_stCfgBhv.ucGrowthRate,"GrowthRate",1,this);
    m_poCfgTab[2] = new CConfiguration(&m_stCfgBhv.ucOverPopulateThreshold,"OverPopulateThd",2,this);
    m_poCfgTab[3] = new CConfiguration(&m_stCfgBhv.ucOverPopulateRate,"OverPopulateRate",3,this);
    m_poCfgTab[4] = new CConfiguration(&m_stCfgBhv.ucUnderPopulateThreshold,"UnderPopulateThd",4,this);
    m_poCfgTab[5] = new CConfiguration(&m_stCfgBhv.ucUnderPopulateRate,"UnderPopulateRate",5,this);

    trace_debug("Lancement du timer Actualize");
    m_pQTickerActualize->start(100);
    trace_debug("Lancement du timer Compute");
    m_pQTickerCompute->start(100);

    trace_debug("Fin de construction de MainWindow");
}

void MainWindow::fnCreatActions()
{
    trace_debug("Création de l'action Save");
    m_pQActionSave = new QAction(tr("&Save"), this);
    m_pQActionSave->setShortcuts(QKeySequence::Save);
    m_pQActionSave->setStatusTip(tr("Save current Configuration"));
    connect(m_pQActionSave,&QAction::triggered, this,&MainWindow::SfnSave);

    trace_debug("Création de l'action Load");
    m_pQActionLoad = new QAction(tr("&Load"), this);
    m_pQActionLoad->setShortcuts(QKeySequence::Open);
    m_pQActionLoad->setStatusTip(tr("Load a saved Configuration"));
    connect(m_pQActionLoad,&QAction::triggered, this,&MainWindow::SfnLoad);

    trace_debug("Création de l'action Reset");
    m_pQActionReset = new QAction(tr("&Reset"), this);
    m_pQActionReset->setShortcuts(QKeySequence::Refresh);
    m_pQActionReset->setStatusTip(tr("Reset to default Configuration"));
    connect(m_pQActionReset,&QAction::triggered, this,&MainWindow::SfnReset);

    trace_debug("Création de l'action Help");
    m_pQActionHelp = new QAction(tr("&Help"), this);
    m_pQActionHelp->setShortcuts(QKeySequence::HelpContents);
    m_pQActionHelp->setStatusTip(tr("What is this ?"));
    connect(m_pQActionHelp,&QAction::triggered, this,&MainWindow::SfnHelp);
}

void MainWindow::fnCreateMenus()
{
    trace_debug("Création du Menu");

    trace_debug("Création du menu File");
    m_pQMenuFile = menuBar()->addMenu(tr("&File"));
    m_pQMenuFile->addAction(m_pQActionLoad);
    m_pQMenuFile->addAction(m_pQActionSave);
    m_pQMenuFile->addAction(m_pQActionReset);

    trace_debug("Création du menu Help");
    m_pQMenuHelp = menuBar()->addMenu(tr("&Help"));
    m_pQMenuHelp->addAction(m_pQActionHelp);
}


void MainWindow::SfnSave()
{
    trace_info("Fonction Save");
}

void MainWindow::SfnLoad()
{
    trace_info("Fonction Load");
}

void MainWindow::SfnReset()
{
    trace_info("Fonction Reset");
    FORALLCELLS
    (
        m_pCCelluleMap[iI][iJ]->fnSetStrength(0);
    )
    m_stCfgBhv = m_stCfgBhvInit;
    for(int iQ=0;iQ<C_NB_CFG;iQ++)
    {
        m_poCfgTab[iQ]->fnActualizeSlider();
    }
}

void MainWindow::SfnHelp()
{
    trace_info("Fonction Help");
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
