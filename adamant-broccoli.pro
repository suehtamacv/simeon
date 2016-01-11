TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle qt

QMAKE_CXXFLAGS += -std=c++11 -fopenmp
QMAKE_LFLAGS += -std=c++11 -fopenmp
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3

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
    src/RWA/RoutingAlgorithms/RoutingAlgorithm.cpp \
    src/RWA/WavelengthAssignmentAlgorithms/WavelengthAssignmentAlgorithm.cpp \
    src/RWA/Route.cpp \
    src/RWA/RoutingAlgorithms/DijkstraRoutingAlgorithm.cpp \
    src/RWA/RoutingAlgorithms/StaticRouting/StaticRoutingAlgorithm.cpp \
    src/RWA/RoutingAlgorithms/StaticRouting/MinimumHops.cpp \
    src/RWA/RoutingAlgorithms/StaticRouting/ShortestPath.cpp \
    src/RWA/WavelengthAssignmentAlgorithms/FirstFit.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/NodalDegreeFirst.cpp \
    src/Devices/Amplifiers/InLineAmplifier.cpp \
    src/RWA/RegeneratorAssignmentAlgorithms/FirstLongestReach.cpp \
    src/RWA/TransparentSegment.cpp \
    src/GeneralClasses/ModulationScheme.cpp \
    src/Devices/Device.cpp \
    src/SimulationTypes/SimulationType.cpp \
    src/SimulationTypes/NetworkSimulation.cpp \
    src/RWA/RoutingAlgorithms/LengthOccupationRoutingAvailability.cpp \
    src/SimulationTypes/Simulation_NetworkLoad.cpp \
    src/RWA/RoutingAlgorithms/LengthOccupationRoutingContiguity.cpp \
    src/RWA/RegeneratorAssignmentAlgorithms/FirstNarrowestSpectrum.cpp \
    src/RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/MostUsed.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/MostSimultaneouslyUsed.cpp \
    src/SimulationTypes/Simulation_PSROptimization.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Availability.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Distance.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/PowerSeriesRouting.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Occupability.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Contiguity.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Bitrate.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_ModulationScheme.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_NormalizedContiguity.cpp \
    src/SimulationTypes/Simulation_StatisticalTrend.cpp \
    src/GeneralPurposeAlgorithms/NSGA-II/NSGA2.cpp \
    src/GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.cpp \
    src/GeneralPurposeAlgorithms/NSGA-II/NSGA2_Parameter.cpp \
    src/GeneralPurposeAlgorithms/NSGA-II/NSGA2_Generation.cpp \
    src/Devices/Regenerator.cpp \
    src/SimulationTypes/Simulation_NSGA2_RegnPlac.cpp \
    src/SimulationTypes/Simulation_TransparencyAnalysis.cpp \
    src/SimulationTypes/Simulation_RegeneratorNumber.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Noise.cpp


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
    include/RWA/RoutingAlgorithms/RoutingAlgorithm.h \
    include/RWA/WavelengthAssignmentAlgorithms/WavelengthAssignmentAlgorithm.h \
    include/RWA/Route.h \
    include/RWA/RoutingAlgorithms/DijkstraRoutingAlgorithm.h \
    include/RWA/RoutingAlgorithms/StaticRouting/StaticRoutingAlgorithm.h \
    include/RWA/RoutingAlgorithms/StaticRouting/MinimumHops.h \
    include/RWA/RoutingAlgorithms/StaticRouting/ShortestPath.h \
    include/RWA/WavelengthAssignmentAlgorithms/FirstFit.h \
    include/RWA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.h \
    include/RWA/RegeneratorPlacementAlgorithms/NodalDegreeFirst.h \
    include/Devices/Amplifiers/InLineAmplifier.h \
    include/RWA/RegeneratorAssignmentAlgorithms/FirstLongestReach.h \
    include/RWA/TransparentSegment.h \
    include/GeneralClasses/ModulationScheme.h \
    include/SimulationTypes/SimulationType.h \
    include/SimulationTypes/NetworkSimulation.h \
    include/RWA/RoutingAlgorithms/LengthOccupationRoutingAvailability.h \
    include/SimulationTypes/Simulation_NetworkLoad.h \
    include/RWA/RoutingAlgorithms/LengthOccupationRoutingContiguity.h \
    include/RWA/RegeneratorAssignmentAlgorithms/FirstNarrowestSpectrum.h \
    include/Calls.h \
    include/Devices.h \
    include/Devices/Amplifiers.h \
    include/GeneralClasses.h \
    include/Structure.h \
    include/RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h \
    include/RWA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h \
    include/RWA/RegeneratorAssignmentAlgorithms.h \
    include/RWA/RegeneratorPlacementAlgorithms.h \
    include/RWA/RoutingAlgorithms.h \
    include/RWA/WavelengthAssignmentAlgorithms.h \
    include/RWA.h \
    include/SimulationTypes.h \
    include/RWA/RegeneratorPlacementAlgorithms/MostUsed.h \
    include/RWA/RegeneratorPlacementAlgorithms/MostSimultaneouslyUsed.h \
    include/GeneralPurposeAlgorithms/PSO/ParticleSwarmOptimization.h \
    include/GeneralPurposeAlgorithms/PSO/PSO_Particle.h \
    include/SimulationTypes/Simulation_PSROptimization.h \
    include/GeneralClasses/RandomGenerator.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Availability.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Distance.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/PowerSeriesRouting.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Occupability.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Contiguity.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Bitrate.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_ModulationScheme.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_NormalizedContiguity.h \
    include/SimulationTypes/Simulation_StatisticalTrend.h \
    include/GeneralPurposeAlgorithms/PSO.h \
    include/GeneralPurposeAlgorithms/NSGA-II/NSGA2.h \
    include/GeneralPurposeAlgorithms/NSGA-2.h \
    include/GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.h \
    include/GeneralPurposeAlgorithms/NSGA-II/NSGA2_Parameter.h \
    include/GeneralPurposeAlgorithms/NSGA-II/NSGA2_Generation.h \
    include/Devices/Regenerator.h \
    include/SimulationTypes/Simulation_NSGA2_RegnPlac.h \
    include/SimulationTypes/Simulation_TransparencyAnalysis.h \
    include/SimulationTypes/Simulation_RegeneratorNumber.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Noise.h

LIBS += -lboost_system -lboost_program_options -larmadillo

INSTALL_TOPOLOGIES.path = $$OUT_PWD/data/topologies
INSTALL_TOPOLOGIES.files = data/topologies/*

INSTALLS += INSTALL_TOPOLOGIES

OTHER_FILES += README.md \
               .astylerc \
               .travis.yml


INCLUDEPATH += include/
