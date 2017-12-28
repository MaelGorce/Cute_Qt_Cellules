#include "ccellule.h"


CCellule::CCellule() : QPushButton(),
    m_ucStrength(0),
    m_ucNextStrength(0),
    m_bIsEdge(true),
    m_iX(0),
    m_iY(0)
{
    for(int iI=0; iI < C_NB_VOISINS;iI++)
    {
        m_pCVoisinage[iI]=nullptr;
    }
}

CCellule::CCellule(int x, int y, QMainWindow *parent): QPushButton(parent),
    m_ucStrength(0),
    m_ucNextStrength(0),
    m_bIsEdge(false),
    m_iX(x),
    m_iY(y)
{
    for(int iI=0; iI < C_NB_VOISINS;iI++)
    {

        m_pCVoisinage[iI]=nullptr;
    }
    this->setGeometry( C_LAR_CEL * m_iX,
                       C_HAU_CEL * m_iY,
                       C_LAR_CEL,
                       C_HAU_CEL);

    // Propriété du bouton
    this->setBackgroundRole(QPalette::Button);
    this->setForegroundRole(QPalette::NoRole);
    this->setAutoFillBackground(true);
    this->setFlat(true);

    ActualizeColor();

    this->setCursor(Qt::PointingHandCursor);
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
    ActualizeColor();
}

void CCellule::fnClicked()
{
    m_ucStrength=100;
    ActualizeColor();
}
