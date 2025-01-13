#include "Display.h"
#include <vector>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    Display<T>::Display(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler) : BlockTypes::BasicCpp::SimulationBlock<T>(configurationValues, eventHandler)
    {
        this->sampleTime = std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::inherited, 
                                                                     std::vector<BlockTypes::BasicCpp::SampleTimeType>{BlockTypes::BasicCpp::SampleTimeType::constant,
                                                                                                                        BlockTypes::BasicCpp::SampleTimeType::continuous,
                                                                                                                        BlockTypes::BasicCpp::SampleTimeType::discrete});    

        this->id = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<std::string>("Id", configurationValues);
    }

    template <typename T>
    const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> Display<T>::GetSampleTime() const
    {
        return this->sampleTime;
    }

    template <typename T>
    const int Display<T>::GetInputPortAmmount() const
    {
        return 1;
    }

    template <typename T>
    const int Display<T>::GetOutputPortAmmount() const
    {
        return 0;
    }

    template <typename T>
    const std::vector<bool> Display<T>::InputsHasDirectFeedthrough() const 
    {
        return {false};
    }

    template <typename T>
    std::vector<T> Display<T>::CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        if (!isMinorStep)
        {
            this->eventHandler->NotifyNewValueEvent(currentTime, "DisplayValue/" + this->id, inputs[0]);
        }
        return {};
    }  

    template class Display<double>;
    template class Display<std::complex<double>>;
} // namespace BlockLibraries::BasicBlocks

