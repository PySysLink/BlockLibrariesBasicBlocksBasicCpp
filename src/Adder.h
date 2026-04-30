#ifndef SRC_SUMATOR
#define SRC_SUMATOR
#ifndef BLOCK_LIBRARIES_BASIC_BLOCKS_SUMATOR
#define BLOCK_LIBRARIES_BASIC_BLOCKS_SUMATOR

#include <map>
#include <vector>
#include <variant>
#include <BlockTypeSupports/BasicCppSupport/SimulationBlockCpp.h>
#include <PySysLinkBase/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class Adder : public BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>
    {
        private:
            std::vector<T> gains;
            std::shared_ptr<PySysLinkBase::SampleTime> sampleTime;
        public:
            Adder(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler);
            const int GetInputPortAmount() const;
            const int GetOutputPortAmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const;

            std::vector<T> ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep=false) override;

            bool _TryUpdateConfigurationValue(std::string keyName, PySysLinkBase::ConfigurationValue value) override;
    };

    template <typename T>
    Adder<T>::Adder(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler) : BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>(configurationValues, eventHandler)
    {
        this->gains = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<std::vector<T>>("Gains", configurationValues);
        this->sampleTime = std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::inherited,
                                                                     std::vector<PySysLinkBase::SampleTimeType>{PySysLinkBase::SampleTimeType::constant,
                                                                                                                PySysLinkBase::SampleTimeType::continuous,
                                                                                                                PySysLinkBase::SampleTimeType::discrete});
    }

    template <typename T>
    const int Adder<T>::GetInputPortAmount() const
    {
        return static_cast<int>(this->gains.size());
    }

    template <typename T>
    const int Adder<T>::GetOutputPortAmount() const
    {
        return 1;
    }

    template <typename T>
    const std::vector<bool> Adder<T>::InputsHasDirectFeedthrough() const
    {
        std::vector<bool> result;
        result.reserve(this->gains.size());
        for (size_t i = 0; i < this->gains.size(); ++i)
        {
            result.push_back(true);
        }
        return result;
    }

    template <typename T>
    std::vector<T> Adder<T>::ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        T sumation = T{};
        for (size_t i = 0; i < this->gains.size(); ++i)
        {
            sumation += inputs[i] * this->gains[i];
        }
        return {sumation};
    }

    template <typename T>
    bool Adder<T>::_TryUpdateConfigurationValue(std::string keyName, PySysLinkBase::ConfigurationValue value)
    {
        if (keyName == "Gains")
        {
            try
            {
                this->gains = std::get<std::vector<T>>(value);
                return true;
            }
            catch(const std::bad_variant_access&)
            {
                return false;
            }
        }
        return false;
    }
} // namespace BlockLibraries::BasicBlocksBasicCpp

#endif /* BLOCK_LIBRARIES_BASIC_BLOCKS_SUMATOR */

#endif /* SRC_SUMATOR */
