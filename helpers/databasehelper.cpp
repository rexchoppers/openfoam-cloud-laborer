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
        qDebug() << "Error running migration SQL:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseHelper::applyMigration(const QString &migrationName, const QString &sql) {
    if (!database.isOpen()) {
        if(!database.open()) {
            qDebug() << "Error opening database for migrations:" << database.lastError().text();
            return false;
        }
    }

    // Check if query exists
    QSqlQuery existingMigrationQuery(database);
    existingMigrationQuery.prepare("SELECT COUNT(*) FROM migrations WHERE name ?");
    existingMigrationQuery.addBindValue(migrationName);
    if (!existingMigrationQuery.exec() || (existingMigrationQuery.next() && existingMigrationQuery.value(0).toInt() > 0)) {
        qDebug() << "Migration" << migrationName << "already applied.";
        return true;
    }

    // Run the migration
    QSqlQuery migrationQuery(database);
    if (!migrationQuery.exec(sql)) {
        qDebug() << "Error running migration SQL:" << migrationQuery.lastError().text();
        return false;
    }

    // Record the migration
    QSqlQuery recordMigrationQuery(database);
    recordMigrationQuery.prepare("INSERT INTO migrations (name) VALUES (?)");
    recordMigrationQuery.addBindValue(migrationName);
    if (!recordMigrationQuery.exec()) {
        qDebug() << "Error recording migration:" << recordMigrationQuery.lastError().text();
        return false;
    }

    qDebug() << "Migration" << migrationName << "applied successfully";

    return true;
}
