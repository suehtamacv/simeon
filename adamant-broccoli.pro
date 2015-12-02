TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle qt

SOURCES += src/main.cpp \
    src/cpp/GeneralClasses/TransmissionBitrate.cpp \
    src/cpp/GeneralClasses/dB.cpp \
    src/cpp/ModulationSchemes/MQAM_ModulationScheme.cpp


HEADERS += src/lib/ModulationSchemes/ModulationScheme.h \
    src/lib/ModulationSchemes/MQAM_ModulationScheme.h \
    src/lib/GeneralClasses/TransmissionBitrate.h \
    src/lib/GeneralClasses/dB.h \
    src/lib/Devices/Device.h

LIBS += -lboost_system

OTHER_FILES += README.md \
               .astylerc


INCLUDEPATH += src/lib/
