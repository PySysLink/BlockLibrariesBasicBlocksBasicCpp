#include "Acumulator.h"

namespace BlockLibraries::BasicBlocksBasicCpp
{
    Acumulator::Acumulator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler) : BlockTypes::BasicCpp::SimulationBlock(configurationValues, eventHandler)
    {
        try
        {
            this->value = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<double>("InitialValue", configurationValues);
        }
        catch (...) // TODO change to correct error
        {
            this->value = 0;
        }
        this->sampleTimeValue = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<double>("SampleTime", configurationValues);

        this->sampleTime = std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::discrete, this->sampleTimeValue);    

    }

    const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> Acumulator::GetSampleTime() const
    {
        return this->sampleTime;
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

    std::vector<double> Acumulator::CalculateOutputs(const std::vector<double> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime)
    {
        double value_no_updated = this->value;
        this->value += inputs[0];
        return {value_no_updated};
    }

} // namespace BlockLibraries::BasicBlocks

