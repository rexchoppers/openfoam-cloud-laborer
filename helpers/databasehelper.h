#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QString>

class DatabaseHelper
{
public:
    explicit DatabaseHelper(const QString &name);

    bool init();
    bool applyMigration(const QString &migrationName, const QString &sql);
    bool applyAllMigrations(const QList<QPair<QString, QString>> &migrations);

private:
    QString name;
    bool createMigrationTable();
};

#endif // DATABASEHELPER_H
