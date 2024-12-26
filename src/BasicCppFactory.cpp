#include "BasicCppFactory.h"
#include "Constant.h"
#include "Sumator.h"
#include "Display.h"
#include "Acumulator.h"

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    std::vector<std::string> BasicCppFactory<T>::GetSupportedBlockClasses() const
    {
        return {"BasicBlocks/Constant",
                "BasicBlocks/Sumator",
                "BasicBlocks/Acumulator",
                "BasicBlocks/Display"};
    }

    template <typename T>
    std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock<T>> BasicCppFactory<T>::CreateBlock(std::string blockClass, std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> blockConfiguration, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler)
    {
        if (blockClass == "BasicBlocks/Constant")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock<T>> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Constant<T>>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else if (blockClass == "BasicBlocks/Sumator")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock<T>> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Sumator<T>>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else if (blockClass == "BasicBlocks/Display")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock<T>> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Display<T>>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else if (blockClass == "BasicBlocks/Acumulator")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock<T>> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Acumulator<T>>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else 
        {
            throw std::out_of_range("Block type with id: " + blockClass + " not found in block library BasicBlocksBasicCpp.");
        }
    }

    template class BasicCppFactory<double>;
    template class BasicCppFactory<std::complex<double>>;
} // namespace BlockLibraries::BasicBlocksBasicCpp
