#ifndef SRC_INTEGRATOR
#define SRC_INTEGRATOR


#include <BlockTypes/BasicCpp/SimulationBlockWithContinuousStates.h>
#include <BlockTypes/BasicCpp/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class Integrator : public BlockTypes::BasicCpp::SimulationBlockWithContinuousStates<T>
    {
        private:
            std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime;
            double integratorValue;
        public:
            Integrator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler);
            const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> GetSampleTime() const;
            const int GetInputPortAmmount() const;
            const int GetOutputPortAmmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<T> CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime);
            
            const std::vector<double> GetContinuousStates() const;
            void SetContinuousStates(std::vector<double> newStates);

            const std::vector<double> GetContinousStateDerivatives(const std::vector<T> inputs, const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime) const;

    };

    extern template class Integrator<double>;
} // namespace BasicBlocks


#endif /* SRC_INTEGRATOR */