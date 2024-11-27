#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Get the central widget
    QWidget *central = centralWidget();

    // Set the
    QHBoxLayout *layout = new QHBoxLayout;

    // Add sessions layout


    central->setLayout(layout);
}



MainWindow::~MainWindow()
{
    delete ui;
}

QVBoxLayout *MainWindow::createSessionLayout()
{

}

