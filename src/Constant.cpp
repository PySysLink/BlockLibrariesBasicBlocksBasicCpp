#include "Constant.h"
#include <vector>
#include <stdexcept>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    Constant<T>::Constant(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler) : BlockTypes::BasicCpp::SimulationBlock<T>(configurationValues, eventHandler)
    {
        this->value = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<T>("Value", configurationValues);

        this->sampleTime = std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::constant);
    }

    template <typename T>
    const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> Constant<T>::GetSampleTime() const
    {
        return this->sampleTime;
    }

    template <typename T>
    const int Constant<T>::GetInputPortAmmount() const
    {
        return 0;
    }

    template <typename T>
    const int Constant<T>::GetOutputPortAmmount() const
    {
        return 1;
    }

    template <typename T>
    const std::vector<bool> Constant<T>::InputsHasDirectFeedthrough() const 
    {
        return {};
    }

    template <typename T>
    std::vector<T> Constant<T>::CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        return {this->value};
    }

    template <typename T>
    bool Constant<T>::TryUpdateConfigurationValue(std::string keyName, BlockTypes::BasicCpp::ConfigurationValue value)
    {
        if (keyName == "Value")
        {
            try
            {
                this->value = std::get<double>(value);
                return true;
            }
            catch(std::bad_variant_access)
            {
                return false;
            }
        }
        else {return false;}
    }

    template class Constant<double>;
    template class Constant<std::complex<double>>;
} // namespace BlockLibraries::BasicBlocks

