#-------------------------------------------------
#
# Project created by QtCreator 2018-09-20T22:56:38
#
#-------------------------------------------------

QT       += core gui charts sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = BDMedicalApp
TEMPLATE = app

#INCLUDEPATH += C:\OpenCV\install\include

#LIBS += -LC:\OpenCV\install\x86\mingw\lib
#LIBS += -lopencv_core341 -lopencv_imgproc341 -lopencv_highgui341 \
#-lopencv_ml341 -lopencv_video341 -lopencv_features2d341 -lopencv_calib3d341 \
#-lopencv_objdetect341 -lopencv_flann341 -lopencv_videoio341

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
    Managers/databasemanager.cpp \
    appcore.cpp \
    Common/Models/entity.cpp \
    Common/Models/circlemodel.cpp \
    Common/Models/rectmodel.cpp \
    Common/Models/patientmodel.cpp \
    Common/Models/imagemodel.cpp \
    Common/Models/foldermodel.cpp \
    patientinputform.cpp \
    appmodel.cpp \
    imageeditor.cpp \
    Managers/Helpers/queryripper.cpp \
    Common/consts.cpp \
    Common/Models/linemodel.cpp \
    Common/Models/markmodel.cpp

HEADERS += \
        mainwindow.h \
    Managers/databasemanager.h \
    Common/magic.h \
    appcore.h \
    Common/Models/entity.h \
    Common/Models/circlemodel.h \
    Common/Models/rectmodel.h \
    Common/Models/models.h \
    Common/Models/patientmodel.h \
    Common/Models/imagemodel.h \
    Common/Models/foldermodel.h \
    patientinputform.h \
    appmodel.h \
    Common/consts.h \
    imageeditor.h \
    Managers/Helpers/queryripper.h \
    Common/Models/linemodel.h \
    Common/Models/markmodel.h

FORMS += \
        mainwindow.ui \
    patientinputform.ui

RESOURCES += \
    resources.qrc
