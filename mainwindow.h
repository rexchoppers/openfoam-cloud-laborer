#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QSqlDatabase &db, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openProfiles();

private:
    Ui::MainWindow *ui;

    // Variables
    QTableWidget *sessionsTableWidget;
    QSqlDatabase &database;

    // Methods
    QVBoxLayout* createSessionLayout();
    void setupMenuBar();
    void exit();
};
#endif // MAINWINDOW_H
