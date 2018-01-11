#ifndef CCONFIGURATION_H
#define CCONFIGURATION_H

#include <QObject>
#include <QSlider>
#include <QLabel>
#include <QLCDNumber>
#include <QMainWindow>
#include "traces.h"

// Défine pour Cellules :
#define C_NB_VOISINS 8
#define C_SIZE_CEL 10
#define C_MAX_STRENGHT 100

// Défine pour MainWindow :
#define C_LAR_WD 800
#define C_HAU_WD 500
#define C_HAU_BAR 25
#define C_HAU_CFG 200
#define C_NB_CFG 6

class CConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit CConfiguration(unsigned char *pucConfig, QString strName, unsigned char ucPosition, QMainWindow *parent = nullptr);
    void fnActualizeSlider();
signals:

public slots:
    void setValue(int);

private:
    unsigned char *m_pucConfig;
    QString m_strName;
    QSlider* m_pQslider;
    QLabel*  m_pQlabel;
    QLCDNumber* m_pQlcd;
};

#endif // CCONFIGURATION_H
