#include "Integrator.h"
#include <limits>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    Integrator<T>::Integrator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler) : BlockTypes::BasicCpp::SimulationBlockWithContinuousStates<T>(configurationValues, eventHandler)
    {
        try
        {
            this->integratorValue = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<T>("InitialValue", configurationValues);
        }
        catch (...) // TODO change to correct error
        {
            this->integratorValue = 0;
        }

        int continuousSampleTimeGroup;
        try
        {
           continuousSampleTimeGroup = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<int>("ContinuousSampleTimeGroup", configurationValues);
        }
        catch (...) // TODO change to correct error
        {
            continuousSampleTimeGroup = 0;
        }
        this->sampleTime = std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::continuous, continuousSampleTimeGroup);    

    }

    template <typename T>
    const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> Integrator<T>::GetSampleTime() const
    {
        return this->sampleTime;
    }

    template <typename T>
    const int Integrator<T>::GetInputPortAmount() const
    {
        return 1;
    }

    template <typename T>
    const int Integrator<T>::GetOutputPortAmount() const
    {
        return 1;
    }

    template <typename T>
    const std::vector<bool> Integrator<T>::InputsHasDirectFeedthrough() const 
    {
        std::vector<bool> result = {false};
        return result;
    }

    template <typename T>
    std::vector<T> Integrator<T>::CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        return {this->integratorValue};
    }

    template <typename T>
    const std::vector<double> Integrator<T>::GetContinuousStates() const
    {
        return {this->integratorValue};
    }

    template <typename T>
    void Integrator<T>::SetContinuousStates(std::vector<double> newStates)
    {
        this->integratorValue = newStates[0];
    }

    template <typename T>
    const std::vector<double> Integrator<T>::GetContinuousStateDerivatives(const std::vector<T> inputs, const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime) const
    {
        return {inputs[0]};
    }

    template <typename T>
    const std::vector<std::pair<double, double>> Integrator<T>::GetEvents(const std::vector<T> inputs, const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double eventTime, std::vector<double> eventTimeStates) const
    {
        return {std::make_pair(eventTimeStates[0], std::numeric_limits<double>::quiet_NaN())};
    }


    template class Integrator<double>;

} // namespace BlockLibraries::BasicBlocks

