#include "mainwindow.h"
#include "helpers/databasehelper.h"
#include <QDir>


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("OpenFoam Cloud Laborer");

    qDebug() << "Current working directory:" << QDir::currentPath();


    DatabaseHelper databaseHelper = DatabaseHelper("openfoam-cloud-laborer.db");
    databaseHelper.init();


    w.show();
    return a.exec();
}
