#include "viewprofiles.h"
#include "ui_viewprofiles.h"

ViewProfiles::ViewProfiles(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ViewProfiles)
{
    ui->setupUi(this);
}

ViewProfiles::~ViewProfiles()
{
    delete ui;
}
