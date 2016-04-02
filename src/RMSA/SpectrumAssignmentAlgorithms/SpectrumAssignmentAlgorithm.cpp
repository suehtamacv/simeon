#include <RMSA/SpectrumAssignmentAlgorithms/SpectrumAssignmentAlgorithm.h>
#include <RMSA/SpectrumAssignmentAlgorithms.h>
#include <boost/assign.hpp>
#include <iostream>
#include <fstream>

using namespace SA;

SpectrumAssignmentAlgorithm::SpecAssignAlgNameBimap
SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithmNames =
    boost::assign::list_of<SpectrumAssignmentAlgorithm::SpecAssignAlgNameBimap::relation>
#define X(a,b,c,d) (a,b)
    SPECTRUMASSIGNMENT_ALGORITHM
#undef X
    ;

SpectrumAssignmentAlgorithm::SpecAssignAlgNicknameBimap
SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithmNicknames =
    boost::assign::list_of<SpectrumAssignmentAlgorithm::SpecAssignAlgNicknameBimap::relation>
#define X(a,b,c,d) (a,c)
    SPECTRUMASSIGNMENT_ALGORITHM
#undef X
    ;

SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithm(
    std::shared_ptr<Topology> T,
    SpectrumAssignmentAlgorithms WavAssAlgType) :
    SpecAssAlgType(WavAssAlgType), T(T)
{

}

SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithms
SpectrumAssignmentAlgorithm::define_SpectrumAssignmentAlgorithm()
{
    std::cout << std::endl << "-> Choose a wavelength assignment algorithm."
              << std::endl;

    do
        {
        for (auto &wavasgn : SpectrumAssignmentAlgorithmNames.left)
            {
            std::cout << "(" << wavasgn.first << ")\t" << wavasgn.second << std::endl;
            }

        int WavAssgn_Alg;
        std::cin >> WavAssgn_Alg;

        if (std::cin.fail() || SpectrumAssignmentAlgorithmNames.left.count
                ((SpectrumAssignmentAlgorithms) WavAssgn_Alg) == 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid wavelength assignment algorithm." << std::endl;
            std::cout << std::endl << "-> Choose a wavelength assignment algorithm."
                      << std::endl;
            }
        else
            {
            return (SpectrumAssignmentAlgorithms) WavAssgn_Alg;
            }
        }
    while (1);

    return (SpectrumAssignmentAlgorithms) - 1;
}

std::shared_ptr<SpectrumAssignmentAlgorithm>
SpectrumAssignmentAlgorithm::create_SpectrumAssignmentAlgorithm(
    SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithms Algorithm,
    std::shared_ptr<Topology> T)
{

    std::shared_ptr<SpectrumAssignmentAlgorithm> WA_Alg;

    switch (Algorithm)
        {
#define X(a,b,c,d) case a: WA_Alg = std::make_shared<d>(T); break;
            SPECTRUMASSIGNMENT_ALGORITHM
#undef X
        }

    WA_Alg->load();
    return WA_Alg;
}

void SpectrumAssignmentAlgorithm::save(std::string SimConfigFileName)
{
    std::ofstream SimConfigFile(SimConfigFileName,
                                std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << "  WavelengthAssignmentAlgorithm = " <<
                  SpectrumAssignmentAlgorithmNicknames.left.at(SpecAssAlgType)
                  << std::endl;
}
