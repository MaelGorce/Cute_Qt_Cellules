#ifndef CCELLULE_H
#define CCELLULE_H

#include <QObject>
#include <QPushButton>
#include <QMainWindow>
#include <stdlib.h>
#include <time.h>
#include "traces.h"

#define C_NB_VOISINS 8

#define C_SIZE_CEL 10

#define C_MAX_STRENGHT 100

class CCellule : public QPushButton
{
    Q_OBJECT

public:
    CCellule(int x, int y, QMainWindow* parent);
    ~CCellule();

    void fnSetVoisinage(CCellule**);
    unsigned char fnGetStrength();

public slots:
    void fnCompute();
    void fnActualize();

private slots:
    void fnClicked();

private:
    void ActualizeColor();

    // Membres de la classe Cellule
    unsigned char m_ucStrength;
    unsigned char m_ucNextStrength;
    int m_iX;
    int m_iY;
    CCellule* m_pCVoisinage[C_NB_VOISINS];
    QPalette m_qPalette;
};

#endif // CCELLULE_H
