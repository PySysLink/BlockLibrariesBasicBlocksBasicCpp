#ifndef BLOCK_LIBRARIES_BASIC_BLOCKS_SATURATION
#define BLOCK_LIBRARIES_BASIC_BLOCKS_SATURATION

#include <map>
#include <vector>
#include <variant>
#include <BlockTypeSupports/BasicCppSupport/SimulationBlockCpp.h>
#include <PySysLinkBase/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class Saturation : public BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>
    {
        private:
            T upperSaturation;
            T lowerSaturation;
        public:
            Saturation(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler, int inputPortNumber, int outputPortNumber);

            std::vector<T> ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep=false) override;

            bool _TryUpdateConfigurationValue(std::string keyName, PySysLinkBase::ConfigurationValue value) override;
    };

    template <typename T>
    Saturation<T>::Saturation(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler, int inputPortNumber, int outputPortNumber)
        : BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>(configurationValues, eventHandler, inputPortNumber, outputPortNumber, true)
    {
        this->upperSaturation = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<T>("UpperSaturation", configurationValues);
        this->lowerSaturation = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<T>("LowerSaturation", configurationValues);

        if constexpr (std::is_arithmetic_v<T>)
        {
            if (lowerSaturation > upperSaturation)
                throw std::runtime_error(
                    "LowerSaturation must be <= UpperSaturation.");
        }
        else
        {
            if (lowerSaturation.rows() != upperSaturation.rows() ||
                lowerSaturation.cols() != upperSaturation.cols())
                throw std::runtime_error(
                    "UpperSaturation and LowerSaturation must have identical dimensions.");

            if (((lowerSaturation.array() > upperSaturation.array()).any()))
                throw std::runtime_error(
                    "Every element of LowerSaturation must be <= the corresponding element of UpperSaturation.");
        }

        this->sampleTime = std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::inherited,
                                                                     std::vector<PySysLinkBase::SampleTimeType>{PySysLinkBase::SampleTimeType::constant,
                                                                                                                PySysLinkBase::SampleTimeType::continuous,
                                                                                                                PySysLinkBase::SampleTimeType::discrete});
    }

    template <typename T>
    std::vector<T> Saturation<T>::ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        T output = inputs[0];

        if constexpr (std::is_arithmetic_v<T>)
        {
            if (output > upperSaturation)
                output = upperSaturation;
            else if (output < lowerSaturation)
                output = lowerSaturation;
        }
        else
        {
            // Eigen matrices
            output =
                output.cwiseMin(upperSaturation)
                    .cwiseMax(lowerSaturation);
        }

        return {output};
    }

    template <typename T>
    bool Saturation<T>::_TryUpdateConfigurationValue(std::string keyName, PySysLinkBase::ConfigurationValue value)
    {
        if (keyName == "UpperSaturation")
        {
            try
            {
                this->upperSaturation = std::get<T>(value);
                return true;
            }
            catch(const std::bad_variant_access&)
            {
                return false;
            }
        }
        else if (keyName == "LowerSaturation")
        {
            try
            {
                this->lowerSaturation = std::get<T>(value);
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

#endif /* BLOCK_LIBRARIES_BASIC_BLOCKS_SATURATION */
