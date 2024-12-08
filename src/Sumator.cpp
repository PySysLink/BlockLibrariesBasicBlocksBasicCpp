#include "Sumator.h"
#include <iostream>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    Sumator::Sumator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues) : BlockTypes::BasicCpp::SimulationBlock(configurationValues)
    {
        this->gains = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<std::vector<double>>("Gains", configurationValues);

        this->sampleTimes.push_back(BlockTypes::BasicCpp::SampleTime(BlockTypes::BasicCpp::SampleTimeType::inherited, 
                                                                     std::vector<BlockTypes::BasicCpp::SampleTimeType>{BlockTypes::BasicCpp::SampleTimeType::constant,
                                                                                                                        BlockTypes::BasicCpp::SampleTimeType::continuous,
                                                                                                                        BlockTypes::BasicCpp::SampleTimeType::discrete}));    
        std::cout << "Sample time account: " << this->sampleTimes.size() << std::endl;

    }

    const std::vector<BlockTypes::BasicCpp::SampleTime>& Sumator::GetSampleTimes() const
    {
        return this->sampleTimes;
    }

    const int Sumator::GetInputPortAmmount() const
    {
        return this->gains.size();
    }
    const int Sumator::GetOutputPortAmmount() const
    {
        return 1;
    }

    const std::vector<bool> Sumator::InputsHasDirectFeedthrough() const 
    {
        std::vector<bool> result = {};
        for (int i = 0; i < this->gains.size(); i++)
        {
            result.push_back(true);
        }
        return result;
    }

    std::vector<double> Sumator::CalculateOutputs(const std::vector<double> inputs, BlockTypes::BasicCpp::SampleTime sampleTime)
    {
        double sumation = 0;
        std::cout << "Start sumation..." << std::endl;
        for (int i = 0; i < this->gains.size(); i++)
        {
            sumation += inputs[i] * this->gains[i];
            std::cout << "Sumation: " << sumation << std::endl;
        }
        return {sumation};
    }

} // namespace BlockLibraries::BasicBlocks

