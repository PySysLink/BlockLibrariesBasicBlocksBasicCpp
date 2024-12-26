#ifndef SRC_SUMATOR
#define SRC_SUMATOR
#ifndef BLOCK_LIBRARIES_BASIC_BLOCKS_SUMATOR
#define BLOCK_LIBRARIES_BASIC_BLOCKS_SUMATOR

#include <BlockTypes/BasicCpp/SimulationBlock.h>
#include <BlockTypes/BasicCpp/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class Sumator : public BlockTypes::BasicCpp::SimulationBlock<T>
    {
        private:
            std::vector<T> gains;
            std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime;
        public:
            Sumator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler);
            const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> GetSampleTime() const;
            const int GetInputPortAmmount() const;
            const int GetOutputPortAmmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<T> CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime);

            bool TryUpdateConfigurationValue(std::string keyName, BlockTypes::BasicCpp::ConfigurationValue value) override;
    };

    extern template class Sumator<double>;
    extern template class Sumator<std::complex<double>>;
} // namespace BasicBlocks


#endif /* BLOCK_LIBRARIES_BASIC_BLOCKS_SUMATOR */


#endif /* SRC_SUMATOR */
