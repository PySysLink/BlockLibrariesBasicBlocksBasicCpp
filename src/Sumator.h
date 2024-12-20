#ifndef SRC_SUMATOR
#define SRC_SUMATOR
#ifndef BLOCK_LIBRARIES_BASIC_BLOCKS_SUMATOR
#define BLOCK_LIBRARIES_BASIC_BLOCKS_SUMATOR

#include <BlockTypes/BasicCpp/SimulationBlock.h>
#include <BlockTypes/BasicCpp/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    class Sumator : public BlockTypes::BasicCpp::SimulationBlock
    {
        private:
            std::vector<double> gains;
            std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime;
        public:
            Sumator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler);
            const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> GetSampleTime() const;
            const int GetInputPortAmmount() const;
            const int GetOutputPortAmmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<double> CalculateOutputs(const std::vector<double> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime);
    };
} // namespace BasicBlocks


#endif /* BLOCK_LIBRARIES_BASIC_BLOCKS_SUMATOR */


#endif /* SRC_SUMATOR */
