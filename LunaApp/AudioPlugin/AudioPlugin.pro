include(../LunaPlugin.pri)

HEADERS += \
    audioplugin.h \
    audiomodel.h \
    audiochannelprocessor.h \
    audioprovider.h \
    fft.h \
    fftw3.h \
    samplebuffer.h

SOURCES += \
    audioplugin.cpp \
    audiomodel.cpp \
    audiochannelprocessor.cpp \
    audioprovider.cpp \
    fft.cpp \
    samplebuffer.cpp

RESOURCES += \
    qml.qrc

win32 {
    INCLUDEPATH += ./win32
    SOURCES += \
        win32/audiocapture.cpp \
        win32/win32errorhandling.cpp

    HEADERS += \
        win32/audiocapture.h \
        win32/win32errorhandling.h

    LIBS += -lmmdevapi -lole32 -llibfftw3f-3
    LIBS += -L$$PWD/lib/
}
