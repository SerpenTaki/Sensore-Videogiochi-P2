######################################################################
# Automatically generated by qmake (3.1) Tue Aug 27 14:48:50 2024
######################################################################

TEMPLATE = app
TARGET = Sensore-Videogiochi-P2
INCLUDEPATH += .
QT += widgets
QT += charts
QT += xml

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x060000 # disables all APIs deprecated in Qt 6.0.0 and earlier

# Input
HEADERS += core_files/headers/contentvisitor.h \
           core_files/headers/fisico.h \
           core_files/headers/magico.h \
           core_files/headers/sacro.h \
           core_files/headers/sensoreDanno.h \
           core_files/headers/visitor.h \
           QT_files/headers/aggiungiSensore.h \
           QT_files/headers/content.h \
           QT_files/headers/leftSideBar.h \
           QT_files/headers/mainWindow.h \
           QT_files/headers/modificaSensore.h \
           QT_files/headers/rightSideBar.h \
           QT_files/headers/viewlib.h
SOURCES += main.cpp \
           core_files/contentvisitor.cpp \
           core_files/fisico.cpp \
           core_files/magico.cpp \
           core_files/sacro.cpp \
           core_files/sensoreDanno.cpp \
           QT_files/aggiungiSensore.cpp \
           QT_files/content.cpp \
           QT_files/leftSideBar.cpp \
           QT_files/mainWindow.cpp \
           QT_files/modificaSensore.cpp \
           QT_files/rightSideBar.cpp
