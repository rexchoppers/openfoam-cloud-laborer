#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QString>
#include <QList>

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

private:
    QString name;

    QList<Migration> migrations;

    bool createMigrationTable();
};

#endif // DATABASEHELPER_H
