#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T00:35:10
#
#-------------------------------------------------

QT       += core gui

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameLab4
TEMPLATE = app



TRANSLATIONS = translations/arrowpad_en.ts \
        translations/arrowpad_ru.ts

SOURCES += src/main.cpp \
        src/mainwindow.cpp

INCLUDEPATH += headers

HEADERS  += headers/mainwindow.h

FORMS    += ui/mainwindow.ui

DISTFILES += \
    statistics.txt

RESOURCES += \
    translations/translations.qrc
