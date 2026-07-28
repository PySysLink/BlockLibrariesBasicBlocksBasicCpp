#ifndef SRC_STATE_SPACE_SISO
#define SRC_STATE_SPACE_SISO

#include <Eigen/Dense>
#include <BlockTypeSupports/BasicCppSupport/SimulationBlockCppWithContinuousStates.h>
#include <PySysLinkBase/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{

class ContinuousStateSpaceSISO :
    public BlockTypeSupports::BasicCppSupport::SimulationBlockCppWithContinuousStates<double>
{
private:

    Eigen::MatrixXd A;
    Eigen::VectorXd B;
    Eigen::RowVectorXd C;
    double D;

    Eigen::VectorXd x;

public:
    ContinuousStateSpaceSISO(
        std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues,
        std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler,
        int inputPortNumber,
        int outputPortNumber);

    std::vector<double> ComputeOutputsOfCppBlock(
        const std::vector<double> inputs,
        const std::shared_ptr<PySysLinkBase::SampleTime> sampleTime,
        double currentTime,
        bool isMinorStep=false) override;

    const std::vector<double> GetContinuousStates() const override;

    void SetContinuousStates(std::vector<double> newStates) override;

    const std::vector<double> GetContinuousStateDerivativesOfCppBlock(
        const std::vector<double> inputs,
        const std::shared_ptr<PySysLinkBase::SampleTime> sampleTime,
        double currentTime) const override;
};

ContinuousStateSpaceSISO::ContinuousStateSpaceSISO(
    std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues,
    std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler,
    int inputPortNumber,
    int outputPortNumber)
    :
    SimulationBlockCppWithContinuousStates<double>(
        configurationValues,
        eventHandler,
        inputPortNumber,
        outputPortNumber,
        false)
{
    A = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<Eigen::MatrixXd>("A", configurationValues);
    Eigen::MatrixXd Bm =
        PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<Eigen::MatrixXd>("B", configurationValues);
    Eigen::MatrixXd Cm =
        PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<Eigen::MatrixXd>("C", configurationValues);

    B = Bm.col(0);
    C = Cm.row(0);

    D = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<double>("D", configurationValues);

    if (A.rows() != A.cols())
        throw std::runtime_error("ContinuousStateSpaceSISO: A must be square.");

    const int n = A.rows();

    if (B.rows() != n || B.cols() != 1)
        throw std::runtime_error("ContinuousStateSpaceSISO: B must be n x 1.");

    if (C.rows() != 1 || C.cols() != n)
        throw std::runtime_error("ContinuousStateSpaceSISO: C must be 1 x n.");

    x = Eigen::VectorXd::Zero(n);

    try
    {
        std::vector<double> initialState =
            PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<std::vector<double>>(
                "InitialState",
                configurationValues);

        if (initialState.size() != static_cast<size_t>(n))
            throw std::runtime_error(
                "ContinuousStateSpaceSISO: InitialState has incorrect dimension.");

        for (int i = 0; i < n; ++i)
            x(i) = initialState[i];
    }
    catch (...)
    {
    }

    int continuousSampleTimeGroup = 0;

    try
    {
        continuousSampleTimeGroup =
            PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<int>(
                "ContinuousSampleTimeGroup",
                configurationValues);
    }
    catch (...)
    {
    }

    sampleTime =
        std::make_shared<PySysLinkBase::SampleTime>(
            PySysLinkBase::SampleTimeType::continuous,
            continuousSampleTimeGroup);
}

std::vector<double> ContinuousStateSpaceSISO::ComputeOutputsOfCppBlock(
    const std::vector<double> inputs,
    const std::shared_ptr<PySysLinkBase::SampleTime>,
    double,
    bool)
{
    double y = (C * x)(0) + D * inputs[0];
    return {y};
}

const std::vector<double> ContinuousStateSpaceSISO::GetContinuousStates() const
{
    return std::vector<double>(x.data(), x.data() + x.size());
}

void ContinuousStateSpaceSISO::SetContinuousStates(std::vector<double> newStates)
{
    if (newStates.size() != static_cast<size_t>(x.size()))
        throw std::runtime_error("ContinuousStateSpaceSISO: Wrong number of states.");

    for (int i = 0; i < x.size(); ++i)
        x(i) = newStates[i];
}

const std::vector<double>
ContinuousStateSpaceSISO::GetContinuousStateDerivativesOfCppBlock(
    const std::vector<double> inputs,
    const std::shared_ptr<PySysLinkBase::SampleTime>,
    double) const
{
    Eigen::VectorXd dx = A * x + B * inputs[0];

    return std::vector<double>(dx.data(), dx.data() + dx.size());
}

}

#endif // SRC_STATE_SPACE_SISO