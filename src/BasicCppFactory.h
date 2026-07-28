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
#include <PySysLinkBase/FullySupportedSignalValue.h>

#include "Constant.h"
#include "Adder.h"
#include "Display.h"
#include "Accumulator.h"
#include "ContinuousToDiscrete.h"
#include "Gain.h"
#include "Saturation.h"
#include "Integrator.h" 
#include "ContinuousStateSpaceSISO.h"
#include "ContinuousStateSpaceMIMO.h"
#include "PackMatrix.h"
#include "UnpackMatrix.h"

namespace BlockLibraries::BasicBlocksBasicCpp
{
      class BasicCppFactory : public BlockTypeSupports::BasicCppSupport::IBasicCppBlockFactory {
      protected:

            using ConfigMap = std::map<std::string, PySysLinkBase::ConfigurationValue>;

           

            template <typename I, typename O>
            std::unique_ptr<PySysLinkBase::ISimulationBlock> CreateBlockTyped(const std::string& blockClass, const ConfigMap& cfg, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> handler, int inputPortAmount, int outputPortAmount)
            {
                  if (blockClass == "BasicBlocks/Constant")
                        return std::make_unique<Constant<I>>(cfg, handler, inputPortAmount, outputPortAmount);

                  if (blockClass == "BasicBlocks/Adder")
                        return std::make_unique<Adder<I>>(cfg, handler, inputPortAmount, outputPortAmount);

                  if (blockClass == "BasicBlocks/Display")
                        return std::make_unique<Display<I>>(cfg, handler, inputPortAmount, outputPortAmount);

                  if (blockClass == "BasicBlocks/Accumulator")
                        if constexpr (std::is_arithmetic_v<I> || std::is_same_v<I, std::complex<double>>) {
                              return std::make_unique<Accumulator<I>>(cfg, handler, inputPortAmount, outputPortAmount);
                        }
                        else {
                              throw std::invalid_argument("Accumulator does not support matrixes.");
                        }

                  if (blockClass == "BasicBlocks/ContinuousToDiscrete")
                        return std::make_unique<ContinuousToDiscrete<I>>(cfg, handler, inputPortAmount, outputPortAmount);

                  if (blockClass == "BasicBlocks/Gain")
                        if constexpr (!(std::is_same_v<I, bool> || std::is_same_v<I, PySysLinkBase::BoolMatrix>)) {
                              return std::make_unique<Gain<I>>(cfg, handler, inputPortAmount, outputPortAmount);
                        } else {
                              throw std::invalid_argument("Gain does not support bool.");
                        }
                  if (blockClass == "BasicBlocks/Saturation")
                  {
                        if constexpr (
                              std::is_same_v<I, int> ||
                              std::is_same_v<I, double> ||
                              std::is_same_v<I, PySysLinkBase::IntMatrix> ||
                              std::is_same_v<I, PySysLinkBase::DoubleMatrix>)
                        {
                              return std::make_unique<Saturation<I>>(
                                    cfg,
                                    handler,
                                    inputPortAmount,
                                    outputPortAmount);
                        }
                        else
                        {
                              throw std::invalid_argument(
                                    "Saturation only supports int, double, matrix<int> and matrix<double>.");
                        }
                  }

                  if (blockClass == "BasicBlocks/Integrator")
                  {
                        if constexpr (!std::is_same_v<I, double>)
                        {
                              throw std::invalid_argument("Integrator only supports double.");
                        }

                        return std::make_unique<Integrator<double>>(cfg, handler, inputPortAmount, outputPortAmount);
                  }
                  if (blockClass == "BasicBlocks/ContinuousStateSpaceSISO")
                  {
                        if constexpr (!std::is_same_v<I, double>)
                        {
                              throw std::invalid_argument("ContinuousStateSpaceSISO only supports double.");
                        }

                        return std::make_unique<ContinuousStateSpaceSISO>(cfg, handler, inputPortAmount, outputPortAmount);
                  }
                  if (blockClass == "BasicBlocks/ContinuousStateSpaceMIMO")
                  {
                        if constexpr (!std::is_same_v<I, Eigen::MatrixXd>)
                        {
                              throw std::invalid_argument("ContinuousStateSpaceMIMO only supports matrix<double>.");
                        }

                        return std::make_unique<ContinuousStateSpaceMIMO>(cfg, handler, inputPortAmount, outputPortAmount);
                  }
                  if (blockClass == "BasicBlocks/PackMatrix")
                  {
                        return std::make_unique<PackMatrix<I>>(cfg, handler, inputPortAmount, outputPortAmount);
                  }
                  if (blockClass == "BasicBlocks/UnpackMatrix")
                  {
                        return std::make_unique<UnpackMatrix<O>>(cfg, handler, inputPortAmount, outputPortAmount);
                  }

                  throw std::out_of_range("Block type not found: " + blockClass);
            }

            template<typename F>
            auto DispatchType(const std::string& type, F&& f)
            {
                  if (type == "int")
                        return f.template operator()<int>();

                  if (type == "double")
                        return f.template operator()<double>();

                  if (type == "complex_double")
                        return f.template operator()<std::complex<double>>();

                  if (type == "bool")
                        return f.template operator()<bool>();

                  if (type == "matrix<int>")
                        return f.template operator()<PySysLinkBase::IntMatrix>();

                  if (type == "matrix<double>")
                        return f.template operator()<PySysLinkBase::DoubleMatrix>();

                  if (type == "matrix<bool>")
                        return f.template operator()<PySysLinkBase::BoolMatrix>();

                  if (type == "matrix<complex_double>")
                        return f.template operator()<PySysLinkBase::ComplexMatrix>();

                  throw std::invalid_argument("Unsupported type: " + type);
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
                        "BasicBlocks/Saturation",
                        "BasicBlocks/Integrator",
                        "BasicBlocks/ContinuousStateSpaceSISO",
                        "BasicBlocks/ContinuousStateSpaceMIMO",
                        "BasicBlocks/PackMatrix",
                        "BasicBlocks/UnpackMatrix"
                  };
            }

            
            std::unique_ptr<PySysLinkBase::ISimulationBlock> CreateBlock(std::string blockClass, std::map<std::string, PySysLinkBase::ConfigurationValue> blockConfiguration, 
                                                                         std::shared_ptr<PySysLinkBase::IBlockEventsHandler> blockEventsHandler,
                                                                         std::string inputDataType, std::string outputDataType, int inputPortAmount, int outputPortAmount) override
            {
                  return DispatchType(inputDataType, [&]<typename I>()
                  {
                        return DispatchType(outputDataType, [&]<typename O>()
                        {
                              return CreateBlockTyped<I, O>(
                                    blockClass,
                                    blockConfiguration,
                                    blockEventsHandler,
                                    inputPortAmount,
                                    outputPortAmount);
                        });
                  }); 
            }
      };
} // namespace BlockLibraries::BasicBlocksBasicCpp

#endif /* SRC_BASIC_CPP_FACTORY */
