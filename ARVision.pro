#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T12:15:57
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ARVision
TEMPLATE = app


SOURCES += main.cpp\
        source.cpp \
    database.cpp \
    login.cpp \
    mainwindow.cpp \
    customers.cpp \
    mainsettings.cpp \
    customerprofile.cpp \
    newaccount.cpp \
    newpurchase.cpp \
    optimize.cpp \
    spectacles.cpp \
    newspectacles.cpp \
    newcontacts.cpp \
    spectaclesprint.cpp \
    clientprint.cpp \
    labprint.cpp \
    usermanagement.cpp \
    selectuser.cpp \
    newuser.cpp

HEADERS  += source.h \
    database.h \
    login.h \
    mainwindow.h \
    customers.h \
    mainsettings.h \
    customerprofile.h \
    newaccount.h \
    newpurchase.h \
    optimize.h \
    spectacles.h \
    newspectacles.h \
    newcontacts.h \
    spectaclesprint.h \
    clientprint.h \
    labprint.h \
    usermanagement.h \
    selectuser.h \
    newuser.h

FORMS    += source.ui \
    login.ui \
    mainwindow.ui \
    customers.ui \
    mainsettings.ui \
    customerprofile.ui \
    newaccount.ui \
    newpurchase.ui \
    optimize.ui \
    spectacles.ui \
    newspectacles.ui \
    newcontacts.ui \
    spectaclesprint.ui \
    clientprint.ui \
    labprint.ui \
    usermanagement.ui \
    selectuser.ui \
    newuser.ui
