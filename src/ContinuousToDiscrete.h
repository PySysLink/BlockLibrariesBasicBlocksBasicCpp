#ifndef SRC_CONTINUOUS_TO_DISCRETE
#define SRC_CONTINUOUS_TO_DISCRETE

#include <map>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <BlockTypeSupports/BasicCppSupport/SimulationBlockCpp.h>
#include <PySysLinkBase/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class ContinuousToDiscrete : public BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>
    {
        private:
            T bufferedValue;
            int continuousSampleTimeGroup = -1;
            double sampleTimeValue = std::numeric_limits<double>::quiet_NaN();
            double simulationStartTime = std::numeric_limits<double>::quiet_NaN();
        public:
            ContinuousToDiscrete(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler, int inputPortNumber, int outputPortNumber);

            std::vector<T> ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep=false) override;
            const std::vector<double> GetKnownEvents(const std::shared_ptr<PySysLinkBase::SampleTime> resolvedSampleTime, double simulationStartTime, double simulationEndTime) const override;
    };

    template <typename T>
    ContinuousToDiscrete<T>::ContinuousToDiscrete(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler, int inputPortNumber, int outputPortNumber)
        : BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>(configurationValues, eventHandler, inputPortNumber, outputPortNumber, true)
    {
        std::vector<std::shared_ptr<PySysLinkBase::SampleTime>> multirateSampleTimes = {};
        int inputMultirateSampleTimeIndex = 0;
        int outputMultirateSampleTimeIndex = 1;

        try
        {
            this->continuousSampleTimeGroup = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<int>("ContinuousSampleTimeGroup", configurationValues);
            multirateSampleTimes.push_back(std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::continuous, this->continuousSampleTimeGroup));
        }
        catch(const std::exception&)
        {
            multirateSampleTimes.push_back(std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::inherited,
                                                                        std::vector<PySysLinkBase::SampleTimeType>{PySysLinkBase::SampleTimeType::continuous}));
        }
        try
        {
            this->sampleTimeValue = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<double>("DiscreteSampleTime", configurationValues);
            multirateSampleTimes.push_back(std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::discrete, this->sampleTimeValue));
        }
        catch(const std::invalid_argument&)
        {
            multirateSampleTimes.push_back(std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::inherited,
                                                                        std::vector<PySysLinkBase::SampleTimeType>{PySysLinkBase::SampleTimeType::discrete}));
        }

        this->sampleTime = std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::multirate, multirateSampleTimes, inputMultirateSampleTimeIndex, outputMultirateSampleTimeIndex);
    }

    template <typename T>
    std::vector<T> ContinuousToDiscrete<T>::ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        if (std::isnan(this->simulationStartTime))
        {
            this->simulationStartTime = currentTime;
        }
        if (sampleTime->GetSampleTimeType() == PySysLinkBase::SampleTimeType::continuous)
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
    const std::vector<double> ContinuousToDiscrete<T>::GetKnownEvents(const std::shared_ptr<PySysLinkBase::SampleTime> resolvedSampleTime, double simulationStartTime, double simulationEndTime) const
    {
        std::vector<double> knownSampleTimes;
        for (double t = simulationStartTime; t <= simulationEndTime; t += resolvedSampleTime->GetMultirateSampleTimes()[1]->GetDiscreteSampleTime())
        {
            knownSampleTimes.push_back(t);
        }
        return knownSampleTimes;
    }
} // namespace BlockLibraries::BasicBlocksBasicCpp

#endif /* SRC_CONTINUOUS_TO_DISCRETE */
