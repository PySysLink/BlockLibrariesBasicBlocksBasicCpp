#ifndef SRC_ACUMULATOR
#define SRC_ACUMULATOR


#include <BlockTypes/BasicCpp/SimulationBlock.h>
#include <BlockTypes/BasicCpp/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class Acumulator : public BlockTypes::BasicCpp::SimulationBlock<T>
    {
        private:
            std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime;
            T value;
            double sampleTimeValue;
        public:
            Acumulator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler);
            const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> GetSampleTime() const;
            const int GetInputPortAmmount() const;
            const int GetOutputPortAmmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<T> CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime, bool isMinorStep=false);
    };

    extern template class Acumulator<double>;
    extern template class Acumulator<std::complex<double>>;
} // namespace BasicBlocks


#endif /* SRC_ACUMULATOR */
