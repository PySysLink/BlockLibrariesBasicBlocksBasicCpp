#include <BlockTypes/BasicCpp/IBasicCppBlockFactory.h>
#include "BasicCppFactory.h"


extern "C" void RegisterBasicCppFactories(std::map<std::string, std::unique_ptr<BlockTypes::BasicCpp::IBasicCppBlockFactory>>& registry) {
    registry["BasicBlocksBasicCpp"] = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::BasicCppFactory>();
}
