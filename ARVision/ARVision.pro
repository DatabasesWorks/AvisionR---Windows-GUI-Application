#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T12:15:57
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ARVision
TEMPLATE = app

QTPLUGIN += windowsprintersupport

SOURCES += main.cpp\
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
    newuser.cpp \
    modifyprofile.cpp \
    frames.cpp \
    newframes.cpp \
    editframe.cpp \
    lens.cpp \
    newlens.cpp \
    editlens.cpp \
    log.cpp \
    manual.cpp

HEADERS  += database.h \
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
    newuser.h \
    modifyprofile.h \
    frames.h \
    newframes.h \
    editframe.h \
    lens.h \
    newlens.h \
    editlens.h \
    log.h \
    manual.h

FORMS    += login.ui \
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
    newuser.ui \
    modifyprofile.ui \
    frames.ui \
    newframes.ui \
    editframe.ui \
    lens.ui \
    newlens.ui \
    editlens.ui \
    log.ui \
    manual.ui
