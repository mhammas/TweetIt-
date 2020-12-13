QT += core gui widgets
DESTDIR = $$PWD/bin

TARGET = KeywordSearch
TEMPLATE = app

FORMS += \
    mainwindow.ui

HEADERS += \
    database.h \
    mainwindow.h \
    map.h

SOURCES += \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp

