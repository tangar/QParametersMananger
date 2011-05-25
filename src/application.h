#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "mainwindow.h"

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application( int & argc, char ** argv );
    bool loadSettings();
    bool configure();

signals:

public slots:

private:
    MainWindow window;

};

#endif // APPLICATION_H
