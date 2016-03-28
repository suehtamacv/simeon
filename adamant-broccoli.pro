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
    src/Calls/Call.cpp \
    src/Calls/CallGenerator.cpp \
    src/Calls/Event.cpp \
    src/Devices/Amplifiers/Amplifier.cpp \
    src/Devices/Amplifiers/BoosterAmplifier.cpp \
    src/Devices/Amplifiers/EDFA.cpp \
    src/Devices/Amplifiers/InLineAmplifier.cpp \
    src/Devices/Amplifiers/PreAmplifier.cpp \
    src/Devices/Device.cpp \
    src/Devices/Fiber.cpp \
    src/Devices/Regenerator.cpp \
    src/Devices/Splitter.cpp \
    src/Devices/SSS.cpp \
    src/GeneralClasses/Gain.cpp \
    src/GeneralClasses/ModulationScheme.cpp \
    src/GeneralClasses/Power.cpp \
    src/GeneralClasses/Signal.cpp \
    src/GeneralClasses/SpectralDensity.cpp \
    src/GeneralClasses/TransferFunctions/GaussianTransferFunction.cpp \
    src/GeneralClasses/TransferFunctions/TransferFunction.cpp \
    src/GeneralClasses/TransmissionBitrate.cpp \
    src/GeneralPurposeAlgorithms/IntegrationMethods/IntegrationMethod.cpp \
    src/GeneralPurposeAlgorithms/IntegrationMethods/SimpsonsRule.cpp \
    src/GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.cpp \
    src/GeneralPurposeAlgorithms/NSGA-II/NSGA2.cpp \
    src/GeneralPurposeAlgorithms/NSGA-II/NSGA2_Generation.cpp \
    src/GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.cpp \
    src/GeneralPurposeAlgorithms/NSGA-II/NSGA2_Parameter.cpp \
    src/Structure/Link.cpp \
    src/Structure/Node.cpp \
    src/Structure/Slot.cpp \
    src/Structure/Topology.cpp \
    src/RWA/RegeneratorAssignmentAlgorithms/FirstLongestReach.cpp \
    src/RWA/RegeneratorAssignmentAlgorithms/FirstNarrowestSpectrum.cpp \
    src/RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/DistanceAdaptative.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/Empty_RegeneratorPlacementAlgorithm.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/MostSimultaneouslyUsed.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/MostUsed.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/NodalDegreeFirst.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/NX_MostSimultaneouslyUsed.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SignalQualityPrediction.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SignalQualityPrediction_Variants.cpp \
    src/RWA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SQP_NetworkSimulation.cpp \
    src/RWA/Route.cpp \
    src/RWA/RoutingAlgorithms/DijkstraRoutingAlgorithm.cpp \
    src/RWA/RoutingAlgorithms/LengthOccupationRoutingAvailability.cpp \
    src/RWA/RoutingAlgorithms/LengthOccupationRoutingContiguity.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants/AdaptativeWeighingRouting.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants/LocalPowerSeriesRouting.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants/MatricialPowerSeriesRouting.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants/TensorialPowerSeriesRouting.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Availability.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Bitrate.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Contiguity.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Distance.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_HopDistance.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_LinkLength.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_ModulationScheme.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Noise.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_NormalizedContiguity.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_NormalizedNoise.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Occupability.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_OrigDestIndex.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Slots.cpp \
    src/RWA/RoutingAlgorithms/PowerSeriesRouting/PowerSeriesRouting.cpp \
    src/RWA/RoutingAlgorithms/RoutingAlgorithm.cpp \
    src/RWA/RoutingAlgorithms/StaticRouting/MinimumHops.cpp \
    src/RWA/RoutingAlgorithms/StaticRouting/ShortestPath.cpp \
    src/RWA/RoutingAlgorithms/StaticRouting/StaticRoutingAlgorithm.cpp \
    src/RWA/RoutingWavelengthAssignment.cpp \
    src/RWA/TransparentSegment.cpp \
    src/RWA/WavelengthAssignmentAlgorithms/BestFit.cpp \
    src/RWA/WavelengthAssignmentAlgorithms/ExactFit.cpp \
    src/RWA/WavelengthAssignmentAlgorithms/FirstFit.cpp \
    src/RWA/WavelengthAssignmentAlgorithms/LeastUsed.cpp \
    src/RWA/WavelengthAssignmentAlgorithms/MostUsedSA.cpp \
    src/RWA/WavelengthAssignmentAlgorithms/RandomFit.cpp \
    src/RWA/WavelengthAssignmentAlgorithms/WavelengthAssignmentAlgorithm.cpp \
    src/SimulationTypes/NetworkSimulation.cpp \
    src/SimulationTypes/SimulationType.cpp \
    src/SimulationTypes/Simulation_NetworkLoad.cpp \
    src/SimulationTypes/Simulation_NSGA2_RegnPlac/Simulation_NSGA2_RegnPlac.cpp \
    src/SimulationTypes/Simulation_PSROptimization.cpp \
    src/SimulationTypes/Simulation_RegeneratorNumber.cpp \
    src/SimulationTypes/Simulation_StatisticalTrend.cpp \
    src/SimulationTypes/Simulation_TransparencyAnalysis.cpp \
    src/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameter_CapEx.cpp \
    src/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameter_OpEx.cpp \
    src/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameter_BlockingProbability.cpp \
    src/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameter_NumberOfRegenerators.cpp

HEADERS += \
    include/Calls.h \
    include/Calls/Call.h \
    include/Calls/CallGenerator.h \
    include/Calls/Event.h \
    include/Devices.h \
    include/Devices/Amplifiers.h \
    include/Devices/Amplifiers/Amplifier.h \
    include/Devices/Amplifiers/BoosterAmplifier.h \
    include/Devices/Amplifiers/EDFA.h \
    include/Devices/Amplifiers/InLineAmplifier.h \
    include/Devices/Amplifiers/PreAmplifier.h \
    include/Devices/Device.h \
    include/Devices/Fiber.h \
    include/Devices/Regenerator.h \
    include/Devices/SSS.h \
    include/Devices/Splitter.h \
    include/GeneralClasses.h \
    include/GeneralClasses/Gain.h \
    include/GeneralClasses/ModulationScheme.h \
    include/GeneralClasses/PhysicalConstants.h \
    include/GeneralClasses/Power.h \
    include/GeneralClasses/RandomGenerator.h \
    include/GeneralClasses/Signal.h \
    include/GeneralClasses/SpectralDensity.h \
    include/GeneralClasses/TransferFunctions/GaussianTransferFunction.h \
    include/GeneralClasses/TransferFunctions/TransferFunction.h \
    include/GeneralClasses/TransmissionBitrate.h \
    include/GeneralPurposeAlgorithms/IntegrationMethods/IntegrationMethod.h \
    include/GeneralPurposeAlgorithms/IntegrationMethods/SimpsonsRule.h \
    include/GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h \
    include/GeneralPurposeAlgorithms/NSGA-2.h \
    include/GeneralPurposeAlgorithms/NSGA-II/NSGA2.h \
    include/GeneralPurposeAlgorithms/NSGA-II/NSGA2_Generation.h \
    include/GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.h \
    include/GeneralPurposeAlgorithms/NSGA-II/NSGA2_Parameter.h \
    include/GeneralPurposeAlgorithms/PSO.h \
    include/GeneralPurposeAlgorithms/PSO/ParticleSwarmOptimization.h \
    include/GeneralPurposeAlgorithms/PSO/PSO_Particle.h \
    include/Structure.h \
    include/Structure/Link.h \
    include/Structure/Node.h \
    include/Structure/Slot.h \
    include/Structure/Topology.h \
    include/RWA.h \
    include/RWA/RegeneratorAssignmentAlgorithms.h \
    include/RWA/RegeneratorAssignmentAlgorithms/FirstLongestReach.h \
    include/RWA/RegeneratorAssignmentAlgorithms/FirstNarrowestSpectrum.h \
    include/RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h \
    include/RWA/RegeneratorPlacementAlgorithms.h \
    include/RWA/RegeneratorPlacementAlgorithms/DistanceAdaptative.h \
    include/RWA/RegeneratorPlacementAlgorithms/Empty_RegeneratorPlacementAlgorithm.h \
    include/RWA/RegeneratorPlacementAlgorithms/MostSimultaneouslyUsed.h \
    include/RWA/RegeneratorPlacementAlgorithms/MostUsed.h \
    include/RWA/RegeneratorPlacementAlgorithms/NodalDegreeFirst.h \
    include/RWA/RegeneratorPlacementAlgorithms/NX_MostSimultaneouslyUsed.h \
    include/RWA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.h \
    include/RWA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h \
    include/RWA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SignalQualityPrediction.h \
    include/RWA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SignalQualityPrediction_Variants.h \
    include/RWA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SQP_NetworkSimulation.h \
    include/RWA/Route.h \
    include/RWA/RoutingAlgorithms.h \
    include/RWA/RoutingAlgorithms/DijkstraRoutingAlgorithm.h \
    include/RWA/RoutingAlgorithms/LengthOccupationRoutingAvailability.h \
    include/RWA/RoutingAlgorithms/LengthOccupationRoutingContiguity.h \
    include/RWA/RoutingAlgorithms/RoutingAlgorithm.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants/AdaptativeWeighingRouting.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants/LocalPowerSeriesRouting.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants/MatricialPowerSeriesRouting.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants/TensorialPowerSeriesRouting.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Availability.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Bitrate.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Contiguity.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Distance.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_HopDistance.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_LinkLength.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_ModulationScheme.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Noise.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_NormalizedContiguity.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_NormalizedNoise.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Occupability.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_OrigDestIndex.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Slots.h \
    include/RWA/RoutingAlgorithms/PowerSeriesRouting/PowerSeriesRouting.h \
    include/RWA/RoutingAlgorithms/StaticRouting/MinimumHops.h \
    include/RWA/RoutingAlgorithms/StaticRouting/ShortestPath.h \
    include/RWA/RoutingAlgorithms/StaticRouting/StaticRoutingAlgorithm.h \
    include/RWA/RoutingWavelengthAssignment.h \
    include/RWA/TransparentSegment.h \
    include/RWA/WavelengthAssignmentAlgorithms.h \
    include/RWA/WavelengthAssignmentAlgorithms/BestFit.h \
    include/RWA/WavelengthAssignmentAlgorithms/ExactFit.h \
    include/RWA/WavelengthAssignmentAlgorithms/FirstFit.h \
    include/RWA/WavelengthAssignmentAlgorithms/LeastUsed.h \
    include/RWA/WavelengthAssignmentAlgorithms/MostUsedSA.h \
    include/RWA/WavelengthAssignmentAlgorithms/RandomFit.h \
    include/RWA/WavelengthAssignmentAlgorithms/WavelengthAssignmentAlgorithm.h \
    include/SimulationTypes.h \
    include/SimulationTypes/NetworkSimulation.h \
    include/SimulationTypes/SimulationType.h \
    include/SimulationTypes/Simulation_NetworkLoad.h \
    include/SimulationTypes/Simulation_NSGA2_RegnPlac/Simulation_NSGA2_RegnPlac.h \
    include/SimulationTypes/Simulation_PSROptimization.h \
    include/SimulationTypes/Simulation_RegeneratorNumber.h \
    include/SimulationTypes/Simulation_StatisticalTrend.h \
    include/SimulationTypes/Simulation_TransparencyAnalysis.h \
    include/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameter_CapEx.h \
    include/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameter_OpEx.h \
    include/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameter_BlockingProbability.h \
    include/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameters.h \
    include/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameter_NumberOfRegenerators.h

LIBS += -lboost_system -lboost_program_options -larmadillo

INSTALL_TOPOLOGIES.path = $$OUT_PWD/data/topologies
INSTALL_TOPOLOGIES.files = data/topologies/*

INSTALLS += INSTALL_TOPOLOGIES

OTHER_FILES += README.md \
               .astylerc \
               .travis.yml


INCLUDEPATH += include/
