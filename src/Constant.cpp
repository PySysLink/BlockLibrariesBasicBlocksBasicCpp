#include "Constant.h"
#include <vector>
#include <stdexcept>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    Constant::Constant(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler) : BlockTypes::BasicCpp::SimulationBlock(configurationValues, eventHandler)
    {
        this->value = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<double>("Value", configurationValues);

        this->sampleTime = std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::constant);
    }

    const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> Constant::GetSampleTime() const
    {
        return this->sampleTime;
    }

    const int Constant::GetInputPortAmmount() const
    {
        return 0;
    }
    const int Constant::GetOutputPortAmmount() const
    {
        return 1;
    }

    const std::vector<bool> Constant::InputsHasDirectFeedthrough() const 
    {
        return {};
    }

    std::vector<double> Constant::CalculateOutputs(const std::vector<double> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime)
    {
        return {this->value};
    }

    bool Constant::TryUpdateConfigurationValue(std::string keyName, BlockTypes::BasicCpp::ConfigurationValue value)
    {
        if (keyName == "Value")
        {
            try
            {
                this->value = std::get<double>(value);
                return true;
            }
            catch(std::bad_variant_access)
            {
                return false;
            }
        }
        else {return false;}
    }

} // namespace BlockLibraries::BasicBlocks

