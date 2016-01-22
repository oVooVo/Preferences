#-------------------------------------------------
#
# Project created by QtCreator 2015-12-29T15:45:08
#
#-------------------------------------------------

QT       += widgets

TARGET = Preferences
TEMPLATE = lib

DEFINES += PREFERENCES_LIBRARY

gcc {
    QMAKE_CXXFLAGS += -std=c++0x
}

SOURCES += preferences.cpp \
    preference.cpp \
    interfaceoptions.cpp \
    preferencedialog.cpp \
    filedialogwidget.cpp

HEADERS += preferences.h\
    preferences_global.h \
    preference.h \
    interfaceoptions.h \
    preferencedialog.h \
    filedialogwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    preferencedialog.ui \
    filedialogwidget.ui

RESOURCES += \
    ressources.qrc
