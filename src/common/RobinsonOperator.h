#ifndef ROBINSONOPERATOR_H
#define ROBINSONOPERATOR_H

#include "SupressOperator.h"

class COMMONSHARED_EXPORT RobinsonOperator : public SupressOperator
{
    enum Direction
    {
        ee, // 0
        ne, // 45
        nn, // 90
        nw, // 135
        ww, // 180
        sw, // 225
        ss, // 270
        se, // 315
    };

    // SupressOperator interface
public:
    virtual PixelsMatrix operator ()(const PixelsMatrix &in) const override;
private:
    class GradientCalculator {
    public:
        explicit GradientCalculator(const QSize size);

        typedef std::vector<Direction> direction_vector;
        void operator() (const PixelsMatrix &in) const;
        PixelsMatrix getGradient() const;
        direction_vector getGradientDirection() const;
    private:
        mutable PixelsMatrix gradient;
        mutable direction_vector gradientDirection;
    };
};

#endif // ROBINSONOPERATOR_H
