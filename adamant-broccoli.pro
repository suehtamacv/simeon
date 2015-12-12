TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle qt

QMAKE_CXXFLAGS += -std=c++11

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
    src/GeneralClasses/Signal.cpp \
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
    src/RWA/Routing/StaticRouting/ShortestPath.cpp \
    src/RWA/WavelengthAssignment/FirstFit.cpp \
    src/RWA/RegeneratorPlacement/RegeneratorPlacement.cpp \
    src/RWA/RegeneratorPlacement/NX_RegeneratorPlacement.cpp \
    src/RWA/RegeneratorPlacement/NodalDegreeFirst.cpp \
    src/Devices/Amplifiers/InLineAmplifier.cpp \
    src/RWA/RegeneratorAssignment/RegeneratorAssignment.cpp \
    src/RWA/RegeneratorAssignment/FirstLongestReach.cpp \
    src/RWA/TransparentSegment.cpp \
    src/GeneralClasses/ModulationScheme.cpp \
    src/Devices/Device.cpp \
    src/SimulationTypes/SimulationType.cpp \
    src/SimulationTypes/NetworkSimulation.cpp \
    src/RWA/Routing/LengthOccupationRoutingAvailability.cpp \
    src/SimulationTypes/Simulation_NetworkLoad.cpp


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
    include/GeneralClasses/Signal.h \
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
    include/RWA/Routing/StaticRouting/ShortestPath.h \
    include/RWA/WavelengthAssignment/FirstFit.h \
    include/RWA/RegeneratorPlacement/RegeneratorPlacement.h \
    include/RWA/RegeneratorPlacement/NX_RegeneratorPlacement.h \
    include/RWA/RegeneratorPlacement/NodalDegreeFirst.h \
    include/Devices/Amplifiers/InLineAmplifier.h \
    include/RWA/RegeneratorAssignment/RegeneratorAssignment.h \
    include/RWA/RegeneratorAssignment/FirstLongestReach.h \
    include/RWA/TransparentSegment.h \
    include/GeneralClasses/ModulationScheme.h \
    include/SimulationTypes/SimulationType.h \
    include/SimulationTypes/NetworkSimulation.h \
    include/RWA/Routing/LengthOccupationRoutingAvailability.h \
    include/SimulationTypes/Simulation_NetworkLoad.h

LIBS += -lboost_system -lboost_program_options

OTHER_FILES += README.md \
               .astylerc


INCLUDEPATH += include/
