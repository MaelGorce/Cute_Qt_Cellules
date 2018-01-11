#include "ccellule.h"

CCellule::CCellule(int x, int y, stConfigBehave* pstCfgBhv, QMainWindow *parent): QPushButton(parent),
    m_ucStrength(0),
    m_ucNextStrength(0),
    m_ucAroundStrength(0),
    m_iX(x),
    m_iY(y)
{
    trace_debug("Construction de Cellule [" << m_iX << "][" << m_iY << "]");
    for(int iI=0; iI < C_NB_VOISINS;iI++)
    {
        m_pCVoisinage[iI]=nullptr;
    }
    // On Positione la cellule
    this->setGeometry( C_SIZE_CEL * m_iX,
                       C_HAU_BAR + C_HAU_CFG + C_SIZE_CEL * m_iY,
                       C_SIZE_CEL,
                       C_SIZE_CEL);

    // Récupération de la configuration initiale
    m_pstCfgBhv = pstCfgBhv;

    // Propriété du bouton
    this->setBackgroundRole(QPalette::Button);
    this->setForegroundRole(QPalette::NoRole);
    this->setAutoFillBackground(true);
    this->setFlat(true);
    this->setCursor(Qt::PointingHandCursor);

    ActualizeColor();

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(fnClicked()));
}

CCellule::~CCellule()
{
    trace_debug("Destruction de Cellule [" << m_iX << "][" << m_iY << "]");
}

void CCellule::ActualizeColor()
{
    m_qPalette.setColor(QPalette::Button,QColor(255-2*m_ucStrength,255,255-2*m_ucStrength));
    this->setPalette(m_qPalette);
}

void CCellule::fnActualize()
{
    // Randomize
    if (m_pstCfgBhv->ucRandomization !=0 ) m_ucNextStrength += (unsigned char) rand() % m_pstCfgBhv->ucRandomization - m_pstCfgBhv->ucRandomization /2 ;
    if (m_ucNextStrength > 200 )           m_ucNextStrength=0; // 'négatif' du unsigned char
    if (m_ucNextStrength > C_MAX_STRENGHT) m_ucNextStrength = C_MAX_STRENGHT;

    m_ucStrength = m_ucNextStrength;
    ActualizeColor();
}

void CCellule::fnSetVoisinage(CCellule** pCVoisinage)
{
    for(int iI=0; iI < C_NB_VOISINS;iI++)
    {
        m_pCVoisinage[iI]=pCVoisinage[iI];
    }
}

void CCellule::fnSetStrength(unsigned char ucStrength)
{
    m_ucStrength=ucStrength;
}

void CCellule::fnCompute()
{
    m_ucAroundStrength=0;
    for(int iI=0; iI < C_NB_VOISINS;iI++)
    {
        if (m_pCVoisinage[iI] != nullptr)
        {
            m_ucAroundStrength+=m_pCVoisinage[iI]->fnGetStrength();
        }
    }

    if (m_ucAroundStrength/C_NB_VOISINS < m_pstCfgBhv->ucUnderPopulateThreshold)
    {
        // Sous-population envirronnante
        if (m_ucStrength < m_pstCfgBhv->ucUnderPopulateRate)
        {
            m_ucNextStrength = 0;
        }
        else
        {
            m_ucNextStrength = m_ucStrength - m_pstCfgBhv->ucUnderPopulateRate;
        }
    }
    else if (m_ucAroundStrength/C_NB_VOISINS > m_pstCfgBhv->ucOverPopulateThreshold)
    {
        // Sur-population envirronnante
        if (m_ucStrength < m_pstCfgBhv->ucUnderPopulateRate)
        {
            m_ucNextStrength = 0;
        }
        else
        {
            m_ucNextStrength = m_ucStrength - m_pstCfgBhv->ucUnderPopulateRate;
        }
    }
    else
    {
        // Croissance
        if (m_ucStrength > C_MAX_STRENGHT - m_pstCfgBhv->ucGrowthRate )
        {
            m_ucNextStrength = C_MAX_STRENGHT;
        }
        else
        {
            m_ucNextStrength = m_ucStrength + m_pstCfgBhv->ucGrowthRate;
        }
    }
}

unsigned char CCellule::fnGetStrength()
{
    return m_ucStrength;
}

void CCellule::fnClicked()
{
    trace_info("Click Cellule [" << m_iX << "][" << m_iY << "]");
    m_ucStrength=100;
    ActualizeColor();
}
