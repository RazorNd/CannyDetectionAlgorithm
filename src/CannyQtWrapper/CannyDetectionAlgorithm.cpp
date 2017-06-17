#include "CannyDetectionAlgorithm.h"

CannyDetectionAlgorithm::CannyDetectionAlgorithm(QObject *parent) :
    QObject(parent)
{
    setSupressOperator(0);
    setConnection();
}

CannyDetectionAlgorithm::CannyDetectionAlgorithm(int tMin, int tMax, double sigma, QObject *parent) :
    QObject (parent), canny(tMin, tMax, sigma)
{
    setSupressOperator(0);
    setConnection();
}

int CannyDetectionAlgorithm::getTMin() const
{
    return canny.getTMin();
}

void CannyDetectionAlgorithm::setTMin(int value)
{
    canny.setTMin(value);
    emit tMinChanged(getTMin());
}

int CannyDetectionAlgorithm::getTMax() const
{
    return canny.getTMax();
}

void CannyDetectionAlgorithm::setTMax(int value)
{
    canny.setTMax(value);
    emit tMaxChanged(getTMax());
}

double CannyDetectionAlgorithm::getSigma() const
{
    return canny.getSigma();
}

int CannyDetectionAlgorithm::currentSuppressOperatorNumber() const
{
    return currentSuppressOperator;
}

void CannyDetectionAlgorithm::recalculate()
{
    output = canny(input);    
    emit outputImageChanged(output);
}

void CannyDetectionAlgorithm::setInputImage(QImage image)
{
    input = image;
    emit inputImageChanged(input);
}

void CannyDetectionAlgorithm::setSigma(double value)
{
    canny.setSigma(value);
    emit sigmaChanged(getSigma());
}

void CannyDetectionAlgorithm::setSupressOperator(int supressOperatorNumber)
{
    auto tmp = std::move(suppressOperators[supressOperatorNumber]);    
    canny.setSupressOperator(std::move(tmp));
    suppressOperators[currentSuppressOperatorNumber()] = std::move(tmp);
    setCurrentSupressOperatorNumber(supressOperatorNumber);
}

void CannyDetectionAlgorithm::setCurrentSupressOperatorNumber(int suppressOperatorNumber)
{
    currentSuppressOperator = suppressOperatorNumber;
    emit supressOperatorNumberChanged(currentSuppressOperator);
}

void CannyDetectionAlgorithm::setConnection()
{
    connect(this, &CannyDetectionAlgorithm::inputImageChanged, &CannyDetectionAlgorithm::needRecalculation);
    connect(this, &CannyDetectionAlgorithm::tMinChanged, &CannyDetectionAlgorithm::needRecalculation);
    connect(this, &CannyDetectionAlgorithm::tMaxChanged, &CannyDetectionAlgorithm::needRecalculation);
    connect(this, &CannyDetectionAlgorithm::sigmaChanged, &CannyDetectionAlgorithm::needRecalculation);
    connect(this, &CannyDetectionAlgorithm::supressOperatorNumberChanged, &CannyDetectionAlgorithm::needRecalculation);
}

QImage CannyDetectionAlgorithm::getOutput() const
{
    return output;
}
