#include "Display.h"
#include <vector>
#include <iostream>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    Display::Display(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues) : BlockTypes::BasicCpp::SimulationBlock(configurationValues)
    {
        this->sampleTime = std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::inherited, 
                                                                     std::vector<BlockTypes::BasicCpp::SampleTimeType>{BlockTypes::BasicCpp::SampleTimeType::constant,
                                                                                                                        BlockTypes::BasicCpp::SampleTimeType::continuous,
                                                                                                                        BlockTypes::BasicCpp::SampleTimeType::discrete});    
    }

    const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> Display::GetSampleTime() const
    {
        return this->sampleTime;
    }

    const int Display::GetInputPortAmmount() const
    {
        return 1;
    }
    const int Display::GetOutputPortAmmount() const
    {
        return 0;
    }

    const std::vector<bool> Display::InputsHasDirectFeedthrough() const 
    {
        return {false};
    }

    std::vector<double> Display::CalculateOutputs(const std::vector<double> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime)
    {
        std::cout << "Display value: " << inputs[0] << std::endl;
        return {};
    }  
} // namespace BlockLibraries::BasicBlocks

