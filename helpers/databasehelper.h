#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QString>
#include <QList>
#include <QSqlDatabase>

class DatabaseHelper
{
public:
    explicit DatabaseHelper(const QString &name);

    bool init();
    bool applyMigration(const QString &migrationName, const QString &sql);
    bool applyAllMigrations(const QList<QPair<QString, QString>> &migrations);

    struct Migration {
        QString name;
        QString sql;
    };

    static const QList<Migration> migrations;

    static DatabaseHelper& getInstance();

private:
    QString name;
    QSqlDatabase database;

    bool createMigrationTable();
};

#endif // DATABASEHELPER_H
