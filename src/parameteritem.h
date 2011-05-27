#ifndef PARAMETERITEM_H
#define PARAMETERITEM_H

#include <QString>
#include <QObject>
#include "property.h"
#include "logger.h"

class ParameterItem
{
public:

    PROPERTY( int, number, setNumber, getNumber );
    PROPERTY( int, lowLimit, setLowLimit, getLowLimit );
    PROPERTY( int, highLimit, setHighLimit, getHighLimit );
    PROPERTY( int, defValue, setDefValue, getDefValue );
    PROPERTY( int, resolution, setResolution, getResolution );
    PROPERTY( bool, isNa, setIsNa, getIsNa );
    PROPERTY( QString, comment, setComment, getComment );
    PROPERTY( QString, name, setName, getName );
    PROPERTY( QString, type, setType, getType );

    ParameterItem()
    {
        setName( QObject::tr( "" ) );
        setComment( QObject::tr( "" ) );
        setNumber( 0 );
        setHighLimit( 0 );
        setDefValue( 0 );
        setResolution( 0 );
        setIsNa( true );
    }

    void print()
    {
        LOG_DEBUG( QObject::tr( "ParameterItem" ),
                   QObject::tr( "Print parameter #%1:\n%2\nmin:%3\tmax:%4\tdefault:%5\t\tres:%6\t%7\tBlocked:%8" ).arg( getNumber() ).arg( getComment() ).arg( getLowLimit() ).arg( getHighLimit() ).arg( getDefValue() ).arg( getResolution() ).arg( getType() ).arg( getIsNa() ) );
    }
};

#endif // PARAMETERITEM_H

