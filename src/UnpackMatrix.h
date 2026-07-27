#ifndef BLOCK_LIBRARIES_BASIC_BLOCKS_BREAK_MATRIX
#define BLOCK_LIBRARIES_BASIC_BLOCKS_BREAK_MATRIX

#include <map>
#include <vector>
#include <Eigen/Dense>

#include <BlockTypeSupports/BasicCppSupport/SimulationBlockCpp.h>
#include <PySysLinkBase/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{

template<typename T>
class UnpackMatrix
    : public BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<
          Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>,
          T>
{
private:

    using Matrix =
        Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;

    int rows;
    int cols;

public:

    UnpackMatrix(
        std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues,
        std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler,
        int inputPortNumber,
        int outputPortNumber);

    std::vector<T> ComputeOutputsOfCppBlock(
        const std::vector<Matrix> inputs,
        std::shared_ptr<PySysLinkBase::SampleTime> sampleTime,
        double currentTime,
        bool isMinorStep = false) override;
};


template<typename T>
UnpackMatrix<T>::UnpackMatrix(
    std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues,
    std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler,
    int inputPortNumber,
    int outputPortNumber)
    :
    BlockTypeSupports::BasicCppSupport::SimulationBlockCpp<
        Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>,
        T>(
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
std::vector<T>
UnpackMatrix<T>::ComputeOutputsOfCppBlock(
    const std::vector<Matrix> inputs,
    std::shared_ptr<PySysLinkBase::SampleTime>,
    double,
    bool)
{
    if (inputs.size() != 1)
        throw std::runtime_error(
            "UnpackMatrix expects exactly one matrix input.");

    const Matrix& matrix = inputs.front();

    if (matrix.rows() != rows || matrix.cols() != cols)
        throw std::runtime_error(
            "UnpackMatrix: input matrix dimensions do not match Rows and Columns.");

    std::vector<T> outputs;
    outputs.reserve(rows * cols);

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            outputs.push_back(matrix(r, c));
        }
    }

    return outputs;
}

}

#endif