#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "modals/viewprofiles.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QToolBar>
#include <QMessageBox>

MainWindow::MainWindow(QSqlDatabase &db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , database(db)
{
    ui->setupUi(this);

    // Get the central widget
    QWidget *central = centralWidget();

    // Set the main layout
    QHBoxLayout *layout = new QHBoxLayout;

    // @TODO - Change
    QVBoxLayout *leftLayout = new QVBoxLayout;

    // Add sessions layout
    layout->addLayout(leftLayout);
    layout->addLayout(createSessionLayout(), 2);


    central->setLayout(layout);

    // Add Toolbar
    setupMenuBar();
}



MainWindow::~MainWindow()
{
    delete ui;
}

QVBoxLayout *MainWindow::createSessionLayout()
{
    QVBoxLayout *sessionLayout = new QVBoxLayout;

    QLabel *title = new QLabel("Sessions");

    // Set layout title
    sessionLayout->addWidget(title);

    /**
     *
     * Sessions table
     *
     */
    sessionsTableWidget = new QTableWidget(0, 5, this);
    sessionsTableWidget->setHorizontalHeaderLabels({"Name", "Status", "Profile", "Cloud Provider", "Created At"});
    sessionsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    sessionLayout->addWidget(sessionsTableWidget);

    return sessionLayout;
}

void MainWindow::openProfiles() {
    ViewProfiles viewProfiles(database, this);

    viewProfiles.setWindowModality(Qt::ApplicationModal);
    viewProfiles.setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowTitleHint);

    viewProfiles.exec();
}

void MainWindow::setupMenuBar() {
    QMenu *actionsMenu = menuBar()->addMenu("Actions");

    // Profiles button
    QAction *profilesAction = new QAction("Profiles", this);
    profilesAction->setToolTip("Configure profiles to run OpenFOAM simulations");
    actionsMenu->addAction(profilesAction);

    connect(profilesAction, &QAction::triggered, this, &MainWindow::openProfiles);
}

void MainWindow::exit() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Quit", "Are you sure you want to quit?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}


