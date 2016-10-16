#ifndef SOBELOPERATOR_H
#define SOBELOPERATOR_H

#include "SupressOperator.h"

class SobelOperator : public SupressOperator
{
    // SupressOperator interface
public:
    virtual PixelsMatrix operator ()(const PixelsMatrix &in) const override;
};

#endif // SOBELOPERATOR_H
