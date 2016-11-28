#ifndef CANNYDETECTIONALGORITHM_H
#define CANNYDETECTIONALGORITHM_H

#include "cannyqtwrapper_global.h"
#include "CannyDetection.h"
#include "RobinsonOperator.h"
#include "SobelOperator.h"
#include <QObject>
#include <QImage>

class CANNYQTWRAPPERSHARED_EXPORT CannyDetectionAlgorithm : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int tMin READ getTMin WRITE setTMin NOTIFY tMinChanged)
    Q_PROPERTY(int tMax READ getTMax WRITE setTMax NOTIFY tMaxChanged)
    Q_PROPERTY(double sigma READ getSigma WRITE setSigma NOTIFY sigmaChanged)
    Q_PROPERTY(int currentSuppressOperatorNumber READ currentSuppressOperatorNumber WRITE setSupressOperator NOTIFY supressOperatorNumberChanged)

    explicit CannyDetectionAlgorithm(QObject *parent = 0);
    explicit CannyDetectionAlgorithm(int tMin, int tMax, double sigma, QObject *parent = 0);

    int getTMin() const;
    int getTMax() const;
    double getSigma() const;

    int currentSuppressOperatorNumber() const;

    QImage getOutput() const;

signals:
    void inputImageChanged(QImage);
    void outputImageChanged(QImage);
    void tMinChanged(int);
    void tMaxChanged(int);
    void sigmaChanged(double);
    void supressOperatorNumberChanged(int);

public slots:
    void recalculate();
    void setInputImage(QImage image);
    void setTMin(int value);
    void setTMax(int value);
    void setSigma(double value);
    void setSupressOperator(int supressOperatorNumber);

private:
    int currentSuppressOperator = 0;
    QVector<CannyDetection::SupressOperatorType> suppressOperators = {RobinsonOperator(), SobelOperator()};

    QImage input;
    QImage output;
    CannyDetection canny;

    void setCurrentSupressOperatorNumber(int suppressOperatorNumber);
    void setConnection();
};

#endif // CANNYDETECTIONALGORITHM_H
