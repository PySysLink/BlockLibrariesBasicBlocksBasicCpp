#ifndef SRC_ACUMULATOR
#define SRC_ACUMULATOR


#include <BlockTypes/BasicCpp/SimulationBlock.h>
#include <BlockTypes/BasicCpp/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    class Acumulator : public BlockTypes::BasicCpp::SimulationBlock
    {
        private:
            std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime;
            float value;
            double sampleTimeValue;
        public:
            Acumulator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler);
            const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> GetSampleTime() const;
            const int GetInputPortAmmount() const;
            const int GetOutputPortAmmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<double> CalculateOutputs(const std::vector<double> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime);
    };
} // namespace BasicBlocks


#endif /* SRC_ACUMULATOR */
