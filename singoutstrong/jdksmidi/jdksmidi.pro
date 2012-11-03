#-------------------------------------------------
#
# Project created by QtCreator 2012-05-02T17:22:54
#
#-------------------------------------------------

QT       -= core gui

TARGET = jdksmidi
TEMPLATE = lib

DEFINES += JDKSMIDI_LIBRARY

SOURCES += \
    src/jdksmidi_utils.cpp \
    src/jdksmidi_track.cpp \
    src/jdksmidi_tick.cpp \
    src/jdksmidi_tempo.cpp \
    src/jdksmidi_sysex.cpp \
    src/jdksmidi_smpte.cpp \
    src/jdksmidi_showcontrolhandler.cpp \
    src/jdksmidi_showcontrol.cpp \
    src/jdksmidi_sequencer.cpp \
    src/jdksmidi_queue.cpp \
    src/jdksmidi_process.cpp \
    src/jdksmidi_parser.cpp \
    src/jdksmidi_multitrack.cpp \
    src/jdksmidi_msg.cpp \
    src/jdksmidi_midi.cpp \
    src/jdksmidi_matrix.cpp \
    src/jdksmidi_manager.cpp \
    src/jdksmidi_keysig.cpp \
    src/jdksmidi_filewritemultitrack.cpp \
    src/jdksmidi_filewrite.cpp \
    src/jdksmidi_fileshow.cpp \
    src/jdksmidi_filereadmultitrack.cpp \
    src/jdksmidi_fileread.cpp \
    src/jdksmidi_file.cpp \
    src/jdksmidi_edittrack.cpp \
    src/jdksmidi_driverdump.cpp \
    src/jdksmidi_driver.cpp \
    src/jdksmidi_advancedsequencer.cpp \
    src/win32/jdksmidi_driverwin32.cpp

INCLUDEPATH += $$PWD/include

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE148A2BE
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = jdksmidi.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:LIBS += -lwinmm -L./
win32:DEFINES+=__WINDOWS_MM__

HEADERS += \
    include/jdksmidi/utils.h \
    include/jdksmidi/track.h \
    include/jdksmidi/tick.h \
    include/jdksmidi/tempo.h \
    include/jdksmidi/sysex.h \
    include/jdksmidi/song.h \
    include/jdksmidi/smpte.h \
    include/jdksmidi/showcontrolhandler.h \
    include/jdksmidi/showcontrol.h \
    include/jdksmidi/sequencer.h \
    include/jdksmidi/queue.h \
    include/jdksmidi/process.h \
    include/jdksmidi/parser.h \
    include/jdksmidi/multitrack.h \
    include/jdksmidi/msg.h \
    include/jdksmidi/midi.h \
    include/jdksmidi/matrix.h \
    include/jdksmidi/manager.h \
    include/jdksmidi/keysig.h \
    include/jdksmidi/filewritemultitrack.h \
    include/jdksmidi/filewrite.h \
    include/jdksmidi/fileshow.h \
    include/jdksmidi/filereadmultitrack.h \
    include/jdksmidi/fileread.h \
    include/jdksmidi/file.h \
    include/jdksmidi/edittrack.h \
    include/jdksmidi/driverwin32.h \
    include/jdksmidi/driverdump.h \
    include/jdksmidi/driver.h \
    include/jdksmidi/advancedsequencer.h \
    include/jdksmidi/world.h
