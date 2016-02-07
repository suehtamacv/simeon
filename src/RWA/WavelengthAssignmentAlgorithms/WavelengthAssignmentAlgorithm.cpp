#include <RWA/WavelengthAssignmentAlgorithms/WavelengthAssignmentAlgorithm.h>
#include <RWA/WavelengthAssignmentAlgorithms.h>
#include <boost/assign.hpp>
#include <iostream>
#include <fstream>

WavelengthAssignmentAlgorithm::WavAssignAlgNameBimap
WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithmNames =
    boost::assign::list_of<WavelengthAssignmentAlgorithm::WavAssignAlgNameBimap::relation>
#define X(a,b,c,d) (a,b)
    WAVELENGTHASSIGNMENT_ALGORITHM
#undef X
    ;

WavelengthAssignmentAlgorithm::WavAssignAlgNicknameBimap
WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithmNicknames =
    boost::assign::list_of<WavelengthAssignmentAlgorithm::WavAssignAlgNicknameBimap::relation>
#define X(a,b,c,d) (a,c)
    WAVELENGTHASSIGNMENT_ALGORITHM
#undef X
    ;

WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithm(
    std::shared_ptr<Topology> T,
    WavelengthAssignmentAlgorithms WavAssAlgType) :
    WavAssAlgType(WavAssAlgType), T(T)
{

}

WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithms
WavelengthAssignmentAlgorithm::define_WavelengthAssignmentAlgorithm()
{
    std::cout << std::endl << "-> Choose a wavelength assignment algorithm."
              << std::endl;

    do
        {
        for (auto &wavasgn : WavelengthAssignmentAlgorithmNames.left)
            {
            std::cout << "(" << wavasgn.first << ")\t" << wavasgn.second << std::endl;
            }

        int WavAssgn_Alg;
        std::cin >> WavAssgn_Alg;

        if (std::cin.fail() || WavelengthAssignmentAlgorithmNames.left.count
                ((WavelengthAssignmentAlgorithms) WavAssgn_Alg) == 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid wavelength assignment algorithm." << std::endl;
            std::cout << std::endl << "-> Choose a wavelength assignment algorithm."
                      << std::endl;
            }
        else
            {
            return (WavelengthAssignmentAlgorithms) WavAssgn_Alg;
            }
        }
    while (1);

    return (WavelengthAssignmentAlgorithms) - 1;
}

std::shared_ptr<WavelengthAssignmentAlgorithm>
WavelengthAssignmentAlgorithm::create_WavelengthAssignmentAlgorithm(
    WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithms Algorithm,
    std::shared_ptr<Topology> T)
{

    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg;

    switch (Algorithm)
        {
#define X(a,b,c,d) case a: WA_Alg = std::make_shared<d>(T); break;
            WAVELENGTHASSIGNMENT_ALGORITHM
#undef X
        }

    WA_Alg->load();
    return WA_Alg;
}

void WavelengthAssignmentAlgorithm::save(std::string SimConfigFileName)
{
    std::ofstream SimConfigFile(SimConfigFileName,
                                std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << "  WavelengthAssignmentAlgorithm = " <<
                  WavelengthAssignmentAlgorithmNicknames.left.at(WavAssAlgType)
                  << std::endl;
}
