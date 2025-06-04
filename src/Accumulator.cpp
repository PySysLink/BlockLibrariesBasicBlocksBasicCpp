#include "Accumulator.h"

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    Accumulator<T>::Accumulator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler) : BlockTypes::BasicCpp::SimulationBlock<T>(configurationValues, eventHandler)
    {
        try
        {
            this->value = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<T>("InitialValue", configurationValues);
        }
        catch (...) // TODO change to correct error
        {
            this->value = 0;
        }
        this->sampleTimeValue = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<double>("SampleTime", configurationValues);
        this->sampleTime = std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::discrete, this->sampleTimeValue);    
    }

    template <typename T>
    const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> Accumulator<T>::GetSampleTime() const
    {
        return this->sampleTime;
    }

    template <typename T>
    const int Accumulator<T>::GetInputPortAmount() const
    {
        return 1;
    }

    template <typename T>
    const int Accumulator<T>::GetOutputPortAmount() const
    {
        return 1;
    }

    template <typename T>
    const std::vector<bool> Accumulator<T>::InputsHasDirectFeedthrough() const 
    {
        std::vector<bool> result = {false};
        return result;
    }

    template <typename T>
    std::vector<T> Accumulator<T>::CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        T value_no_updated = this->value;
        this->value += inputs[0];
        return {value_no_updated};
    }

    template class Accumulator<double>;
    template class Accumulator<std::complex<double>>;

} // namespace BlockLibraries::BasicBlocks

