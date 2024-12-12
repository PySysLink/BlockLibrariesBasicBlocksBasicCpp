#ifndef BLOCK_LIBRARIES_BASIC_BLOCKS_DISPLAY
#define BLOCK_LIBRARIES_BASIC_BLOCKS_DISPLAY


#include <BlockTypes/BasicCpp/SimulationBlock.h>
#include <BlockTypes/BasicCpp/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    class Display : public BlockTypes::BasicCpp::SimulationBlock
    {
        private:
            std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime;
        public:
            Display(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues);
            const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> GetSampleTime() const;
            const int GetInputPortAmmount() const;
            const int GetOutputPortAmmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<double> CalculateOutputs(const std::vector<double> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime);
    };
} // namespace BasicBlocksBasicCpp


#endif /* BLOCK_LIBRARIES_BASIC_BLOCKS_DISPLAY */
