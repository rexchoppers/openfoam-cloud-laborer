#include "viewprofiles.h"
#include "modals/ui_viewprofiles.h"

ViewProfiles::ViewProfiles(QSqlDatabase &db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ViewProfiles)
    , database(db)
{
    ui->setupUi(this);
}

ViewProfiles::~ViewProfiles()
{
    delete ui;
}
