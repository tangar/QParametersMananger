#include "inputparser.h"
#include "logger.h"

#include <QFile>
#include <QStringList>
#include <math.h>

#define DEF_SEPARATOR ";"

InputParser::InputParser( QObject * parent ) :
    QObject( parent )
{
}

QList<ParameterItem> InputParser::readItems( QString source )
{
    QList<ParameterItem> parameterList;        
    ParameterItem * parameterItem;
    char buf[1024];
    qint64 ret;

    QFile file( source );
    if( !file.exists() )
    {
        LOG_DEBUG( tr( "Input parser" ), tr( "input file doesn't exist" ) );
        goto finish;
    }

    if( !file.open( QIODevice::ReadOnly ) )
    {
        LOG_DEBUG( tr( "Input parser" ), tr( "can not open input file" ) );
        goto finish;
    }

    ret = file.readLine( buf, sizeof( buf ) );
    while ( ret > 0 )
    {
        QString line = QString( buf );
        LOG_DEBUG( tr( "Input parser" ), tr( "string from file: %1" ).arg(line) );

        parameterItem = new  ParameterItem();
        if ( parseLine( line, parameterItem ) )
            parameterList.append( * parameterItem );

        ret = file.readLine( buf, sizeof( buf ) );
    }

    finish:
        return parameterList;
}

bool InputParser::parseLine(QString line, ParameterItem *item)
{    
    QStringList fields;
    qreal tempReal1, tempReal2, tempReal3;
    bool tempRet1, tempRet2, tempRet3;
    int tempInt;
    bool tempRet;
    QString tempString;

    // line structure:
    // [ 0 ]    [ 1 ]   [ 2 ]       [ 3 ]       [ 4 ]   [ 5 ]       [ 6 ]        [ 7 ]      [ 8 ]
    // NUMBER;  NAME;   MIN;        MAX;        DEF;    ALARM_CODE  TYPE         BLOCKED    resolution;
    // int      QString int         int         int     QString     QString      bool       int
    // number   comment lowLimit    HighLimit   defVlue code        V/A/s/m/degC isNA       resolution

#define COLUMN_COUNT    9
#define DEF_COMMENT     1
#define DEF_TYPE        6
#define DEF_LOW         2
#define DEF_HIGH        3
#define DEF_DEF         4
#define DEF_RES         8
#define DEF_BLOCKED     7

    fields = line.split( DEF_SEPARATOR, QString::KeepEmptyParts, Qt::CaseInsensitive );
    if ( fields.length() != COLUMN_COUNT )
    {
        LOG_DEBUG( tr( "Input parser" ), tr( "Incorrect line format" ) );
        return false;
    }

    // set number of parameter
    tempInt = fields.at( 0 ).toInt( &tempRet );
    if ( tempRet ) item->setNumber( tempInt );
    else return false;

    // set comment and type for parameter
    tempString = fields.at( DEF_COMMENT );
    item->setComment( tempString );
    tempString = fields.at( DEF_TYPE );
    item->setType( tempString );

    // get diapasons
    tempReal1 = fields.at( DEF_LOW  ).toInt( &tempRet1 );
    tempReal2 = fields.at( DEF_HIGH ).toInt( &tempRet2 );
    tempReal3 = fields.at( DEF_DEF  ).toInt( &tempRet3 );
    tempInt   = fields.at( DEF_RES  ).toInt( &tempRet );

    // in case of incorrect numbers - write zeroes and mark parameter as "unprocessed"
    if ( !( tempRet1 && tempRet2 && tempRet3 && tempRet ) )
    {
        LOG_DEBUG( tr( "Input parser" ), tr( "Incorrect line fields. All set to zeroes" ) );
        item->setLowLimit( 0 );
        item->setHighLimit( 0 );
        item->setDefValue( 0 );
        item->setResolution( 0 );
        item->setIsNa( true );
    }
    else
    {
        item->setResolution( tempInt );
        int resolution = item->getResolution();
        int grade = pow( 10, resolution );
        item->setLowLimit ( (int)( tempReal1 * grade ) );
        item->setHighLimit( (int)( tempReal2 * grade ) );
        item->setDefValue ( (int)( tempReal3 * grade ) );
    }

    // set "can be blocked" field
    if ( fields.at( DEF_BLOCKED ) == "+" )
        item->setIsNa( true );
    else
        item->setIsNa( false );


    item->print();

    return true;
}
