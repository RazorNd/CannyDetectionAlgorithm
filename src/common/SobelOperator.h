#ifndef SOBELOPERATOR_H
#define SOBELOPERATOR_H

#include "SupressOperator.h"

class COMMONSHARED_EXPORT SobelOperator : public SupressOperator
{
    // SupressOperator interface
public:
    virtual PixelsMatrix operator ()(const PixelsMatrix &in) const override;
};

#endif // SOBELOPERATOR_H
