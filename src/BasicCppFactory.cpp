#include "BasicCppFactory.h"
#include "Constant.h"
#include "Sumator.h"
#include "Display.h"
#include "Acumulator.h"

namespace BlockLibraries::BasicBlocksBasicCpp
{
    std::vector<std::string> BasicCppFactory::GetSupportedBlockClasses() const
    {
        return {"BasicBlocks/Constant",
                "BasicBlocks/Sumator",
                "BasicBlocks/Acumulator",
                "BasicBlocks/Display"};
    }

    std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock> BasicCppFactory::CreateBlock(std::string blockClass, std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> blockConfiguration, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler)
    {
        if (blockClass == "BasicBlocks/Constant")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Constant>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else if (blockClass == "BasicBlocks/Sumator")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Sumator>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else if (blockClass == "BasicBlocks/Display")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Display>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else if (blockClass == "BasicBlocks/Acumulator")
        {
            std::unique_ptr<BlockTypes::BasicCpp::SimulationBlock> simulationBlock = std::make_unique<BlockLibraries::BasicBlocksBasicCpp::Acumulator>(blockConfiguration, eventHandler);
            return std::move(simulationBlock);
        }
        else 
        {
            throw std::out_of_range("Block type with id: " + blockClass + " not found in block library BasicBlocksBasicCpp.");
        }
    }
} // namespace BlockLibraries::BasicBlocksBasicCpp
