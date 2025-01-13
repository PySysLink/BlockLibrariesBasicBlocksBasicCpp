#ifndef SRC_BASIC_BLOCKS_CONSTANT
#define SRC_BASIC_BLOCKS_CONSTANT

#include <BlockTypes/BasicCpp/SimulationBlock.h>
#include <BlockTypes/BasicCpp/SampleTime.h>
#include <BlockTypes/BasicCpp/ConfigurationValue.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class Constant : public BlockTypes::BasicCpp::SimulationBlock<T>
    {
        private:
            T value;
            std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime;
        public:
            Constant(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler);
            const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> GetSampleTime() const;
            const int GetInputPortAmmount() const;
            const int GetOutputPortAmmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<T> CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime, bool isMinorStep=false);

            bool TryUpdateConfigurationValue(std::string keyName, BlockTypes::BasicCpp::ConfigurationValue value) override;
    };

    extern template class Constant<double>;
    extern template class Constant<std::complex<double>>;
} // namespace BasicBlocks

#endif /* SRC_BASIC_BLOCKS_CONSTANT */
