#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication QApp(argc, argv);
    MainWindow CMainWindow;
    CMainWindow.show();

    return QApp.exec();
}
