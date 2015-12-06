TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle qt

SOURCES += src/main.cpp \
    src/GeneralClasses/TransmissionBitrate.cpp \
    src/Devices/Fiber.cpp \
    src/Devices/SSS.cpp \
    src/Devices/Amplifiers/Amplifier.cpp \
    src/GeneralClasses/Gain.cpp \
    src/GeneralClasses/Power.cpp \
    src/Devices/Splitter.cpp \
    src/Structure/Slot.cpp \
    src/Structure/Link.cpp \
    src/Structure/Node.cpp \
    src/ModulationSchemes/ModulationScheme.cpp \
    src/GeneralClasses/Signal.cpp \
    src/Devices/Amplifiers/LineAmplifier.cpp \
    src/Devices/Amplifiers/BoosterAmplifier.cpp \
    src/Devices/Amplifiers/PreAmplifier.cpp \
    src/Calls/Event.cpp \
    src/Calls/Call.cpp \
    src/Calls/CallGenerator.cpp \
    src/Structure/Topology.cpp \
    src/Devices/Amplifiers/EDFA.cpp \
    src/RWA/RoutingWavelengthAssignment.cpp \
    src/RWA/Routing/RoutingAlgorithm.cpp \
    src/RWA/WavelengthAssignment/WavelengthAssignmentAlgorithm.cpp \
    src/RWA/Route.cpp \
    src/RWA/Routing/DijkstraRoutingAlgorithm.cpp \
    src/RWA/Routing/StaticRouting/StaticRoutingAlgorithm.cpp \
    src/RWA/Routing/StaticRouting/MinimumHops.cpp \
    src/RWA/Routing/StaticRouting/ShortestPath.cpp


HEADERS += \
    include/GeneralClasses/TransmissionBitrate.h \
    include/Devices/Device.h \
    include/Devices/Fiber.h \
    include/Devices/SSS.h \
    include/Devices/Amplifiers/Amplifier.h \
    include/GeneralClasses/Gain.h \
    include/GeneralClasses/Power.h \
    include/GeneralClasses/PhysicalConstants.h \
    include/Devices/Splitter.h \
    include/Structure/Slot.h \
    include/Structure/Link.h \
    include/Structure/Node.h \
    include/ModulationSchemes/ModulationScheme.h \
    include/GeneralClasses/Signal.h \
    include/Devices/Amplifiers/LineAmplifier.h \
    include/Devices/Amplifiers/BoosterAmplifier.h \
    include/Devices/Amplifiers/PreAmplifier.h \
    include/Calls/Event.h \
    include/Calls/Call.h \
    include/Calls/CallGenerator.h \
    include/Structure/Topology.h \
    include/Devices/Amplifiers/EDFA.h \
    include/RWA/RoutingWavelengthAssignment.h \
    include/RWA/Routing/RoutingAlgorithm.h \
    include/RWA/WavelengthAssignment/WavelengthAssignmentAlgorithm.h \
    include/RWA/Route.h \
    include/RWA/Routing/DijkstraRoutingAlgorithm.h \
    include/RWA/Routing/StaticRouting/StaticRoutingAlgorithm.h \
    include/RWA/Routing/StaticRouting/MinimumHops.h \
    include/RWA/Routing/StaticRouting/ShortestPath.h

LIBS += -lboost_system -lboost_program_options

OTHER_FILES += README.md \
               .astylerc


INCLUDEPATH += include/
