#ifndef SRC_CONTINUOUS_TO_DISCRETE
#define SRC_CONTINUOUS_TO_DISCRETE


#include <BlockTypes/BasicCpp/SimulationBlock.h>
#include <BlockTypes/BasicCpp/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class ContinuousToDiscrete : public BlockTypes::BasicCpp::SimulationBlock<T>
    {
        private:
            std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime;
            T bufferedValue;
            int continuousSampleTimeGroup = -1;
            double sampleTimeValue = std::numeric_limits<double>::quiet_NaN();

            double simulationStartTime = std::numeric_limits<double>::quiet_NaN();
        public:
            ContinuousToDiscrete(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler);
            const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> GetSampleTime() const;
            const int GetInputPortAmmount() const;
            const int GetOutputPortAmmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;


            std::vector<T> CalculateOutputs(const std::vector<T> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime, double currentTime, bool isMinorStep=false);

            const std::vector<double> GetKnownEvents(const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> resolvedSampleTime, double simulationStartTime, double simulationEndTime) const override;
    };

    extern template class ContinuousToDiscrete<double>;
    extern template class ContinuousToDiscrete<std::complex<double>>;
} // namespace BasicBlocks



#endif /* SRC_CONTINUOUS_TO_DISCRETE */
