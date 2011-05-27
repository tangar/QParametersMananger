#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QList>
#include "parameteritem.h"
#include "mainwindow.h"


class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application( int & argc, char ** argv );
    bool loadSettings();
    bool configure();

    QList <ParameterItem> parameterItemList;

signals:

public slots:
    void loadDescriptionFile( void );
    void onQuitRequest( void );

private:
    MainWindow * mainWindow;
    void createConnections( void );

};

#endif // APPLICATION_H
