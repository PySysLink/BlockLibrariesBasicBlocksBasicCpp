#include "Adder.h"

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    Adder<T>::Adder(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler) : BlockTypes::BasicCpp::SimulationBlock<T>(configurationValues, eventHandler)
    {
        this->gains = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<std::vector<T>>("Gains", configurationValues);

        this->sampleTime = std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::inherited, 
                                                                     std::vector<BlockTypes::BasicCpp::SampleTimeType>{BlockTypes::BasicCpp::SampleTimeType::constant,
                                                                                                                        BlockTypes::BasicCpp::SampleTimeType::continuous,
                                                                                                                        BlockTypes::BasicCpp::SampleTimeType::discrete});    
    }

    template <typename T>
    const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> Adder<T>::GetSampleTime() const
    {
        return this->sampleTime;
    }
    template <typename T>
    const int Adder<T>::GetInputPortAmount() const
    {
        return this->gains.size();
    }

    template <typename T>
    const int Adder<T>::GetOutputPortAmount() const
    {
        return 1;
    }

    template <typename T>
    const std::vector<bool> Adder<T>::InputsHasDirectFeedthrough() const 
    {
        std::vector<bool> result = {};
        for (int i = 0; i < this->gains.size(); i++)
        {
            result.push_back(true);
        }
        return result;
    }

    template <typename T>
    std::vector<T> Adder<T>::CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        T sumation = 0;
        for (int i = 0; i < this->gains.size(); i++)
        {
            sumation += inputs[i] * this->gains[i];
        }
        return {sumation};
    }

    template <typename T>
    bool Adder<T>::TryUpdateConfigurationValue(std::string keyName, BlockTypes::BasicCpp::ConfigurationValue value)
    {
        if (keyName == "Gains")
        {
            try
            {
                this->gains = std::get<std::vector<T>>(value);
                return true;
            }
            catch(std::bad_variant_access)
            {
                return false;
            }
        }
        else {return false;}
    }

    template class Adder<double>;
    template class Adder<std::complex<double>>;

} // namespace BlockLibraries::BasicBlocks

