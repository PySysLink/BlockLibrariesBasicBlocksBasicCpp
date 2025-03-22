#include "BasicCppFactory.h"
#include "Constant.h"
#include "Adder.h"
#include "Display.h"
#include "Accumulator.h"
#include "Integrator.h"
#include "ContinuousToDiscrete.h"

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    std::vector<std::string> BasicCppFactory<T>::GetSupportedBlockClasses() const
    {
        return {"BasicBlocks/Constant",
                "BasicBlocks/Adder",
                "BasicBlocks/Accumulator",
                "BasicBlocks/Display",
                "BasicBlocks/Integrator",
                "BasicBlocks/ContinuousToDiscrete"};
    }

    template <typename T>
    std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock<T>> BasicCppFactory<T>::CreateBlock(std::string blockClass, std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> blockConfiguration, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler)
    {
        if (blockClass == "BasicBlocks/Constant")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock<T>> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Constant<T>>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else if (blockClass == "BasicBlocks/Adder")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock<T>> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Adder<T>>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else if (blockClass == "BasicBlocks/Display")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock<T>> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Display<T>>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else if (blockClass == "BasicBlocks/Accumulator")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock<T>> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Accumulator<T>>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else if (blockClass == "BasicBlocks/ContinuousToDiscrete")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock<T>> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::ContinuousToDiscrete<T>>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else if (blockClass == "BasicBlocks/Integrator")
        {
            if constexpr (std::is_same_v<T, double>)
            {
                return std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Integrator<double>>(blockConfiguration, eventHandler);
            }
            else
            {
                throw std::invalid_argument("The Integrator block is only supported for type double.");
            }
        }
        else 
        {
            throw std::out_of_range("Block type with id: " + blockClass + " not found in block library BasicBlocksBasicCpp.");
        }
    }

    template class BasicCppFactory<double>;
    template class BasicCppFactory<std::complex<double>>;
} // namespace BlockLibraries::BasicBlocksBasicCpp
