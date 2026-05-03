#ifndef SRC_BASIC_BLOCKS_CONSTANT
#define SRC_BASIC_BLOCKS_CONSTANT

#include <map>
#include <vector>
#include <variant>
#include <BlockTypeSupports/BasicCppSupport/SimulationBlockCpp.h>
#include <PySysLinkBase/SampleTime.h>
#include <PySysLinkBase/ConfigurationValue.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class Constant : public BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>
    {
        private:
            T value;
            std::shared_ptr<PySysLinkBase::SampleTime> sampleTime;
        public:
            Constant(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler);
            const int GetInputPortAmount() const;
            const int GetOutputPortAmount() const;
            const std::vector<bool> InputsHasDirectFeedthrough() const override;

            std::vector<T> ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep=false) override;

            bool _TryUpdateConfigurationValue(std::string keyName, PySysLinkBase::ConfigurationValue value) override;
    };

    template <typename T>
    Constant<T>::Constant(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler) : BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>(configurationValues, eventHandler)
    {
        this->value = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<T>("Value", configurationValues);
        this->sampleTime = std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::constant);
    }

    template <typename T>
    const int Constant<T>::GetInputPortAmount() const
    {
        return 0;
    }

    template <typename T>
    const int Constant<T>::GetOutputPortAmount() const
    {
        return 1;
    }

    template <typename T>
    const std::vector<bool> Constant<T>::InputsHasDirectFeedthrough() const
    {
        return {};
    }

    template <typename T>
    std::vector<T> Constant<T>::ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        return {this->value};
    }

    template <typename T>
    bool Constant<T>::_TryUpdateConfigurationValue(std::string keyName, PySysLinkBase::ConfigurationValue value)
    {
        if (keyName == "Value")
        {
            try
            {
                this->value = std::get<T>(value);
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

#endif /* SRC_BASIC_BLOCKS_CONSTANT */
