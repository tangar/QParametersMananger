#include "inputparser.h"

InputParser::InputParser( QObject * parent ) :
    QObject( parent )
{
}

QList<ParameterItem> InputParser::readItems( QFile * file )
{
    QList<ParameterItem> parameterList;
}
