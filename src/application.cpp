#include "application.h"

Application::Application( int & argc, char ** argv )
    :QApplication( argc, argv )
{    
    window.show();
}

bool Application::loadSettings()
{
    bool ret;
    ret = true;
    return ret;
}

bool Application::configure()
{
    bool ret;
    ret = true;
    return ret;
}
