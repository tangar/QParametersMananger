#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <QObject>
#include <QList>
#include <QFile>
#include "parameteritem.h"

class InputParser : public QObject
{
    Q_OBJECT
public:
    explicit InputParser( QObject * parent = 0 );
    static QList <ParameterItem> readItems( QFile * file );

signals:

public slots:

};

#endif // INPUTPARSER_H
