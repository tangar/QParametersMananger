#include "inputparser.h"
#include "logger.h"

#include <QFile>
#include <QStringList>
#include <math.h>


// line structure:
// [ 0 ]    [ 1 ]   [ 2 ]       [ 3 ]       [ 4 ]   [ 5 ]       [ 6 ]
// NUMBER;  NAME;   MIN;        MAX;        DEF;    ALARM_CODE  TYPE
// int      QString int         int         int     QString     QString
// number   comment lowLimit    HighLimit   defVlue code        V/A/s/m/degC

#define MIN_COLUMN_COUNT    7
#define DEF_NUMBER          0
#define DEF_COMMENT         1
#define DEF_TYPE            6
#define DEF_LOW             2
#define DEF_HIGH            3
#define DEF_DEF             4

#define DEF_SEPARATOR ";"

InputParser::InputParser( QObject * parent ) :
    QObject( parent )
{
}

bool InputParser::readItems( QString source, QList<ParameterItem> * parameterList )
{
    ParameterItem * parameterItem;
    char buf[1024];
    qint64 ret;

    QFile file( source );
    if( !file.exists() )
    {
        LOG_DEBUG( tr( "Input parser" ), tr( "input file doesn't exist" ) );
        return false;
    }

    if( !file.open( QIODevice::ReadOnly ) )
    {
        LOG_DEBUG( tr( "Input parser" ), tr( "can not open input file" ) );
        return false;
    }

    do
    {
        ret = file.readLine( buf, sizeof( buf ) );
        QString line = QString( buf );
        if ( ret > 0 )
        {
            LOG_DEBUG( tr( "Input parser" ), tr( "string from file: %1" ).arg(line) );

            parameterItem = new  ParameterItem();
            if ( parseLine( line, parameterItem ) )
                parameterList->append( * parameterItem );
        }
    } while ( ret > 0 );

    return true;
}

int InputParser::getFractionalLength( double value )
{
    int retValue = 0;
    double fraction;

    value = ( value < 0 ) ? ( value * -1 ) : value;

    do
    {
        fraction = value - ( int ) value;
        if ( fraction != 0 )
        {
            retValue += 1;
            value *= 10;
        }
    }  while ( fraction != 0 );

    return retValue;
}

bool InputParser::parseLine(QString line, ParameterItem *item)
{    
    QStringList fields;
    int resolution;
    double tempReal1, tempReal2, tempReal3;
    bool tempRet1, tempRet2, tempRet3;
    int temp;
    QString tempString;
    QString defString;

    resolution = 0;

    // fix unised '\n'
    temp = line.indexOf( "\n" );
    if ( temp != -1 ) line.remove( temp, 1 );

    fields = line.split( DEF_SEPARATOR, QString::KeepEmptyParts, Qt::CaseInsensitive );
    if ( fields.length() < MIN_COLUMN_COUNT )
    {
        LOG_DEBUG( tr( "Input parser" ), tr( "Incorrect line format" ) );
        return false;
    }

    // set number of parameter
    temp = fields.at( DEF_NUMBER ).toInt( &tempRet1 );
    if ( tempRet1 ) item->setNumber( temp );
    else return false;

    // set comment and type for parameter
    tempString = fields.at( DEF_COMMENT );
    item->setComment( tempString );
    tempString = fields.at( DEF_TYPE );
    item->setType( tempString );

    // get diapasons
    tempReal1 = fields.at( DEF_LOW  ).toDouble( &tempRet1 );
    tempReal2 = fields.at( DEF_HIGH ).toDouble( &tempRet2 );
    tempReal3 = fields.at( DEF_DEF  ).toDouble( &tempRet3 );
    defString = fields.at( DEF_DEF );

    // in case of incorrect numbers - write zeroes and mark parameter as "unprocessed"
    if ( !( tempRet1 && tempRet2 ) )
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
        // determine "can be blocked" flag
        // clause: '*' in default value OR 'мнап'
        temp = defString.indexOf("*");
        int letterIndex = defString.indexOf( "м", 0, Qt::CaseInsensitive );
        if ( ( temp != -1 ) || ( letterIndex != -1 ) )
        {
            if ( temp != -1 )
            {
                defString.remove( temp, 1 );
                tempReal3 = defString.toInt( &tempRet3 );
            }
            item->setIsNa( true );
        }
        else
        {
            item->setIsNa( false );
        }

        // determine length of fractional part
        if ( tempRet1 )
        {
            temp = getFractionalLength( tempReal1 );
            resolution = ( resolution < temp ) ? temp : resolution;
        }
        if ( tempRet2 )
        {
            temp = getFractionalLength( tempReal2 );
            resolution = ( resolution < temp ) ? temp : resolution;
        }
        if ( tempRet3 )
        {
            temp = getFractionalLength( tempReal3 );
            resolution = ( resolution < temp ) ? temp : resolution;
        }
        item->setResolution( resolution );

        // write values modified to integer form
        if ( tempRet1 )
            item->setLowLimit( (int)( tempReal1 * pow( 10, resolution ) ) );
        else item->setLowLimit( 0 );
        if ( tempRet2 )
            item->setHighLimit( (int)( tempReal2 * pow( 10, resolution ) ) );
        else item->setHighLimit( 0 );
        if ( tempRet3 )
            item->setDefValue( (int)( tempReal3 * pow( 10, resolution ) ) );
        else item->setDefValue( 0 );
    }

    item->print();

    return true;
}
