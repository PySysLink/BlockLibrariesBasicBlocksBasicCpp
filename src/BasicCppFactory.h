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
                        if constexpr (std::is_same_v<T, double>) {
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

            std::string ResolveSignalType(
                  const std::vector<PySysLinkBase::PortTypeMetadata>& inputs,
                  const std::vector<PySysLinkBase::PortTypeMetadata>& outputs)
            {
                  
                  for (const auto& p : inputs)
                  {
                        if (p.category == PySysLinkBase::PortCategory::FullySupportedSignalValue &&
                        p.signalValueType.has_value())
                        {
                              std::cout << "Resolved signal type from input port: " << p.signalValueType.value() << std::endl;
                              return p.signalValueType.value();
                        }
                  }
                  for (const auto& p : outputs)
                  {
                        if (p.category == PySysLinkBase::PortCategory::FullySupportedSignalValue &&
                        p.signalValueType.has_value())
                        {
                              std::cout << "Resolved signal type from output port: " << p.signalValueType.value() << std::endl;
                              return p.signalValueType.value();
                        }
                  }

                  throw std::invalid_argument("Could not resolve signal type from ports.");
            }

            std::string PortCategoryToString(PySysLinkBase::PortCategory cat)
            {
                  using namespace PySysLinkBase;

                  switch (cat)
                  {
                        case PortCategory::FullySupportedSignalValue: return "FullySupportedSignalValue";
                        case PortCategory::Enumeration: return "Enumeration";
                        case PortCategory::Structure: return "Structure";
                        case PortCategory::PointerToObject: return "PointerToObject";
                        case PortCategory::OtherType: return "OtherType";
                        case PortCategory::Inherited: return "Inherited";
                        case PortCategory::Unknown: return "Unknown";
                        default: return "Invalid";
                  }
            }
            std::string JoinPortTypes(const std::vector<PySysLinkBase::PortTypeMetadata>& types)
            {
                  if (types.empty())
                        return "[]";

                  std::ostringstream oss;
                  oss << "[";

                  for (size_t i = 0; i < types.size(); ++i)
                  {
                        oss << PortCategoryToString(types[i].category);
                        oss << "(";
                        if (types[i].signalValueType.has_value())
                        {
                              oss << types[i].signalValueType.value();
                        }
                        else
                        {
                              oss << "no signal value type";
                        }
                        oss << ")";
                        if (i + 1 < types.size())
                              oss << ", ";
                  }

                  oss << "]";
                  return oss.str();
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
                  auto inputTypes = PySysLinkBase::ParsePortTypeMetadatas(
                  PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<std::vector<std::string>>(
                        "InputPortTypes", blockConfiguration));

                  auto outputTypes = PySysLinkBase::ParsePortTypeMetadatas(
                  PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<std::vector<std::string>>(
                        "OutputPortTypes", blockConfiguration));
                  
                  std::string dataType;
                  try {
                        dataType = ResolveSignalType(inputTypes, outputTypes);
                  }
                  catch (const std::invalid_argument&)
                  {
                        throw std::invalid_argument(
                              "Could not resolve signal type for block '" + blockClass +
                              "'\n  InputPortTypes: " + JoinPortTypes(inputTypes) +
                              "\n  OutputPortTypes: " + JoinPortTypes(outputTypes)
                        );
                  }


                  std::cout << "Creating block of class " << blockClass << " with data type " << dataType << std::endl;

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
