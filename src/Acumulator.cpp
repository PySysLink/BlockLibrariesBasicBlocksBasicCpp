#include "Acumulator.h"
#include <iostream>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    Acumulator::Acumulator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues) : BlockTypes::BasicCpp::SimulationBlock(configurationValues)
    {
        try
        {
            this->value = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<double>("InitialValue", configurationValues);
        }
        catch (...) // TODO change to correct error
        {
            this->value = 0;
        }
        this->sampleTime = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<double>("SampleTime", configurationValues);

        this->sampleTimes.push_back(BlockTypes::BasicCpp::SampleTime(BlockTypes::BasicCpp::SampleTimeType::discrete, this->sampleTime));    
        std::cout << "Sample time account: " << this->sampleTimes.size() << std::endl;

    }

    const std::vector<BlockTypes::BasicCpp::SampleTime>& Acumulator::GetSampleTimes() const
    {
        return this->sampleTimes;
    }

    const int Acumulator::GetInputPortAmmount() const
    {
        return 1;
    }
    const int Acumulator::GetOutputPortAmmount() const
    {
        return 1;
    }

    const std::vector<bool> Acumulator::InputsHasDirectFeedthrough() const 
    {
        std::vector<bool> result = {false};
        return result;
    }

    std::vector<double> Acumulator::CalculateOutputs(const std::vector<double> inputs, BlockTypes::BasicCpp::SampleTime sampleTime)
    {
        double value_no_updated = this->value;
        this->value += inputs[0];
        return {value_no_updated};
    }

} // namespace BlockLibraries::BasicBlocks

