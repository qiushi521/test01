#-------------------------------------------------
#
# Project created by QtCreator 2018-06-26T20:18:02
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TM_Autoinstall
TEMPLATE = app
#QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"//必须管理员身份运行qt
QTPLUGIN += QSQLMYSQL


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    copypythonlib.cpp \
    IO_mysqlinterface.cpp

HEADERS += \
        mainwindow.h \
    copypythonlib.h \
    IO_mysqlinterface.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc
