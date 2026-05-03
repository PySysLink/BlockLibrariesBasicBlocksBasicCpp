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

           

            template <typename T>
            std::unique_ptr<PySysLinkBase::ISimulationBlock> CreateBlockTyped(const std::string& blockClass, const ConfigMap& cfg, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> handler)
            {
                  if (blockClass == "BasicBlocks/Constant")
                        return std::make_unique<Constant<T>>(cfg, handler);

                  if (blockClass == "BasicBlocks/Adder")
                        return std::make_unique<Adder<T>>(cfg, handler);

                  if (blockClass == "BasicBlocks/Display")
                        return std::make_unique<Display<T>>(cfg, handler);

                  if (blockClass == "BasicBlocks/Accumulator")
                        return std::make_unique<Accumulator<T>>(cfg, handler);

                  if (blockClass == "BasicBlocks/ContinuousToDiscrete")
                        return std::make_unique<ContinuousToDiscrete<T>>(cfg, handler);

                  if (blockClass == "BasicBlocks/Gain")
                        if constexpr (!std::is_same_v<T, double>) {
                              return std::make_unique<Gain<double>>(cfg, handler);
                        }
                        else if constexpr (std::is_same_v<T, int>) {
                              return std::make_unique<Gain<int>>(cfg, handler);
                        } else if constexpr (std::is_same_v<T, std::complex<double>>) {
                              return std::make_unique<Gain<std::complex<double>>>(cfg, handler);
                        } else {
                              throw std::invalid_argument("Gain does not support bool.");
                        }

                  if (blockClass == "BasicBlocks/Integrator")
                  {
                        if constexpr (!std::is_same_v<T, double>)
                        {
                              throw std::invalid_argument("Integrator only supports double.");
                        }

                        return std::make_unique<Integrator<double>>(cfg, handler);
                  }

                  throw std::out_of_range("Block type not found: " + blockClass);
            }

      public:
            std::vector<std::string> GetSupportedBlockClasses() const override
            {
                  return {
                        "BasicBlocks/Constant",
                        "BasicBlocks/Adder",
                        "BasicBlocks/Display",
                        "BasicBlocks/Accumulator",
                        "BasicBlocks/ContinuousToDiscrete",
                        "BasicBlocks/Gain",
                        "BasicBlocks/Integrator"
                  };
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
                  else if (dataType == "complex_double")
                  {
                        return CreateBlockTyped<std::complex<double>>(blockClass, blockConfiguration, blockEventsHandler);
                  }
                  else if (dataType == "bool")
                  {
                        return CreateBlockTyped<bool>(blockClass, blockConfiguration, blockEventsHandler);
                  }
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
