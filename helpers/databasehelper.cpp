#include "databasehelper.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

DatabaseHelper::DatabaseHelper(const QString &name): name(name) {}

QList<DatabaseHelper::Migration> migrations = {
    {"create_profiles_table", R"()"},
    {"create_sessions_table", R"()"},
};

bool DatabaseHelper::init() {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(name);

    if (!database.open()) {
        qDebug() << "Could not open database: " << database.lastError().text();
        return false;
    }

    qDebug() << "Database file path:" << database.databaseName();
    qDebug() << "Database initialised";

    return createMigrationTable();

}

DatabaseHelper& DatabaseHelper::getInstance() {
    static DatabaseHelper instance("openfoam-cloud-laborer.db");
    return instance;
}

bool DatabaseHelper::createMigrationTable() {
    QSqlQuery query(database);
    QString sql = R"(CREATE TABLE IF NOT EXISTS migrations (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT UNIQUE NOT NULL, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP))";

    qDebug() << "Running migrations script";

    if (!query.exec(sql)) {
        qDebug() << "Error running migration SQL: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseHelper::applyMigration(const QString &migrationName, const QString &sql) {
    if (!database.isOpen()) {
        if(!database.open()) {
            qDebug() << "Error opening database for migrations: " << database.lastError().text();
            return false;
        }
    }

    QSqlQuery existingMigrationQuery(database);
    existingMigrationQuery.prepare("SELECT COUNT(*) FROM migrations WHERE name ?");
    existingMigrationQuery.addBindValue(migrationName);

    return false;
}
