#ifndef SEEDERHELPER_H
#define SEEDERHELPER_H

#include <QSqlDatabase>


class SeederHelper
{
public:
    SeederHelper(QSqlDatabase &db);

    void run();

private:
    QSqlDatabase &database;

    static const QList<QPair<QString, QString>> cloudProviders;
};

#endif // SEEDERHELPER_H
