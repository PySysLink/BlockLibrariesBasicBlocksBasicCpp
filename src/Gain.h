#ifndef BLOCK_LIBRARIES_BASIC_BLOCKS_GAIN
#define BLOCK_LIBRARIES_BASIC_BLOCKS_GAIN

#include <map>
#include <vector>
#include <variant>
#include <BlockTypeSupports/BasicCppSupport/SimulationBlockCpp.h>
#include <PySysLinkBase/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class Gain : public BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>
    {
        private:
            T gain;
        public:
            Gain(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler);

            std::vector<T> ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep=false) override;

            bool _TryUpdateConfigurationValue(std::string keyName, PySysLinkBase::ConfigurationValue value) override;
    };

    template <typename T>
    Gain<T>::Gain(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler) 
        : BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>(configurationValues, eventHandler, 1, 1, {true})
    {
        this->gain = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<T>("Gain", configurationValues);
        this->sampleTime = std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::inherited,
                                                                     std::vector<PySysLinkBase::SampleTimeType>{PySysLinkBase::SampleTimeType::constant,
                                                                                                                PySysLinkBase::SampleTimeType::continuous,
                                                                                                                PySysLinkBase::SampleTimeType::discrete});
    }

    template <typename T>
    std::vector<T> Gain<T>::ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        return {inputs[0] * this->gain};
    }

    template <typename T>
    bool Gain<T>::_TryUpdateConfigurationValue(std::string keyName, PySysLinkBase::ConfigurationValue value)
    {
        if (keyName == "Gain")
        {
            try
            {
                this->gain = std::get<T>(value);
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

#endif /* BLOCK_LIBRARIES_BASIC_BLOCKS_GAIN */
