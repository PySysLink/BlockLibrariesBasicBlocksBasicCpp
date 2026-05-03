#ifndef SRC_DISPLAY
#define SRC_DISPLAY

#include <map>
#include <vector>
#include <string>
#include <BlockTypeSupports/BasicCppSupport/SimulationBlockCpp.h>
#include <PySysLinkBase/SampleTime.h>
#include <PySysLinkBase/BlockEvents/ValueUpdateBlockEvent.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{
    template <typename T>
    class Display : public BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>
    {
        private:
            std::string id;
        public:
            Display(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler);


            std::vector<T> ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep=false) override;
    };

    template <typename T>
    Display<T>::Display(std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues, std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler) 
        : BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<T>(configurationValues, eventHandler, 1, 0, {false})
    {
        this->sampleTime = std::make_shared<PySysLinkBase::SampleTime>(PySysLinkBase::SampleTimeType::inherited,
                                                                     std::vector<PySysLinkBase::SampleTimeType>{PySysLinkBase::SampleTimeType::constant,
                                                                                                                PySysLinkBase::SampleTimeType::continuous,
                                                                                                                PySysLinkBase::SampleTimeType::discrete});
        this->id = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<std::string>("Id", configurationValues);
    }

    template <typename T>
    std::vector<T> Display<T>::ComputeOutputsOfCppBlock(const std::vector<T> inputs, std::shared_ptr<PySysLinkBase::SampleTime> sampleTime, double currentTime, bool isMinorStep)
    {
        if (!isMinorStep)
        {
            
            this->blockEventsHandler->BlockEventCallback(std::make_shared<PySysLinkBase::ValueUpdateBlockEvent>(currentTime, "BasicCppBlock/" + this->id, inputs[0]));
        }
        return {};
    }
} // namespace BlockLibraries::BasicBlocksBasicCpp

#endif /* SRC_DISPLAY */
