#-------------------------------------------------
#
# Project created by QtCreator 2012-05-03T12:17:49
#
#-------------------------------------------------

QT       += core gui \
            opengl \
            xml

TARGET = singoutstrong

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    audioinsettings.cpp \
    outputsettings.cpp \
    playlist.cpp \
    songwindow.cpp \
    generalsettings.cpp \
    highlightlist.cpp \
    windowbar.cpp \
    mainwindowevents.cpp \
    mainwindowslots.cpp \
    tutorialwindow.cpp \
    soscontext.cpp \
    soslyricswidget.cpp \
    sosnoteswidget.cpp \
    sossubwindow.cpp

HEADERS  += mainwindow.h \
    audioinsettings.h \
    outputsettings.h \
    playlist.h \
    songwindow.h \
    generalsettings.h \
    highlightlist.h \
    windowbar.h \
    tutorialwindow.h \
    soscontext.h \
    soslyricswidget.h \
    sosnoteswidget.h \
    sossubwindow.h \
    fileformats.h

FORMS    += mainwindow.ui \
    audioinsettings.ui \
    outputsettings.ui \
    playlist.ui \
    songwindow.ui \
    generalsettings.ui \
    windowbar.ui \
    tutorialwindow.ui

RC_FILE = singoutstrong.rc
CONFIG(debug, debug|release): DEFINES += DEBUG

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../soscore/release/ -lsoscore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../soscore/debug/ -lsoscore
else:symbian: LIBS += -lsoscore
else:unix: LIBS += -L$$OUT_PWD/../soscore/ -lsoscore

INCLUDEPATH += $$PWD/../soscore/include
INCLUDEPATH += $$PWD/../libs/log
DEPENDPATH += $$PWD/../soscore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../jdksmidi/release/ -ljdksmidi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../jdksmidi/debug/ -ljdksmidi
else:symbian: LIBS += -ljdksmidi
else:unix: LIBS += -L$$OUT_PWD/../jdksmidi/ -ljdksmidi

INCLUDEPATH += $$PWD/../jdksmidi/include
DEPENDPATH += $$PWD/../jdksmidi/include

RESOURCES += \
    resources.qrc
