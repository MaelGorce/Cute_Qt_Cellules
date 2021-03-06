#include "cconfiguration.h"

CConfiguration::CConfiguration(unsigned char *pucConfig, QString strName, unsigned char ucPosition, QMainWindow *parent) : QObject(parent),
    m_pucConfig(pucConfig),
    m_strName(strName)
{

    m_pQslider = new QSlider(Qt::Vertical, parent);
    m_pQlabel = new QLabel(parent);
    m_pQlcd = new QLCDNumber(parent);

    m_pQslider->setGeometry(C_LAR_WD/12+ucPosition*C_LAR_WD/6,C_HAU_BAR + C_HAU_BAR , 15, C_HAU_CFG - 2 * C_HAU_BAR);
    m_pQlabel->setGeometry(ucPosition*C_LAR_WD/6,C_HAU_BAR,C_LAR_WD/6, C_HAU_BAR);
    m_pQlcd->setGeometry(ucPosition*C_LAR_WD/6,C_HAU_BAR + C_HAU_CFG - 25,C_LAR_WD/6,C_HAU_BAR);

    QObject::connect(m_pQslider, SIGNAL(valueChanged(int)), m_pQlcd, SLOT(display(int))) ;
    QObject::connect(m_pQslider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int))) ;

    m_pQlabel->setText(m_strName);
    m_pQlabel->setAlignment(Qt::AlignCenter);
    m_pQslider->setValue(*m_pucConfig);
    m_pQslider->setMaximum(100);
}

void CConfiguration::fnActualizeSlider()
{
    m_pQslider->setValue(*m_pucConfig);
}
void CConfiguration::setValue(int iInput)
{
    *m_pucConfig = iInput;
    trace_info("Nouvelle valeur de " << m_strName << " : " <<  *m_pucConfig )
}
