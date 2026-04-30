#ifndef SRC_BASIC_CPP_FACTORY
#define SRC_BASIC_CPP_FACTORY

#include <memory>
#include <functional>
#include <complex>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <PySysLinkBase/ISimulationBlock.h>
#include <PySysLinkBase/ConfigurationValue.h>
#include <BlockTypeSupports/BasicCppSupport/IBasicCppBlockFactory.h>

#include "Constant.h"
#include "Adder.h"
#include "Display.h"
#include "Accumulator.h"
#include "ContinuousToDiscrete.h"
#include "Gain.h"
#include "Integrator.h" 

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
            static const std::map<std::string, BlockCreator>& CreateBlockMap()
            {
                  static const std::map<std::string, BlockCreator> map = {
                        { "BasicBlocks/Constant", [](const ConfigMap& cfg, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> h) { return std::unique_ptr<PySysLinkBase::ISimulationBlock>(std::make_unique<Constant<T>>(cfg, h)); } },
                        { "BasicBlocks/Adder", [](const ConfigMap& cfg, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> h) { return std::unique_ptr<PySysLinkBase::ISimulationBlock>(std::make_unique<Adder<T>>(cfg, h)); } },
                        { "BasicBlocks/Display", [](const ConfigMap& cfg, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> h) { return std::unique_ptr<PySysLinkBase::ISimulationBlock>(std::make_unique<Display<T>>(cfg, h)); } },
                        { "BasicBlocks/Accumulator", [](const ConfigMap& cfg, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> h) { return std::unique_ptr<PySysLinkBase::ISimulationBlock>(std::make_unique<Accumulator<T>>(cfg, h)); } },
                        { "BasicBlocks/ContinuousToDiscrete", [](const ConfigMap& cfg, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> h) { return std::unique_ptr<PySysLinkBase::ISimulationBlock>(std::make_unique<ContinuousToDiscrete<T>>(cfg, h)); } },
                        { "BasicBlocks/Gain", [](const ConfigMap& cfg, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> h) { return std::unique_ptr<PySysLinkBase::ISimulationBlock>(std::make_unique<Gain<T>>(cfg, h)); } },
                        { "BasicBlocks/Integrator", [](const ConfigMap& cfg, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> h) {
                              if constexpr (std::is_same_v<T, double>)
                              return std::unique_ptr<PySysLinkBase::ISimulationBlock>(std::make_unique<Integrator<double>>(cfg, h));
                              else
                              throw std::invalid_argument("Integrator only supports double.");
                        }}
                  };

                  return map;
            }

            template <typename T>
            std::unique_ptr<PySysLinkBase::ISimulationBlock> CreateBlockTyped(const std::string& blockClass, const ConfigMap& cfg, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> handler)
            {
                  const auto& map = CreateBlockMap<T>();

                  auto it = map.find(blockClass);
                  if (it == map.end())
                  {
                        throw std::out_of_range("Block type not found: " + blockClass);
                  }

                  return it->second(cfg, handler);
            }

      public:
            std::vector<std::string> GetSupportedBlockClasses() const override
            {
                  const auto& map = CreateBlockMap<double>(); // representative type

                  std::vector<std::string> keys;
                  keys.reserve(map.size());

                  for (const auto& [key, _] : map)
                  {
                        keys.push_back(key);
                  }

                  return keys;
            }

            std::unique_ptr<PySysLinkBase::ISimulationBlock> CreateBlock(std::string blockClass, std::map<std::string, PySysLinkBase::ConfigurationValue> blockConfiguration, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> blockEventsHandler) override
            {
                  auto it = blockConfiguration.find("DataType");
                  if (it == blockConfiguration.end())
                  {
                        throw std::invalid_argument("Missing 'DataType' in block configuration.");
                  }

                  const auto* str = std::get_if<std::string>(&it->second);
                  if (!str)
                  {
                        throw std::invalid_argument("DataType must be a string.");
                  }

                  const std::string& dataType = *str;

                  if (dataType == "int")
                  {
                        return CreateBlockTyped<int>(blockClass, blockConfiguration, blockEventsHandler);
                  }
                  else if (dataType == "double")
                  {
                        return CreateBlockTyped<double>(blockClass, blockConfiguration, blockEventsHandler);
                  }
                  // else if (dataType == "complex_double")
                  // {
                  //       return CreateBlockTyped<std::complex<double>>(blockClass, blockConfiguration, blockEventsHandler);
                  // }
                  // else if (dataType == "bool")
                  // {
                  //       return CreateBlockTyped<bool>(blockClass, blockConfiguration, blockEventsHandler);
                  // }
                  // else if (dataType == "string")
                  // {
                  //       return CreateBlockTyped<std::string>(blockClass, blockConfiguration, blockEventsHandler);
                  // }
                  else
                  {
                        throw std::invalid_argument("Unsupported DataType: " + dataType);
                  }
            }
      };
} // namespace BlockLibraries::BasicBlocksBasicCpp

#endif /* SRC_BASIC_CPP_FACTORY */
