#ifndef CCELLULE_H
#define CCELLULE_H

#include <QObject>
#include <QPushButton>
#include <QMainWindow>

#define C_NB_VOISINS 8

#define C_LAR_CEL 10
#define C_HAU_CEL 10

class CCellule : public QPushButton
{
    Q_OBJECT

public:
    CCellule();
    CCellule(int x, int y, QMainWindow* parent);
    ~CCellule();

    void fnSetVoisinage(CCellule**);
    void fnCompute();
    void fnActualize();
    unsigned char fnGetStrength();

public slots:
    void fnClicked();

private:
    void ActualizeColor();

    unsigned char m_ucStrength;
    unsigned char m_ucNextStrength;
    bool m_bIsEdge;
    int m_iX;
    int m_iY;
    CCellule* m_pCVoisinage[C_NB_VOISINS];
    QPalette m_qPalette;
};

#endif // CCELLULE_H
