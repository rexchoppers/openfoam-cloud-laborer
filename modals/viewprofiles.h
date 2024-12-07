#ifndef VIEWPROFILES_H
#define VIEWPROFILES_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class ViewProfiles;
}

class ViewProfiles : public QDialog
{
    Q_OBJECT

public:
    explicit ViewProfiles(QSqlDatabase &db, QWidget *parent = nullptr);
    ~ViewProfiles();

private:
    Ui::ViewProfiles *ui;
    QSqlDatabase &database;
};

#endif // VIEWPROFILES_H
