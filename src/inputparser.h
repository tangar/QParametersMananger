#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <QObject>
#include <QList>
#include <QString>
#include "parameteritem.h"

class InputParser : public QObject
{
    Q_OBJECT
public:
    explicit InputParser( QObject * parent = 0 );
    static bool readItems( QString source, QList<ParameterItem> * parameterList );
    static bool parseLine( QString line, ParameterItem * item);
    static int getFractionalLength( double value );

signals:

public slots:

};

#endif // INPUTPARSER_H
