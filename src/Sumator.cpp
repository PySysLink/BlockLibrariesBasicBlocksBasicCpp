#include "Sumator.h"

namespace BlockLibraries::BasicBlocksBasicCpp
{
    Sumator::Sumator(std::map<std::string, BlockTypes::BasicCpp::ConfigurationValue> configurationValues, std::shared_ptr<BlockTypes::BasicCpp::IEventHandler> eventHandler) : BlockTypes::BasicCpp::SimulationBlock(configurationValues, eventHandler)
    {
        this->gains = BlockTypes::BasicCpp::ConfigurationValueManager::TryGetConfigurationValue<std::vector<double>>("Gains", configurationValues);

        this->sampleTime = std::make_shared<BlockTypes::BasicCpp::SampleTime>(BlockTypes::BasicCpp::SampleTimeType::inherited, 
                                                                     std::vector<BlockTypes::BasicCpp::SampleTimeType>{BlockTypes::BasicCpp::SampleTimeType::constant,
                                                                                                                        BlockTypes::BasicCpp::SampleTimeType::continuous,
                                                                                                                        BlockTypes::BasicCpp::SampleTimeType::discrete});    
    }

    const std::shared_ptr<BlockTypes::BasicCpp::SampleTime> Sumator::GetSampleTime() const
    {
        return this->sampleTime;
    }

    const int Sumator::GetInputPortAmmount() const
    {
        return this->gains.size();
    }
    const int Sumator::GetOutputPortAmmount() const
    {
        return 1;
    }

    const std::vector<bool> Sumator::InputsHasDirectFeedthrough() const 
    {
        std::vector<bool> result = {};
        for (int i = 0; i < this->gains.size(); i++)
        {
            result.push_back(true);
        }
        return result;
    }

    std::vector<double> Sumator::CalculateOutputs(const std::vector<double> inputs, std::shared_ptr<BlockTypes::BasicCpp::SampleTime> sampleTime)
    {
        double sumation = 0;
        for (int i = 0; i < this->gains.size(); i++)
        {
            sumation += inputs[i] * this->gains[i];
        }
        return {sumation};
    }

    bool Sumator::TryUpdateConfigurationValue(std::string keyName, BlockTypes::BasicCpp::ConfigurationValue value)
    {
        if (keyName == "Gains")
        {
            try
            {
                this->gains = std::get<std::vector<double>>(value);
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

