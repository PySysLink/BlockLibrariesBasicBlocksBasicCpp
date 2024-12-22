#ifndef SRC_BASIC_BLOCKS_CONSTANT
#define SRC_BASIC_BLOCKS_CONSTANT

#include <BlockTypes/BasicCpp/SimulationBlock.h>
#include <BlockTypes/BasicCpp/SampleTime.h>
#include <BlockTypes/BasicCpp/ConfigurationValue.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    class Constant : public BlockTypes::BasicCpp::SimulationBlock
    {
        private:
            double value;
            std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime;
        public:
            Constant(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler);
            const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> GetSampleTime() const;
            const int GetInputPortAmmount() const;
            const int GetOutputPortAmmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<double> CalculateOutputs(const std::vector<double> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime);

            bool TryUpdateConfigurationValue(std::string keyName, BlockTypes::BasicCpp::ConfigurationValue value) override;
    };
} // namespace BasicBlocks

#endif /* SRC_BASIC_BLOCKS_CONSTANT */
