#include <BlockTypes/BasicCpp/IBasicCppBlockFactory.h>
#include "BasicCppFactory.h"


extern "C" void RegisterBasicCppFactoriesDouble(std::map<std::string, std::unique_ptr<BlockTypes::BasicCpp::IBasicCppBlockFactory<double>>>& registry) {
    registry["BasicBlocksBasicCpp"] = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::BasicCppFactory<double>>();
}

extern "C" void RegisterBasicCppFactoriesComplex(std::map<std::string, std::unique_ptr<BlockTypes::BasicCpp::IBasicCppBlockFactory<std::complex<double>>>>& registry) {
    registry["BasicBlocksBasicCpp"] = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::BasicCppFactory<std::complex<double>>>();
}
