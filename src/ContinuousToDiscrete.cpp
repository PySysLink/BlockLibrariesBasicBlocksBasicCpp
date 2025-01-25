#include "ContinuousToDiscrete.h"

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    ContinuousToDiscrete<T>::ContinuousToDiscrete(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler) : BlockTypes::BasicCpp::SimulationBlock<T>(configurationValues, eventHandler)
    {
        std::vector<std::shared_ptr<BlockTypes::BasicCpp::SampleTime>> multirateSampleTimes = {};
        int inputMultirateSampleTimeIndex = 0;
        int outputMultirateSampleTimeIndex = 1;

        try
        {
            this->continuousSampleTimeGroup = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<int>("ContinuousSampleTimeGroup", configurationValues);
            multirateSampleTimes.push_back(std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::continuous, this->continuousSampleTimeGroup));
        }
        catch(const std::exception& e)
        {
            this->sampleTimeValue = std::numeric_limits<double>::quiet_NaN();
            multirateSampleTimes.push_back(std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::inherited,
                                                                        std::vector<BlockTypes::BasicCpp::SampleTimeType>{BlockTypes::BasicCpp::SampleTimeType::continuous}));
        }
        try
        {
            this->sampleTimeValue = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<double>("DiscreteSampleTime", configurationValues);
            multirateSampleTimes.push_back(std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::discrete, this->sampleTimeValue));
        }
        catch(const std::invalid_argument& e)
        {
            this->sampleTimeValue = std::numeric_limits<double>::quiet_NaN();
            multirateSampleTimes.push_back(std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::inherited,
                                                                        std::vector<BlockTypes::BasicCpp::SampleTimeType>{BlockTypes::BasicCpp::SampleTimeType::discrete}));
        }
        
        this->sampleTime = std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::multirate, multirateSampleTimes, inputMultirateSampleTimeIndex, outputMultirateSampleTimeIndex);     

    }

    template <typename T>
    const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> ContinuousToDiscrete<T>::GetSampleTime() const
    {
        return this->sampleTime;
    }

    template <typename T>
    const int ContinuousToDiscrete<T>::GetInputPortAmmount() const
    {
        return 1;
    }

    template <typename T>
    const int ContinuousToDiscrete<T>::GetOutputPortAmmount() const
    {
        return 1;
    }

    template <typename T>
    const std::vector<bool> ContinuousToDiscrete<T>::InputsHasDirectFeedthrough() const 
    {
        std::vector<bool> result = {true};
        return result;
    }

    template <typename T>
    std::vector<T> ContinuousToDiscrete<T>::CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        if (sampleTime->GetSampleTimeType() == BlockTypes::BasicCpp::SampleTimeType::continuous)
        {
            this->bufferedValue = inputs[0];
            return {this->bufferedValue};
        }
        else
        {
            return {this->bufferedValue};
        }
    }

    template class ContinuousToDiscrete<double>;
    template class ContinuousToDiscrete<std::complex<double>>;

} // namespace BlockLibraries::BasicBlocks

