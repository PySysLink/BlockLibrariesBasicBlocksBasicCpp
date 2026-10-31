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
            T value;
            double sampleTimeValue;
        public:
            Accumulator(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler, int inputPortNumber, int outputPortNumber);
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<T> ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep=false) override;
    };

    template <typename T>
    Accumulator<T>::Accumulator(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler, int inputPortNumber, int outputPortNumber)
        : BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>(configurationValues, eventHandler, inputPortNumber, outputPortNumber, false)
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
        if (this->sampleTimeValue <= 0 && this->sampleTimeValue != -1)
        {
            throw std::invalid_argument("SampleTime must be greater than 0 or equal to -1 for inherited sample time.");
        }
        if (this->sampleTimeValue == -1)
        {
            this->sampleTime = std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::inherited, std::vector<PySysLinkBase::SampleTimeType>{PySysLinkBase::SampleTimeType::discrete});
        }
        else
        {
            this->sampleTime = std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::discrete, this->sampleTimeValue);
        }
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
