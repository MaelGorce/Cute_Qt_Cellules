#ifndef CCELLULE_H
#define CCELLULE_H

#include <QObject>
#include <QPushButton>
#include <QMainWindow>
#include <stdlib.h>
#include <time.h>
#include "traces.h"
#include "cconfiguration.h"

using namespace std;
struct stConfigBehave {
    unsigned char ucRandomization = 0;
    unsigned char ucGrowthRate = 0;
    unsigned char ucOverPopulateThreshold = 0;
    unsigned char ucOverPopulateRate = 0;
    unsigned char ucUnderPopulateThreshold = 0;
    unsigned char ucUnderPopulateRate = 0;

    void fnDumpCfgBhv(){
        trace_info( endl << "Randomization          : " << this->ucRandomization << endl\
        << "GrowthRate             : " << this->ucGrowthRate << endl\
        << "OverPopulateThreshold  : " << this->ucOverPopulateThreshold << endl\
        << "OverPopulateRate       : " << this->ucOverPopulateRate << endl\
        << "UnderPopulateThreshold : " << this->ucUnderPopulateThreshold << endl\
        << "UnderPopulateRate      : " << this->ucUnderPopulateRate)
    }
};

class CCellule : public QPushButton
{
    Q_OBJECT

public:
    CCellule(int x, int y, stConfigBehave* pstCfgBhv, QMainWindow* parent);
    ~CCellule();

    void fnSetVoisinage(CCellule**);
    unsigned char fnGetStrength();
    void fnSetStrength(unsigned char ucStrength);

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
    unsigned int m_ucAroundStrength;
    int m_iX;
    int m_iY;
    CCellule* m_pCVoisinage[C_NB_VOISINS];
    QPalette m_qPalette;
    struct stConfigBehave *m_pstCfgBhv;
};

#endif // CCELLULE_H
