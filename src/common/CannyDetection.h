#ifndef CANNYDETECTION_H
#define CANNYDETECTION_H

#include "common_global.h"
#include "SupressOperator.h"
#include "SobelOperator.h"
#include <functional>
#include <QImage>

class COMMONSHARED_EXPORT CannyDetection
{
public:
    typedef std::function<PixelsMatrix (const PixelsMatrix &in)> SupressOperatorType;
    CannyDetection();
    CannyDetection(int tMin, int tMax, double sigma);    

    double getSigma() const;
    void setSigma(double value);

    int getTMin() const;
    void setTMin(int value);

    int getTMax() const;
    void setTMax(int value);

    QImage operator() (const QImage &in) const;

    void setSupressOperator(SupressOperatorType &&value);

private:
    double sigma = 1.0;
    int tMin = 45;
    int tMax = 50;
    SupressOperatorType supressOperator = SobelOperator();
};

#endif // CANNYDETECTION_H
