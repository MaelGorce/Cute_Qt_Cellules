#include "mainwindow.h"
#include "traces.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    trace_info("Démarrage de l'application Cellule");
    QApplication QApp(argc, argv);
    trace_debug("Création de l'objet MainWindow");
    MainWindow CMainWindow;
    trace_debug("Affichage de la MainWindow");
    CMainWindow.show();
    trace_debug("Éxécution de l'application");
    return QApp.exec();
}
