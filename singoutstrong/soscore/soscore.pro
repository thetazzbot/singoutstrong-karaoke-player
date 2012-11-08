#-------------------------------------------------
#
# Project created by QtCreator 2012-04-08T18:34:27
#
#-------------------------------------------------

QT       -= core gui

TARGET = soscore
TEMPLATE = lib

DEFINES += SOSCORE_LIBRARY

SOURCES += \
    src/audio/audioanalyzer/aubioanalyzer/aubioanalyzer.cpp \
    src/audio/audioio/rtaudioinput/rtaudio/rtaudio.cpp \
    src/audio/pitchrecord/pitchsample.cpp \
    src/audio/pitchrecord/pitchrecord.cpp \
    src/song/track.cpp \
    src/song/textdata.cpp \
    src/song/song.cpp \
    src/song/note.cpp \
    src/song/songcontrol.cpp \
    src/musichandlers/jdkmidihandler/jdkmidihandler.cpp \
    src/musichandlers/ultrastarparser/ultrastarparser.cpp \
    src/musichandlers/bassstreamaudiohandler/bassstreamaudiohandler.cpp \
    src/song/songsettings.cpp \
    src/audio/audioio/bassaudioinput/bassaudioinput.cpp \
    src/audio/audioio/rtaudioinput/rtaudioinput.cpp \
    src/soscore.cpp \
    src/sosdevice.cpp

HEADERS += \
    include/itrack.h \
    include/isong.h \
    include/ipitchsample.h \
    include/ipitchrecord.h \
    include/inote.h \
    include/iaudioio.h \
    include/iaudioanalyzer.h \
    src/essentials.h \
    src/soundproperties.h \
    src/audio/audioanalyzer/aubioanalyzer/aubioanalyzer.h \
    src/audio/audioanalyzer/aubioanalyzer/aubiofuncs.h \
    src/audio/audioio/rtaudioinput/rtaudio/rterror.h \
    src/audio/audioio/rtaudioinput/rtaudio/rtaudio.h \
    src/audio/pitchrecord/pitchrecord.h \
    src/audio/pitchrecord/pitchsample.h \
    include/itextdata.h \
    src/song/textdata.h \
    src/song/song.h \
    src/song/note.h \
    src/song/track.h \
    src/song/songcontrol.h \
    include/isongcontrol.h \
    include/isongsettings.h \
    src/musichandlers/jdkmidihandler/jdkmidihandler.h \
    src/musichandlers/ultrastarparser/ultrastarparser.h \
    src/musichandlers/bassstreamaudiohandler/bassstreamaudiohandler.h \
    src/musichandlers/imusichandler.h \
    src/implementations.h \
    src/audio/audioanalyzer/audioanalyzer.h \
    src/musichandlers/audiohandler.h \
    src/audio/audioio/rtaudioinput/rtaudioinput.h \
    src/audio/audioio/bassaudioinput/bassaudioinput.h \
    src/audio/audioio/audioinput.h \
    src/sosdevice.h \
    include/isosdevice.h \
    include/soscore.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEECB7B53
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = soscore.dll
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

INCLUDEPATH += $$PWD/../libs/aubio/include/aubio
INCLUDEPATH += $$PWD/../libs/aubio/include/fft
INCLUDEPATH += $$PWD/../libs/aubio/include/libsamplerate
INCLUDEPATH += $$PWD/../libs/aubio/include/libsndfile
INCLUDEPATH += $$PWD/../libs/rtaudio
INCLUDEPATH += $$PWD/../libs/log
INCLUDEPATH += $$PWD/../jdksmidi/include
DEPENDPATH += $$PWD/../jdksmidi/include

win32:LIBS += \
        -lwinmm -L./ \
        -ldsound -L./ \
        -lole32 -L./ \

win32:DEFINES+= \
        __WINDOWS_MM__ \
        __WINDOWS_DS__

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../jdksmidi/release/ -ljdksmidi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../jdksmidi/debug/ -ljdksmidi
else:symbian: LIBS += -ljdksmidi
else:unix: LIBS += -L$$OUT_PWD/../jdksmidi/ -ljdksmidi

symbian: LIBS += -lbass
else:unix|win32: LIBS += -L$$PWD/../libs/bass/ -lbass
symbian: LIBS += -lbass_fx
else:unix|win32: LIBS += -L$$PWD/../libs/bass/ -lbass_fx

INCLUDEPATH += $$PWD/../libs/bass
DEPENDPATH += $$PWD/../libs/bass
