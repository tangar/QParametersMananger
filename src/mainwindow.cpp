#include "mainwindow.h"
#include "ui_mainwindow.h"

// русский комментарий

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionImport->setShortcut( QKeySequence::Open );

    //ui->actionQuit_4->setIcon( QIcon( ":/") );


    connect( ui->actionImport, SIGNAL( triggered() ), this, SIGNAL( descriptinFileRequest() ) ) ;
    connect( ui->actionQuit, SIGNAL( triggered() ), this, SIGNAL( quitRequest() ) );
    connect( ui->actionAbout_Qt, SIGNAL( triggered() ), this, SLOT ( QApplication::aboutQt() ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
