TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle qt

SOURCES += src/main.cpp \
    src/GeneralClasses/TransmissionBitrate.cpp \
    src/ModulationSchemes/MQAM_ModulationScheme.cpp \
    src/Devices/Fiber.cpp \
    src/Devices/SSS.cpp \
    src/Devices/Amplifier.cpp \
    src/GeneralClasses/Gain.cpp \
    src/GeneralClasses/Power.cpp \
    src/Devices/Device.cpp \
    src/Devices/Splitter.cpp


HEADERS += include/ModulationSchemes/ModulationScheme.h \
    include/ModulationSchemes/MQAM_ModulationScheme.h \
    include/GeneralClasses/TransmissionBitrate.h \
    include/Devices/Device.h \
    include/Devices/Fiber.h \
    include/Devices/SSS.h \
    include/Devices/Amplifier.h \
    include/GeneralClasses/Gain.h \
    include/GeneralClasses/Power.h \
    include/GeneralClasses/PhysicalConstants.h \
    include/Devices/Splitter.h

LIBS += -lboost_system

OTHER_FILES += README.md \
               .astylerc


INCLUDEPATH += include/
