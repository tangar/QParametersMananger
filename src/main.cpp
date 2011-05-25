#include <QLocale>
#include <QTranslator>

#include "logger.h"
#include "application.h"

// ����������� �� ������� �����

int main( int argc, char * argv[] )
{
    Application app( argc, argv );
    QTranslator translator;
    Logger logger;

#ifdef DEBUG
    logger.setLogFile( "debug.log" );
#endif

    QString locale = QLocale::system().name();
    locale.truncate( 2 );
    const QString codecName = ":/translations/qradiotray_" + locale;
    translator.load( codecName );
    app.installTranslator( &translator );

    app.setQuitOnLastWindowClosed( false );
    if ( !app.loadSettings() || !app.configure() )
        return -1;

    return app.exec();
}

