#include "helpers/seederhelper.h"
#include "mainwindow.h"
#include "helpers/databasehelper.h"
#include <QDir>


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Current working directory:" << QDir::currentPath();


    DatabaseHelper& dbHelper = DatabaseHelper::getInstance();

    if (!dbHelper.init()) {
        qDebug() << "Failed to init database";
        return -1;
    }

    // Run all migrations
    for (const auto &migration : DatabaseHelper::migrations) {
        if (!dbHelper.applyMigration(migration.name, migration.sql)) {
            qDebug() << "Failed to apply migration:" << migration.name;
            return -1;
        }
    }

    // Run all seeders
    SeederHelper seeder(dbHelper.getDatabaseInstance());
    seeder.run();

    MainWindow w(dbHelper.getDatabaseInstance());
    w.setWindowTitle("OpenFoam Cloud Laborer");


    w.show();
    return a.exec();
}
