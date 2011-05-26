#include "application.h"
#include "inputparser.h"
#include "logger.h"

#include <QFileDialog>
#include <QString>

#include <QDebug>

Application::Application( int & argc, char ** argv )
    :QApplication( argc, argv )
{
    mainWindow = new MainWindow();

    createConnections();

    mainWindow->show();
}

bool Application::loadSettings()
{
    bool ret;
    ret = true;
    return ret;
}

bool Application::configure()
{
    bool ret;
    ret = true;
    return ret;
}

void Application::loadDescriptionFile(void)
{
    QFileDialog fileDialog;
    QString fileName;

    fileDialog.setDirectory( "./" );
    fileDialog.setNameFilter( tr( "Data tables (*.csv)" ) );
    fileDialog.setViewMode( QFileDialog::Detail );
    if ( fileDialog.exec() )
    {
        fileName = fileDialog.selectedFiles().first();
        LOG_DEBUG( tr( "Application" ), tr( "Selected file: %1" ).arg( fileName ) );
        InputParser::readItems( fileName );
    }
}

void Application::createConnections(void)
{
    connect( mainWindow, SIGNAL( descriptinFileRequest() ), this, SLOT( loadDescriptionFile() ) );
}
