#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application( int & argc, char ** argv );
    bool loadSettings();
    bool configure();

signals:

public slots:

};

#endif // APPLICATION_H
