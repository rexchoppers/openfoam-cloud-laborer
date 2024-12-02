#include "mainwindow.h"
#include "helpers/databasehelper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("OpenFoam Cloud Laborer");

    DatabaseHelper databaseHelper = DatabaseHelper("openfoam-cloud-laborer");
    databaseHelper.init();


    w.show();
    return a.exec();
}
