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
#include <iostream>

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
            std::unique_ptr<PySysLinkBase::ISimulationBlock> CreateBlockTyped(const std::string& blockClass, const ConfigMap& cfg, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> handler, int inputPortAmmount, int outputPortAmmount)
            {
                  if (blockClass == "BasicBlocks/Constant")
                        return std::make_unique<Constant<T>>(cfg, handler, inputPortAmmount, outputPortAmmount);

                  if (blockClass == "BasicBlocks/Adder")
                        return std::make_unique<Adder<T>>(cfg, handler, inputPortAmmount, outputPortAmmount);

                  if (blockClass == "BasicBlocks/Display")
                        return std::make_unique<Display<T>>(cfg, handler, inputPortAmmount, outputPortAmmount);

                  if (blockClass == "BasicBlocks/Accumulator")
                        return std::make_unique<Accumulator<T>>(cfg, handler, inputPortAmmount, outputPortAmmount);

                  if (blockClass == "BasicBlocks/ContinuousToDiscrete")
                        return std::make_unique<ContinuousToDiscrete<T>>(cfg, handler, inputPortAmmount, outputPortAmmount);

                  if (blockClass == "BasicBlocks/Gain")
                        if constexpr (std::is_same_v<T, double>) {
                              return std::make_unique<Gain<double>>(cfg, handler, inputPortAmmount, outputPortAmmount);
                        }
                        else if constexpr (std::is_same_v<T, int>) {
                              return std::make_unique<Gain<int>>(cfg, handler, inputPortAmmount, outputPortAmmount);
                        } else if constexpr (std::is_same_v<T, std::complex<double>>) {
                              return std::make_unique<Gain<std::complex<double>>>(cfg, handler, inputPortAmmount, outputPortAmmount);
                        } else {
                              throw std::invalid_argument("Gain does not support bool.");
                        }

                  if (blockClass == "BasicBlocks/Integrator")
                  {
                        if constexpr (!std::is_same_v<T, double>)
                        {
                              throw std::invalid_argument("Integrator only supports double.");
                        }

                        return std::make_unique<Integrator<double>>(cfg, handler, inputPortAmmount, outputPortAmmount);
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

            
            std::unique_ptr<PySysLinkBase::ISimulationBlock> CreateBlock(std::string blockClass, std::map<std::string, PySysLinkBase::ConfigurationValue> blockConfiguration, 
                                                                         std::shared_ptr<PySysLinkBase::IBlockEventsHandler> blockEventsHandler,
                                                                         std::string dataType, int inputPortAmmount, int outputPortAmmount) override
            {
                  if (dataType == "int")
                  {
                        return CreateBlockTyped<int>(blockClass, blockConfiguration, blockEventsHandler, inputPortAmmount, outputPortAmmount);
                  }
                  else if (dataType == "double")
                  {
                        return CreateBlockTyped<double>(blockClass, blockConfiguration, blockEventsHandler, inputPortAmmount, outputPortAmmount);
                  }
                  else if (dataType == "complex_double")
                  {
                        return CreateBlockTyped<std::complex<double>>(blockClass, blockConfiguration, blockEventsHandler, inputPortAmmount, outputPortAmmount);
                  }
                  else if (dataType == "bool")
                  {
                        return CreateBlockTyped<bool>(blockClass, blockConfiguration, blockEventsHandler, inputPortAmmount, outputPortAmmount);
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
