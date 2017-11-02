#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include "PixelsMatrix.h"

template<int KernelSize>
PixelsMatrix convolution(const PixelsMatrix &in, const double kernel[], bool normalize = false)
{
    const int nx = in.size.height(), ny = in.size.width();
    const int khalf = KernelSize / 2;
    double min = std::numeric_limits<double>::max(), max = std::numeric_limits<double>::min();

    if (normalize)
        for (int m = khalf; m < nx - khalf; m++)
            for (int n = khalf; n < ny - khalf; n++) {
                double pixel = 0.0;
                size_t c = 0;
                for (int j = -khalf; j <= khalf; j++)
                    for (int i = -khalf; i <= khalf; i++) {
                        pixel += in[(n - j) * nx + m - i] * kernel[c];
                        c++;
                    }
                if (pixel < min)
                    min = pixel;
                if (pixel > max)
                    max = pixel;
                }

    PixelsMatrix out(in.size);

    for (int m = khalf; m < nx - khalf; m++)
        for (int n = khalf; n < ny - khalf; n++) {
            double pixel = 0.0;
            size_t c = 0;
            for (int j = -khalf; j <= khalf; j++)
                for (int i = -khalf; i <= khalf; i++) {
                    pixel += in[(n - j) * nx + m - i] * kernel[c];
                    c++;
                }

            if (normalize)
                pixel = PixelsMatrix::MAX_BRIGHTNESS * (pixel - min) / (max - min);
            out[n * nx + m] = static_cast<PixelsMatrix::pixel_t>(pixel);
        }
    return out;
}

template <int KernelSize>
PixelsMatrix gaussianFilter(const PixelsMatrix &in, const double sigma)
{
    using namespace std;
    const int n = KernelSize;
    const double mean = floor(n / 2.0);
    double kernel[n * n]; // variable length array

    size_t c = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            kernel[c] = exp(-0.5 * (pow((i - mean) / sigma, 2.0) +
                                    pow((j - mean) / sigma, 2.0)))
                        / (2 * M_PI * sigma * sigma);
            c++;
        }

    return convolution<n>(in, kernel, true);
}

#endif // UTIL_H
