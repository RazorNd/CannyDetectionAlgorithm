#include "CannyDetectionAlgorithm.h"
#include <QDebug>

CannyDetectionAlgorithm::CannyDetectionAlgorithm(QObject *parent) :
    QObject(parent)
{
    setConnection();
    setSupressOperator(0);
}

CannyDetectionAlgorithm::CannyDetectionAlgorithm(int tMin, int tMax, double sigma, QObject *parent) :
    QObject (parent), canny(tMin, tMax, sigma)
{
    setConnection();
    setSupressOperator(0);
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
    qDebug() << tmp.target<PixelsMatrix (const PixelsMatrix &in)>();
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
    connect(this, &CannyDetectionAlgorithm::inputImageChanged, &CannyDetectionAlgorithm::recalculate);
    connect(this, &CannyDetectionAlgorithm::tMinChanged, &CannyDetectionAlgorithm::recalculate);
    connect(this, &CannyDetectionAlgorithm::tMaxChanged, &CannyDetectionAlgorithm::recalculate);
    connect(this, &CannyDetectionAlgorithm::sigmaChanged, &CannyDetectionAlgorithm::recalculate);
    connect(this, &CannyDetectionAlgorithm::supressOperatorNumberChanged, &CannyDetectionAlgorithm::recalculate);
}

QImage CannyDetectionAlgorithm::getOutput() const
{
    return output;
}
