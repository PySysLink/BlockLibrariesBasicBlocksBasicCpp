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

            using ConfigMap = std::map<std::string, PySysLinkBase::ConfigurationValue>;
            using BlockCreator = std::function<
            std::unique_ptr<PySysLinkBase::ISimulationBlock>(
                  const ConfigMap&,
                  std::shared_ptr<PySysLinkBase::IBlockEventsHandler>
            )
            >;

            template <typename T>
            std::map<std::string, BlockCreator> CreateBlockMap()      
            {
                  static const std::map<std::string, BlockCreator> map = {
                        { "BasicBlocks/Constant", [](const ConfigMap& cfg, auto h) { return std::make_unique<Constant<T>>(cfg, h); } },
                        { "BasicBlocks/Adder", [](const ConfigMap& cfg, auto h) { return std::make_unique<Adder<T>>(cfg, h); } },
                        { "BasicBlocks/Display", [](const ConfigMap& cfg, auto h) { return std::make_unique<Display<T>>(cfg, h); } },
                        { "BasicBlocks/Accumulator", [](const ConfigMap& cfg, auto h) { return std::make_unique<Accumulator<T>>(cfg, h); } },
                        { "BasicBlocks/ContinuousToDiscrete", [](const ConfigMap& cfg, auto h) { return std::make_unique<ContinuousToDiscrete<T>>(cfg, h); } },
                        { "BasicBlocks/Gain", [](const ConfigMap& cfg, auto h) { return std::make_unique<Gain<T>>(cfg, h); } },
                        { "BasicBlocks/Integrator", [](const ConfigMap& cfg, auto h) {
                              if constexpr (std::is_same_v<T, double>)
                              return std::make_unique<Integrator<double>>(cfg, h);
                              else
                              throw std::invalid_argument("Integrator only supports double.");
                        }}
                  };

                  return map;
            }

            template <typename T>
            std::unique_ptr<PySysLinkBase::ISimulationBlock> CreateBlockTyped(const std::string& blockClass, const ConfigMap& cfg, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> handler)
            {
                  const auto& map = GetBlockCreationMap<T>();

                  auto it = map.find(blockClass);
                  if (it == map.end())
                  {
                        throw std::out_of_range("Block type not found: " + blockClass);
                  }

                  return it->second(cfg, handler);
            }

      public:
            std::vector<std::string> BasicCppFactory::GetSupportedBlockClasses() const
            {
                  const auto& map = GetBlockCreationMap<double>(); // representative type

                  std::vector<std::string> keys;
                  keys.reserve(map.size());

                  for (const auto& [key, _] : map)
                  {
                        keys.push_back(key);
                  }

                  return keys;
            }
            
            std::unique_ptr<PySysLinkBase::ISimulationBlock> BasicCppFactory::CreateBlock(std::string blockClass, std::map<std::string, PySysLinkBase::ConfigurationValue> blockConfiguration, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> blockEventsHandler)
            {
                  auto it = blockConfiguration.find("DataType");
                  if (it == blockConfiguration.end())
                  {
                        throw std::invalid_argument("Missing 'DataType' in block configuration.");
                  }

                  const std::string dataType = it->second.AsString(); // adapt if needed

                  if (dataType == "int")
                  {
                        return CreateBlockTyped<int>(blockClass, blockConfiguration, blockEventsHandler);
                  }
                  else if (dataType == "double")
                  {
                        return CreateBlockTyped<double>(blockClass, blockConfiguration, blockEventsHandler);
                  }
                  else if (dataType == "complex_double")
                  {
                        return CreateBlockTyped<std::complex<double>>(blockClass, blockConfiguration, blockEventsHandler);
                  }
                  else if (dataType == "bool")
                  {
                        return CreateBlockTyped<bool>(blockClass, blockConfiguration, blockEventsHandler);
                  }
                  else if (dataType == "string")
                  {
                        return CreateBlockTyped<std::string>(blockClass, blockConfiguration, blockEventsHandler);
                  }
                  else
                  {
                        throw std::invalid_argument("Unsupported DataType: " + dataType);
                  }
            }
      };
} // BlockLibraries::BasicBlocksBasicCpp 


#endif /* SRC_BASIC_CPP_FACTORY */
