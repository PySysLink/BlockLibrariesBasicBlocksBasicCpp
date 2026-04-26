#ifndef SRC_BASIC_CPP_FACTORY
#define SRC_BASIC_CPP_FACTORY

#include <memory>
#include <PySysLinkBase/ISimulationBlock.h>
#include <map>
#include <PySysLinkBase/ConfigurationValue.h>
#include <BlockTypeSupports/BasicCppSupport/IBasicCppBlockFactory.h>
#include <string>
#include <vector>

namespace BlockLibraries::BasicBlocksBasicCpp
{
      class BasicCppFactory : public BlockTypeSupports::BasicCppSupport::IBasicCppBlockFactory {
         protected:
         template <typename T>
         std::unique_ptr<PySysLinkBase::ISimulationBlock> CreateBlockTyped(std::string blockClass, std::map<std::string, PySysLinkBase::ConfigurationValue> blockConfiguration, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> blockEventsHandler);
         public:
         std::vector<std::string> GetSupportedBlockClasses() const;
         std::unique_ptr<PySysLinkBase::ISimulationBlock> CreateBlock(std::string blockClass, std::map<std::string, PySysLinkBase::ConfigurationValue> blockConfiguration, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> blockEventsHandler);
      };
} // BlockLibraries::BasicBlocksBasicCpp 


#endif /* SRC_BASIC_CPP_FACTORY */
