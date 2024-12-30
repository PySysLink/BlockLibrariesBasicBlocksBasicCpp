#include "Acumulator.h"

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    Acumulator<T>::Acumulator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler) : BlockTypes::BasicCpp::SimulationBlock<T>(configurationValues, eventHandler)
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
    const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> Acumulator<T>::GetSampleTime() const
    {
        return this->sampleTime;
    }

    template <typename T>
    const int Acumulator<T>::GetInputPortAmmount() const
    {
        return 1;
    }

    template <typename T>
    const int Acumulator<T>::GetOutputPortAmmount() const
    {
        return 1;
    }

    template <typename T>
    const std::vector<bool> Acumulator<T>::InputsHasDirectFeedthrough() const 
    {
        std::vector<bool> result = {false};
        return result;
    }

    template <typename T>
    std::vector<T> Acumulator<T>::CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime)
    {
        T value_no_updated = this->value;
        this->value += inputs[0];
        return {value_no_updated};
    }

    template class Acumulator<double>;
    template class Acumulator<std::complex<double>>;

} // namespace BlockLibraries::BasicBlocks

