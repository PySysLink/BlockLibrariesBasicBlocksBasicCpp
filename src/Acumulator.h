#ifndef SRC_ACUMULATOR
#define SRC_ACUMULATOR


#include <BlockTypes/BasicCpp/SimulationBlock.h>
#include <BlockTypes/BasicCpp/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    class Acumulator : public BlockTypes::BasicCpp::SimulationBlock
    {
        private:
            std::vector<BlockTypes::BasicCpp::SampleTime> sampleTimes;
            float value;
            double sampleTime;
        public:
            Acumulator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues);
            const std::vector<BlockTypes::BasicCpp::SampleTime>& GetSampleTimes() const;
            const int GetInputPortAmmount() const;
            const int GetOutputPortAmmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<double> CalculateOutputs(const std::vector<double> inputs, BlockTypes::BasicCpp::SampleTime sampleTime);
    };
} // namespace BasicBlocks


#endif /* SRC_ACUMULATOR */
