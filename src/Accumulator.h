#ifndef SRC_ACUMULATOR
#define SRC_ACUMULATOR

#include <map>
#include <vector>
#include <BlockTypeSupports/BasicCppSupport/SimulationBlockCpp.h>
#include <PySysLinkBase/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class Accumulator : public BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>
    {
        private:
            std::shared_ptr<PySysLinkBase::SampleTime> sampleTime;
            T value;
            double sampleTimeValue;
        public:
            Accumulator(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler);
            const int GetInputPortAmount() const;
            const int GetOutputPortAmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<T> ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep=false) override;
    };

    template <typename T>
    Accumulator<T>::Accumulator(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler) : BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>(configurationValues, eventHandler)
    {
        try
        {
            this->value = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<T>("InitialValue", configurationValues);
        }
        catch (...) // TODO change to correct error
        {
            this->value = 0;
        }
        this->sampleTimeValue = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<double>("SampleTime", configurationValues);
        this->sampleTime = std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::discrete, this->sampleTimeValue);
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
        return {false};
    }

    template <typename T>
    std::vector<T> Accumulator<T>::ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        T value_no_updated = this->value;
        this->value += inputs[0];
        return {value_no_updated};
    }
} // namespace BlockLibraries::BasicBlocksBasicCpp

#endif /* SRC_ACUMULATOR */
