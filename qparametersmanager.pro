TEMPLATE = app
TARGET = qparametersmanager
DEPENDPATH += . debug release src ui translations
INCLUDEPATH += . src
UI_DIR = tmp
MOC_DIR = tmp
RCC_DIR = tmp

QT += core gui

unix {
    target.path = /usr/bin
    INSTALLS += target
    data.path = /usr/share/qparametersmanager
    data.files += config.ini
    INSTALLS += data
    DEFINES += UNIX_BUILD
}

CONFIG(debug, debug|release) {
    DEFINES += DEBUG
    linux-g++: OBJECTS_DIR = debug
    DESTDIR = debug
    CONFIG += console
    QMAKE_CXXFLAGS_DEBUG += -pg
    QMAKE_LFLAGS_DEBUG += -pg
}
else {
    DEFINES += QT_NO_DEBUG_OUTPUT
    linux-g++: OBJECTS_DIR = release
    DESTDIR = release
}

#TRANSLATIONS += \
#    qparametersmanager_en.ts \
#    qparametersmanager_ru.ts

SOURCES += \
    src/main.cpp \
    src/logger.cpp \
    src/application.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/logger.h \
    src/application.h \
    src/mainwindow.h

#win32:RC_FILE = qparametersmanager.rc

OTHER_FILES += \
    README \
    Changelog.txt \
    config.ini \
    CODING_STYLE_ru.txt \
    CODING_STYLE_en.txt \
    qparametersmanager.rc

RESOURCES += \
    resources.qrc

FORMS += \
    src/mainwindow.ui
