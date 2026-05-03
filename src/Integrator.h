#ifndef SRC_INTEGRATOR
#define SRC_INTEGRATOR

#include <map>
#include <vector>
#include <utility>
#include <limits>
#include <BlockTypeSupports/BasicCppSupport/SimulationBlockCppWithContinuousStates.h>
#include <PySysLinkBase/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class Integrator : public BlockTypeSupports::BasicCppSupport::SimulationBlockCppWithContinuousStates<T>
    {
        private:
            std::shared_ptr<PySysLinkBase::SampleTime> sampleTime;
            double integratorValue;
        public:
            Integrator(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler);
            const int GetInputPortAmount() const;
            const int GetOutputPortAmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<T> ComputeOutputsOfCppBlock(const std::vector<T> inputs, const std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep=false) override;
            const std::vector<double> GetContinuousStates() const;
            void SetContinuousStates(std::vector<double> newStates);
            const std::vector<double> GetContinuousStateDerivativesOfCppBlock(const std::vector<T> inputs, const std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime) const;
            const std::vector<std::pair<double, double>> GetEvents(const std::vector<T> inputs, const std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double eventTime, std::vector<double> eventTimeStates, bool includeKnownEvents=false) const override;
    };

    template <typename T>
    Integrator<T>::Integrator(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler) : BlockTypeSupports::BasicCppSupport::SimulationBlockCppWithContinuousStates<T>(configurationValues, eventHandler)
    {
        try
        {
            this->integratorValue = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<T>("InitialValue", configurationValues);
        }
        catch (...) // TODO change to correct error
        {
            this->integratorValue = 0;
        }

        int continuousSampleTimeGroup;
        try
        {
            continuousSampleTimeGroup = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<int>("ContinuousSampleTimeGroup", configurationValues);
        }
        catch (...) // TODO change to correct error
        {
            continuousSampleTimeGroup = 0;
        }
        this->sampleTime = std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::continuous, continuousSampleTimeGroup);
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
        return {false};
    }

    template <typename T>
    std::vector<T> Integrator<T>::ComputeOutputsOfCppBlock(const std::vector<T> inputs, const std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        return {static_cast<T>(this->integratorValue)};
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
    const std::vector<double> Integrator<T>::GetContinuousStateDerivativesOfCppBlock(const std::vector<T> inputs, const std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime) const
    {
        return {inputs[0]};
    }

    template <typename T>
    const std::vector<std::pair<double, double>> Integrator<T>::GetEvents(const std::vector<T> inputs, const std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double eventTime, std::vector<double> eventTimeStates, bool includeKnownEvents) const
    {
        return {std::make_pair(eventTimeStates[0], std::numeric_limits<double>::quiet_NaN())};
    }
} // namespace BlockLibraries::BasicBlocksBasicCpp

#endif /* SRC_INTEGRATOR */
