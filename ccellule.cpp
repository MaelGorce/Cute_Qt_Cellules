#include "ccellule.h"

CCellule::CCellule(int x, int y, QMainWindow *parent): QPushButton(parent),
    m_ucStrength(0),
    m_ucNextStrength(0),
    m_iX(x),
    m_iY(y)
{
    for(int iI=0; iI < C_NB_VOISINS;iI++)
    {
        m_pCVoisinage[iI]=nullptr;
    }
    // On Positione la cellule
    this->setGeometry( C_SIZE_CEL * m_iX,
                       C_SIZE_CEL * m_iY,
                       C_SIZE_CEL,
                       C_SIZE_CEL);

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

}

void CCellule::ActualizeColor()
{
    m_qPalette.setColor(QPalette::Button,QColor(255-2*m_ucStrength,255,255-2*m_ucStrength));
    this->setPalette(m_qPalette);
}

void CCellule::fnActualize()
{
    // Randomize
    m_ucNextStrength += (unsigned char) rand() % 40 -20 ;
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

void CCellule::fnCompute()
{
    unsigned int AroundStrength=m_ucStrength;
    for(int iI=0; iI < C_NB_VOISINS;iI++)
    {
        if (m_pCVoisinage[iI] != nullptr)
        {
            AroundStrength+=m_pCVoisinage[iI]->fnGetStrength();
        }
    }

    if (AroundStrength/C_NB_VOISINS < 20)
    {
        // Sous-population envirronnante
        if (m_ucStrength < 20)
        {
            m_ucNextStrength = 0;
        }
        else
        {
            m_ucNextStrength = m_ucStrength - 20;
        }
    }
    else if (AroundStrength/C_NB_VOISINS > 60)
    {
        // Sur-population envirronnante
        if (m_ucStrength < 20)
        {
            m_ucNextStrength = 0;
        }
        else
        {
            m_ucNextStrength = m_ucStrength - 20;
        }
    }
    else
    {
        // Croissance
        if (m_ucStrength > 80)
        {
            m_ucNextStrength = C_MAX_STRENGHT;
        }
        else
        {
            m_ucNextStrength = m_ucStrength + 20;
        }
    }
}

unsigned char CCellule::fnGetStrength()
{
    return m_ucStrength;
}

void CCellule::fnClicked()
{
    m_ucStrength=100;
    ActualizeColor();
}
