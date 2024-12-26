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
   template <typename T>
      class BasicCppFactory : public BlockTypes::BasicCpp::IBasicCppBlockFactory<T> {
         public:
         std::vector<std::string> GetSupportedBlockClasses() const;
         std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock<T>> CreateBlock(std::string blockClass, std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> blockConfiguration, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler);
      };

   extern template class BasicCppFactory<double>;
   extern template class BasicCppFactory<std::complex<double>>;
} // BlockLibraries::BasicBlocksBasicCpp 


#endif /* SRC_BASIC_CPP_FACTORY */
