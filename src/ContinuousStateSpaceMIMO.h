#ifndef SRC_STATE_SPACE_MIMO
#define SRC_STATE_SPACE_MIMO

#include <Eigen/Dense>
#include <BlockTypeSupports/BasicCppSupport/SimulationBlockCppWithContinuousStates.h>
#include <PySysLinkBase/SampleTime.h>

namespace BlockLibraries::BasicBlocksBasicCpp
{

class ContinuousStateSpaceMIMO :
    public BlockTypeSupports::BasicCppSupport::SimulationBlockCppWithContinuousStates<Eigen::MatrixXd>
{
private:

    Eigen::MatrixXd A;
    Eigen::MatrixXd B;
    Eigen::MatrixXd C;
    Eigen::MatrixXd D;

    Eigen::VectorXd x;

public:
    ContinuousStateSpaceMIMO(
        std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues,
        std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler,
        int inputPortNumber,
        int outputPortNumber);

    std::vector<Eigen::MatrixXd> ComputeOutputsOfCppBlock(
        const std::vector<Eigen::MatrixXd> inputs,
        const std::shared_ptr<PySysLinkBase::SampleTime> sampleTime,
        double currentTime,
        bool isMinorStep=false) override;

    const std::vector<double> GetContinuousStates() const override;

    void SetContinuousStates(std::vector<double> newStates) override;

    const std::vector<double> GetContinuousStateDerivativesOfCppBlock(
        const std::vector<Eigen::MatrixXd> inputs,
        const std::shared_ptr<PySysLinkBase::SampleTime> sampleTime,
        double currentTime) const override;
};

ContinuousStateSpaceMIMO::ContinuousStateSpaceMIMO(
    std::map<std::string, PySysLinkBase::ConfigurationValue> configurationValues,
    std::shared_ptr<PySysLinkBase::IBlockEventsHandler> eventHandler,
    int inputPortNumber,
    int outputPortNumber)
    :
    SimulationBlockCppWithContinuousStates<Eigen::MatrixXd>(
        configurationValues,
        eventHandler,
        inputPortNumber,
        outputPortNumber,
        false)
{
    A = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<Eigen::MatrixXd>("A", configurationValues);
    B = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<Eigen::MatrixXd>("B", configurationValues);
    C = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<Eigen::MatrixXd>("C", configurationValues);
    D = PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<Eigen::MatrixXd>("D", configurationValues);

    if (A.rows() != A.cols())
    throw std::runtime_error(
        "ContinuousStateSpaceMIMO: A must be square.");

    const int n = A.rows();

    // B
    if (B.rows() != n)
        throw std::runtime_error(
            "ContinuousStateSpaceMIMO: B must have the same number of rows as A.");

    const int m = B.cols();

    if (m == 0)
        throw std::runtime_error(
            "ContinuousStateSpaceMIMO: B must have at least one input column.");

    // C
    if (C.cols() != n)
        throw std::runtime_error(
            "ContinuousStateSpaceMIMO: C must have the same number of columns as A.");

    const int p = C.rows();

    if (p == 0)
        throw std::runtime_error(
            "ContinuousStateSpaceMIMO: C must have at least one output row.");

    // D
    if (D.rows() != p || D.cols() != m)
        throw std::runtime_error(
            "ContinuousStateSpaceMIMO: D must have the same dimensions as (outputs × inputs), i.e. p × m.");

    x = Eigen::VectorXd::Zero(n);

    try
    {
        std::vector<double> initialState =
            PySysLinkBase::ConfigurationValueManager::TryGetConfigurationValue<std::vector<double>>(
                "InitialState",
                configurationValues);

        if (initialState.size() != static_cast<size_t>(n))
            throw std::runtime_error(
                "ContinuousStateSpaceMIMO: InitialState has incorrect dimension.");

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

std::vector<Eigen::MatrixXd> ContinuousStateSpaceMIMO::ComputeOutputsOfCppBlock(
    const std::vector<Eigen::MatrixXd> inputs,
    const std::shared_ptr<PySysLinkBase::SampleTime>,
    double,
    bool)
{
    return {C * x + D * inputs[0]};
}

const std::vector<double> ContinuousStateSpaceMIMO::GetContinuousStates() const
{
    return std::vector<double>(x.data(), x.data() + x.size());
}

void ContinuousStateSpaceMIMO::SetContinuousStates(std::vector<double> newStates)
{
    if (newStates.size() != static_cast<size_t>(x.size()))
        throw std::runtime_error("ContinuousStateSpaceMIMO: Wrong number of states.");

    for (int i = 0; i < x.size(); ++i)
        x(i) = newStates[i];
}

const std::vector<double>
ContinuousStateSpaceMIMO::GetContinuousStateDerivativesOfCppBlock(
    const std::vector<Eigen::MatrixXd> inputs,
    const std::shared_ptr<PySysLinkBase::SampleTime>,
    double) const
{
    Eigen::VectorXd dx = A * x + B * inputs[0];

    return std::vector<double>(dx.data(), dx.data() + dx.size());
}

}

#endif // SRC_STATE_SPACE_MIMO