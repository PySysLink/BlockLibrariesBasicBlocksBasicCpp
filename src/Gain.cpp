#include "Gain.h"

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    Gain<T>::Gain(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler) : BlockTypes::BasicCpp::SimulationBlock<T>(configurationValues, eventHandler)
    {
        this->gain = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<T>("Gain", configurationValues);

        this->sampleTime = std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::inherited, 
                                                                     std::vector<BlockTypes::BasicCpp::SampleTimeType>{BlockTypes::BasicCpp::SampleTimeType::constant,
                                                                                                                        BlockTypes::BasicCpp::SampleTimeType::continuous,
                                                                                                                        BlockTypes::BasicCpp::SampleTimeType::discrete});    
    }

    template <typename T>
    const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> Gain<T>::GetSampleTime() const
    {
        return this->sampleTime;
    }
    template <typename T>
    const int Gain<T>::GetInputPortAmount() const
    {
        return 1;
    }

    template <typename T>
    const int Gain<T>::GetOutputPortAmount() const
    {
        return 1;
    }

    template <typename T>
    const std::vector<bool> Gain<T>::InputsHasDirectFeedthrough() const 
    {
        return {true};
    }

    template <typename T>
    std::vector<T> Gain<T>::CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        return {inputs[0] * this->gain};
    }

    template <typename T>
    bool Gain<T>::TryUpdateConfigurationValue(std::string keyName, BlockTypes::BasicCpp::ConfigurationValue value)
    {
        if (keyName == "Gain")
        {
            try
            {
                this->gain = std::get<T>(value);
                return true;
            }
            catch(std::bad_variant_access)
            {
                return false;
            }
        }
        else {return false;}
    }

    template class Gain<double>;
    template class Gain<std::complex<double>>;

} // namespace BlockLibraries::BasicBlocks

