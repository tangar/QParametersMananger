#include "mainwindow.h"
#include "ui_mainwindow.h"

// русский комментарий

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( ui->pushButton, SIGNAL( pressed() ), this, SIGNAL( descriptinFileRequest() ) ) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
