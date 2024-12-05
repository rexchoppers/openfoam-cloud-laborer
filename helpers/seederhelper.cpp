#include "seederhelper.h"

#include <QSqlQuery>
#include <QSqlError>

SeederHelper::SeederHelper(QSqlDatabase &database) : database(database) {}

const QList<QPair<QString, QString>> SeederHelper::cloudProviders = {
    {"GCP", "Google Cloud Platform"},
};

void SeederHelper::run() {
    if (!database.isOpen()) {
        qDebug() << "Database is not open";
        return;
    }

    // Add cloud providers to the database
    QSqlQuery query(database);

    for (const auto &provider : cloudProviders) {
        query.prepare("INSERT OR IGNORE INTO cloud_providers (name) VALUES (?)");
        query.addBindValue(provider.second);

        if (!query.exec()) {
            qDebug() << "Failed to insert cloud provider:" << query.lastError().text();
        } else {
            qDebug() << "Cloud provider added:" << provider.second;
        }
    }
}
