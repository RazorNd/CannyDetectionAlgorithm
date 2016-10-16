#include "CannyDetectionAlgorithm.h"

CannyDetectionAlgorithm::CannyDetectionAlgorithm(QObject *parent) :
    QObject(parent)
{
}

CannyDetectionAlgorithm::CannyDetectionAlgorithm(int tMin, int tMax, double sigma, QObject *parent) :
    QObject (parent), canny(tMin, tMax, sigma)
{
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

QImage CannyDetectionAlgorithm::getOutput() const
{
    return output;
}
