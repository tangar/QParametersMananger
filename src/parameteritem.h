#ifndef PARAMETERITEM_H
#define PARAMETERITEM_H

#include <QString>
#include "property.h"

class ParameterItem
{
public:

    PROPERTY( int, lowLimit, setLowLimit, lowLimit );
    PROPERTY( int, highLimit, setHighLimit, highLimit );
    PROPERTY( int, defValue, setDefValue, defValue );
    PROPERTY( int, resolution, setResolution, resolution );
    PROPERTY( int, isNa, setIsNa, isNa );
    PROPERTY( QString, comment, setComment, comment );
    PROPERTY( QString, name, setName, name );

    ParameterItem()
    {
        setName( tr( "" ) );
        setComment( tr( "" ) );
        setHighLimit( 0 );
        setDefValue( 0 );
        setResolution( 0 );
        setIsNa( true );
    }
};

#endif // PARAMETERITEM_H

