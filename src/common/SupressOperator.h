#ifndef SUPRESSOPERATOR_H
#define SUPRESSOPERATOR_H

#include "PixelsMatrix.h"

class SupressOperator
{
public:
    virtual ~SupressOperator() {}
    virtual PixelsMatrix operator() (const PixelsMatrix &in) const = 0;
};

#endif // SUPRESSOPERATOR_H
