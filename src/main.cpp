#include <QLocale>
#include <QTranslator>
#include <QTextCodec>


#include "logger.h"
#include "application.h"

// комментарий на руссоко языке

int main( int argc, char * argv[] )
{
    Logger logger;
#ifdef DEBUG
    logger.setLogFile( "debug.log" );
#endif


    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("Windows-1251") );
    QTextCodec::setCodecForTr( QTextCodec::codecForName("Windows-1251") );

    Application app( argc, argv );
    QTranslator translator;
    QString locale = QLocale::system().name();
    locale.truncate( 2 );
    const QString codecName = ":/translations/qradiotray_" + locale;
    translator.load( codecName );
    app.installTranslator( &translator );

    app.setQuitOnLastWindowClosed( true );
    if ( !app.loadSettings() || !app.configure() )
        return -1;

    return app.exec();
}

