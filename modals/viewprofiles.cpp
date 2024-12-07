#include "viewprofiles.h"
#include "modals/ui_viewprofiles.h"

#include <QSqlQuery>
#include <QVBoxLayout>
#include <QSqlError>
#include <QPushButton>

ViewProfiles::ViewProfiles(QSqlDatabase &db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ViewProfiles)
    , database(db)
{
    ui->setupUi(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    profilesListWidget = new QListWidget(this);
    mainLayout->addWidget(profilesListWidget);

    // Add Profile button
    QPushButton *addProfileButton = new QPushButton("Add Profile", this);
    mainLayout->addWidget(addProfileButton);

    setLayout(mainLayout);

    loadProfiles();
}

void ViewProfiles::loadProfiles() {
    profilesListWidget->clear();

    if (!database.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query(database);

    if (!query.exec("SELECT id, name FROM profiles")) {
        qDebug() << "Failed to fetch profiles:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        profilesListWidget->addItem(QString("ID: %1 - %2").arg(id).arg(name));
    }

}

ViewProfiles::~ViewProfiles()
{
    delete ui;
}
