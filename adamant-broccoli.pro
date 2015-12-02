TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle qt

SOURCES += src/main.cpp \
    src/GeneralClasses/TransmissionBitrate.cpp \
    src/GeneralClasses/dB.cpp \
    src/ModulationSchemes/MQAM_ModulationScheme.cpp \
    src/Devices/Fiber.cpp \
    src/Devices/SSS.cpp


HEADERS += include/ModulationSchemes/ModulationScheme.h \
    include/ModulationSchemes/MQAM_ModulationScheme.h \
    include/GeneralClasses/TransmissionBitrate.h \
    include/GeneralClasses/dB.h \
    include/Devices/Device.h \
    include/Devices/Fiber.h \
    include/Devices/SSS.h

LIBS += -lboost_system

OTHER_FILES += README.md \
               .astylerc


INCLUDEPATH += include/
