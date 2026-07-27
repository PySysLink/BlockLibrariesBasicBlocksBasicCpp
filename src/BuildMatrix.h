#ifndef BLOCK_LIBRARIES_BASIC_BLOCKS_BUILD_MATRIX
#define BLOCK_LIBRARIES_BASIC_BLOCKS_BUILD_MATRIX

#include <map>
#include <vector>
#include <Eigen/Dense>

#include <BlockTypeSupports/BasicCppSupport/SimulationBlockCpp.h>
#include <PySysLinkBase/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{

template<typename T>
class BuildMatrix
    : public BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<
          T,
          Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>
{
private:

    using Matrix =
        Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;

    int rows;
    int cols;

public:

    BuildMatrix(
        std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues,
        std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler,
        int inputPortNumber,
        int outputPortNumber);

    std::vector<Matrix> ComputeOutputsOfCppBlock(
        const std::vector<T> inputs,
        std::shared_ptr<PySysLinkBase::SampleTime> sampleTime,
        double currentTime,
        bool isMinorStep = false) override;
};


template<typename T>
BuildMatrix<T>::BuildMatrix(
    std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues,
    std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler,
    int inputPortNumber,
    int outputPortNumber)
    :
    BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<
        T,
        Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>(
            configurationValues,
            eventHandler,
            inputPortNumber,
            outputPortNumber,
            true)
{
    rows =
        PySysLinkBase::ConfigurationValueManager::
            TryGetConfigurationValue<int>("Rows", configurationValues);

    cols =
        PySysLinkBase::ConfigurationValueManager::
            TryGetConfigurationValue<int>("Columns", configurationValues);

    this->sampleTime =
        std::make_shared<PySysLinkBase::SampleTime>(
            PySysLinkBase::SampleTimeType::inherited,
            std::vector<PySysLinkBase::SampleTimeType>{
                PySysLinkBase::SampleTimeType::constant,
                PySysLinkBase::SampleTimeType::continuous,
                PySysLinkBase::SampleTimeType::discrete});
}


template<typename T>
std::vector<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>
BuildMatrix<T>::ComputeOutputsOfCppBlock(
    const std::vector<T> inputs,
    std::shared_ptr<PySysLinkBase::SampleTime>,
    double,
    bool)
{
    Matrix matrix(rows, cols);

    if (static_cast<int>(inputs.size()) != rows * cols)
        throw std::runtime_error(
            "BuildMatrix: number of inputs does not match Rows*Columns.");

    int k = 0;

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            matrix(r, c) = inputs[k++];
        }
    }

    return {matrix};
}

}

#endif