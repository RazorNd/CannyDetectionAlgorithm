#ifndef CANNYDETECTIONALGORITHM_H
#define CANNYDETECTIONALGORITHM_H

#include "cannyqtwrapper_global.h"
#include "CannyDetection.h"
#include <QObject>
#include <QImage>

class CANNYQTWRAPPERSHARED_EXPORT CannyDetectionAlgorithm : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int tMin READ getTMin WRITE setTMin NOTIFY tMinChanged)
    Q_PROPERTY(int tMax READ getTMax WRITE setTMax NOTIFY tMaxChanged)
    Q_PROPERTY(double sigma READ setSigma WRITE setSigma NOTIFY sigmaChanged)

    explicit CannyDetectionAlgorithm(QObject *parent = 0);
    explicit CannyDetectionAlgorithm(int tMin, int tMax, double sigma, QObject *parent = 0);

    int getTMin() const;
    int getTMax() const;
    double getSigma() const;

    QImage getOutput() const;

signals:
    void inputImageChanged(QImage);
    void outputImageChanged(QImage);
    void tMinChanged(int);
    void tMaxChanged(int);
    void sigmaChanged(double);

public slots:
    void recalculate();
    void setInputImage(QImage image);
    void setTMin(int value);
    void setTMax(int value);
    void setSigma(double value);

private:
    QImage input;
    QImage output;
    CannyDetection canny;
};

#endif // CANNYDETECTIONALGORITHM_H
