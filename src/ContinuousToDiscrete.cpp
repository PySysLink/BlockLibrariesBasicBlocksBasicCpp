#include "ContinuousToDiscrete.h"
#include <iostream>

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
        if (std::isnan(this->simulationStartTime))
        {
            this->simulationStartTime = currentTime;
        }
        if (sampleTime->GetSampleTimeType() == BlockTypes::BasicCpp::SampleTimeType::continuous)
        {
            this->bufferedValue = inputs[0];
            return {this->bufferedValue};
        }
        else
        {
            if (std::isnan(this->sampleTimeValue))
            {
                this->sampleTimeValue = sampleTime->GetDiscreteSampleTime();
            }
            return {this->bufferedValue};
        }
    }

    template <typename T>
    const std::vector<double> ContinuousToDiscrete<T>::GetKnownEvents(const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> resolvedSampleTime, double simulationStartTime, double simulationEndTime) const
    {
        std::vector<double> knownSampleTimes = {};
        for (double t = simulationStartTime; t <= simulationEndTime; t += resolvedSampleTime->GetMultirateSampleTimes()[1]->GetDiscreteSampleTime())
        {
            knownSampleTimes.push_back(t);
        }
        return knownSampleTimes;
    }


    


    template class ContinuousToDiscrete<double>;
    template class ContinuousToDiscrete<std::complex<double>>;

} // namespace BlockLibraries::BasicBlocks

