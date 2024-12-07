#ifndef VIEWPROFILES_H
#define VIEWPROFILES_H

#include <QDialog>

namespace Ui {
class ViewProfiles;
}

class ViewProfiles : public QDialog
{
    Q_OBJECT

public:
    explicit ViewProfiles(QWidget *parent = nullptr);
    ~ViewProfiles();

private:
    Ui::ViewProfiles *ui;
};

#endif // VIEWPROFILES_H
