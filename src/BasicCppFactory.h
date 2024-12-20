#ifndef SRC_BASIC_CPP_FACTORY
#define SRC_BASIC_CPP_FACTORY

#include <memory>
#include <BlockTypes/BasicCpp/SimulationBlock.h>
#include <map>
#include <BlockTypes/BasicCpp/ConfigurationValue.h>
#include <BlockTypes/BasicCpp/IBasicCppBlockFactory.h>
#include <string>
#include <vector>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    class BasicCppFactory : public BlockTypes::BasicCpp::IBasicCppBlockFactory {
      public:
         std::vector<std::string> GetSupportedBlockClasses() const;
         std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock> CreateBlock(std::string blockClass, std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> blockConfiguration, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler);
   };
} // BlockLibraries::BasicBlocksBasicCpp 


#endif /* SRC_BASIC_CPP_FACTORY */
