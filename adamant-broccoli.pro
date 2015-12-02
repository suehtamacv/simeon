TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle qt

SOURCES += src/main.cpp \
    src/cpp/TransmissionBitrate.cpp \
    src/cpp/MQAM_ModulationScheme.cpp \
    src/cpp/dB.cpp

HEADERS += src/lib/ModulationScheme.h \
    src/lib/TransmissionBitrate.h \
    src/lib/MQAM_ModulationScheme.h \
    src/lib/dB.h \
    src/lib/Device.h

LIBS += -lboost_system

OTHER_FILES += README.md \
               .astylerc


INCLUDEPATH += src/lib/
